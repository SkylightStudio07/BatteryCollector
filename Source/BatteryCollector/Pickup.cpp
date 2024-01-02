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

	// ������ ����ƽ �޽� ������Ʈ�� ��Ʈ ������Ʈ�� ����.
	// ���߿� ������ ����ų� �ٸ� �޽ð� �߰��Ǹ� Pickup �޽��� ũ��� ��ġ�� ������� ��.
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