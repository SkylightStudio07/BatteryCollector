// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

// 현재 게임플레이 상태를 저장
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8 {
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};


UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual void BeginPlay() override;

	// 현재 플레이 상태로 돌아감
	UFUNCTION(BlueprintPure, Category ="Power")
	EBatteryPlayState GetCurrentState() const;

	// 새 플레이 상태 설정
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	// 게임모드는 레벨에 직접 올려놓고 인스턴스를 편집하는 것이 아니기에 다른 형식의 패러미터가 필요
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float PowerToWin;

	// HUD 화면에 사용할 위젯 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// HUD의 인스턴스. HUDWidget에 기인한 하나의 복사본
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	// 현재 플레이 상태를 추적
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	// 게임 플레이 상태에 영향을 주는 모든 함수의 호출을 담당
	void HandleNewState(EBatteryPlayState NewState);
};



