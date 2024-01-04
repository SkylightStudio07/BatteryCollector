// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABatteryPickup();

	// 블루프린트 네이티브 이벤트니 임플멘테이션 이용
	void WasCollected_Implementation() override;

	// 어디서든 배터리의 파워값을 얻을 수 있음
	float GetPower();

protected: 
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Power", META = (BlueprintProtected = "true"))
		float BatteryPower;
};
