// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"

// Set default values
ABatteryPickup::ABatteryPickup() {
	GetMesh()->SetSimulatePhysics(true);
	// ���͸��� ��������ڸ��� ���� �ο�(��������)
}

void ABatteryPickup::WasCollected_Implementation() {
	//���̽� �Ⱦ� ��ũ��Ʈ
	Super::WasCollected_Implementation();
	Destroy();
}