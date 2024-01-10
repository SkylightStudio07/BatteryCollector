// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void SetSpawningActive(bool bShouldSpawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*the pickup to Spawn*/
	// APickup이나 자손클래스만으로 한정하여 사용 가능
	// pickup 블루프린트에서 whaytospawn 변수 설정 가능
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	// 어떤 값이 아니기에 UPROPORTY 매크로 필요없음
	FTimerHandle SpawnTimer;

	// 생성시 최소 지연 시간
	// 블루프린트를 만들면 이 값을 동적으로 변경 가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	//최대 지연 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;






public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// WhereToSpawn 값을 반환
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	// 박스 컴포넌트 볼륨 속의 랜덤한 좌표 반환 후 벡터값으로 변환
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();




private:
	// 아이템 스폰 위치를 지정할 박스 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	// 새 아이템 생성을 다룸
	void SpawnPickup();

	// 코드에서만 값을 변경할 것이기에 private
	// 현재 아이템 생성 딜레이값
	float SpawnDelay;
};
