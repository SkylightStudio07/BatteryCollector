// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

// ���� �����÷��� ���¸� ����
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

	// ���� �÷��� ���·� ���ư�
	UFUNCTION(BlueprintPure, Category ="Power")
	EBatteryPlayState GetCurrentState() const;

	// �� �÷��� ���� ����
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	// ���Ӹ��� ������ ���� �÷����� �ν��Ͻ��� �����ϴ� ���� �ƴϱ⿡ �ٸ� ������ �з����Ͱ� �ʿ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float PowerToWin;

	// HUD ȭ�鿡 ����� ���� Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// HUD�� �ν��Ͻ�. HUDWidget�� ������ �ϳ��� ���纻
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	// ���� �÷��� ���¸� ����
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	// ���� �÷��� ���¿� ������ �ִ� ��� �Լ��� ȣ���� ���
	void HandleNewState(EBatteryPlayState NewState);
};



