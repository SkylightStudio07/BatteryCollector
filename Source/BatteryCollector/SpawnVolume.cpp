// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "BatteryCollector.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 박스 컴포넌트 생성

	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	// 아이템 생성 최소/최대값 설정
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	// SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	// 게임 속 모든 타이머를 추적
	// GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// 모든 박스 컴포넌트에는 중점과 면꺼지의 거리값이 벡터값으로 들어가있음
FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn) {
	if (bShouldSpawn) {
		// spawnpickup 타이머 설정
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		// 게임 속 모든 타이머를 추적
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	}
	else {
		// 타이머 초기화
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawnVolume::SpawnPickup() {

	// 스폰할 무언가를 가지고 있을때
	if (WhatToSpawn != NULL) {
		// 월드가 유효한지 확인
		UWorld* const World = GetWorld();
		// 아이템 생성시에 world를 이용하기에 확인만 하지 않고 저장까지 함
		if (World) {
			// 스폰 패러미터 설정
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this; // 부모는 this
			// 누가 아이템을 만들고 만들게 하였는지 명시

			// 만드는 위치에 랜덤한 위치를 고름
			FVector SpawnLocation = GetRandomPointInVolume();

			// 만든 아이템에 랜덤한 회전값을 넣어줌
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			// 아이템 스폰
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);


			// 하나의 아이템을 생성하고 범위 내 값으로 타이머 시간을 랜덤하게 새로 뽑음.
			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			// 게임 속 모든 타이머를 추적
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
		}
	}
}