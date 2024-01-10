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

	// �ڽ� ������Ʈ ����

	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	// ������ ���� �ּ�/�ִ밪 ����
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	// SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	// ���� �� ��� Ÿ�̸Ӹ� ����
	// GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// ��� �ڽ� ������Ʈ���� ������ �鲨���� �Ÿ����� ���Ͱ����� ������
FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn) {
	if (bShouldSpawn) {
		// spawnpickup Ÿ�̸� ����
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		// ���� �� ��� Ÿ�̸Ӹ� ����
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	}
	else {
		// Ÿ�̸� �ʱ�ȭ
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawnVolume::SpawnPickup() {

	// ������ ���𰡸� ������ ������
	if (WhatToSpawn != NULL) {
		// ���尡 ��ȿ���� Ȯ��
		UWorld* const World = GetWorld();
		// ������ �����ÿ� world�� �̿��ϱ⿡ Ȯ�θ� ���� �ʰ� ������� ��
		if (World) {
			// ���� �з����� ����
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this; // �θ�� this
			// ���� �������� ����� ����� �Ͽ����� ���

			// ����� ��ġ�� ������ ��ġ�� ��
			FVector SpawnLocation = GetRandomPointInVolume();

			// ���� �����ۿ� ������ ȸ������ �־���
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			// ������ ����
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);


			// �ϳ��� �������� �����ϰ� ���� �� ������ Ÿ�̸� �ð��� �����ϰ� ���� ����.
			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			// ���� �� ��� Ÿ�̸Ӹ� ����
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
		}
	}
}