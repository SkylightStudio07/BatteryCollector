// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected: // 자식이 사용 가능
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Return the mesh for the pickup */
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }
	// 다른 클래스에서 메시의 머티리얼을 변경하려고 할때 쓰는 함수.
	// GetMesh() 함수는 메시 컴포넌트를 변경하는 것이 아니라 반환만 해주므로 const 형태이다.

	/*true when the pickup can beused, and false when pickup is deactivated */
	// 사용 가능할 때에는 true, 불가능일 때에는 false
	bool bIsActive;

	//BlueprintPure은 값 변경 가능, 일반적으로는 하면 안됨
	//반환값을 달라고 할 때마다 실행이 되는 만큼, 스택에서 무언가를 꺼내서 반환하는 스크립트가 들어있으면 두번 반환하게 됨. 이러면 값이 순서에 따라 달라질 수 있음.
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool isActive();

	/* Allows other classes to safely change whether or not pickup is active*/
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		//실행 순서 핀에서 실행 신호가 입력되었을 때에만 실행되고, 결과값을 아웃풋 핀에다 저장해 둠.
	void SetActive(bool NewPickupState);

	// 자주 변경하지 않을 것으로 예상되는 코스트가 많이 들어가는 결과값에는 Bluepirnt보다는 BlueprintCallable이 더 적합 
	// 따라서 자주 변경되는 값에는 pure, 자주 변경되지 않는 값에는 Callable.

	// 블루프린트 네이티브 이벤트는 이벤트 발생 시 코드에서 설정한 부분을 실행
	// 블루프린트에서는 설정될 수 없는 부분
	// 아이템을 먹었을 때 호출할 함수
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation(); // 자손 코드에서 오버라이딩 가능


private:
	// pickup 클래스에서만 사용 및 참조 가능
	/** Static mesh to represent the pickup in the level **/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	// 1. 레벨에 아이템을 놓거나 이 클래스를 부모로 하는 블루프린터를 만들면 존재 여부는 알 수 있지만 편집은 불가능하게 하는 것.
	// 2. 액터의 블루프린트에서 나타는 스태틱 메쉬 컴포넌트에서 조절 불가.
	// 3. 디테일 패널의 Pickup 카테고리에서 나타난다.

	class UStaticMeshComponent* PickupMesh;// 스태틱 메쉬 컴포넌트로의 포인터. 전방 선언을 사용한다.

};
