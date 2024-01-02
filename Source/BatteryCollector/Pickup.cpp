// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsActive = true;

	// Create the Static Mesh Component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));

	// 생성한 스태틱 메시 컴포넌트를 루트 컴포넌트로 지정.
	// 나중에 문제가 생기거나 다른 메시가 추가되면 Pickup 메시의 크기와 위치를 기반으로 함.
	RootComponent = PickupMesh;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickup::isActive() {
	return bIsActive;
}

void APickup::SetActive(bool NewPickupState) {
	bIsActive = NewPickupState;
}