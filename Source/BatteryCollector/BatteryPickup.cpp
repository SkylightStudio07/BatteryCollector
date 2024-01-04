// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"

// Set default values
ABatteryPickup::ABatteryPickup() {
	GetMesh()->SetSimulatePhysics(true);
	// 배터리가 만들어지자마자 물리 부여(자유낙하)

	// 배터리 디폴트값
	BatteryPower = 150.0f;

}

void ABatteryPickup::WasCollected_Implementation() {
	//베이스 픽업 스크립트
	Super::WasCollected_Implementation();
	Destroy();
}

//배터리값 반환
float ABatteryPickup::GetPower() {
	return BatteryPower;
}