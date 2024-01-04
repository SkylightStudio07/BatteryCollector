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

protected: // �ڽ��� ��� ����
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Return the mesh for the pickup */
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }
	// �ٸ� Ŭ�������� �޽��� ��Ƽ������ �����Ϸ��� �Ҷ� ���� �Լ�.
	// GetMesh() �Լ��� �޽� ������Ʈ�� �����ϴ� ���� �ƴ϶� ��ȯ�� ���ֹǷ� const �����̴�.

	/*true when the pickup can beused, and false when pickup is deactivated */
	// ��� ������ ������ true, �Ұ����� ������ false
	bool bIsActive;

	//BlueprintPure�� �� ���� ����, �Ϲ������δ� �ϸ� �ȵ�
	//��ȯ���� �޶�� �� ������ ������ �Ǵ� ��ŭ, ���ÿ��� ���𰡸� ������ ��ȯ�ϴ� ��ũ��Ʈ�� ��������� �ι� ��ȯ�ϰ� ��. �̷��� ���� ������ ���� �޶��� �� ����.
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool isActive();

	/* Allows other classes to safely change whether or not pickup is active*/
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		//���� ���� �ɿ��� ���� ��ȣ�� �ԷµǾ��� ������ ����ǰ�, ������� �ƿ�ǲ �ɿ��� ������ ��.
	void SetActive(bool NewPickupState);

	// ���� �������� ���� ������ ����Ǵ� �ڽ�Ʈ�� ���� ���� ��������� Bluepirnt���ٴ� BlueprintCallable�� �� ���� 
	// ���� ���� ����Ǵ� ������ pure, ���� ������� �ʴ� ������ Callable.

	// �������Ʈ ����Ƽ�� �̺�Ʈ�� �̺�Ʈ �߻� �� �ڵ忡�� ������ �κ��� ����
	// �������Ʈ������ ������ �� ���� �κ�
	// �������� �Ծ��� �� ȣ���� �Լ�
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation(); // �ڼ� �ڵ忡�� �������̵� ����


private:
	// pickup Ŭ���������� ��� �� ���� ����
	/** Static mesh to represent the pickup in the level **/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	// 1. ������ �������� ���ų� �� Ŭ������ �θ�� �ϴ� ��������͸� ����� ���� ���δ� �� �� ������ ������ �Ұ����ϰ� �ϴ� ��.
	// 2. ������ �������Ʈ���� ��Ÿ�� ����ƽ �޽� ������Ʈ���� ���� �Ұ�.
	// 3. ������ �г��� Pickup ī�װ����� ��Ÿ����.

	class UStaticMeshComponent* PickupMesh;// ����ƽ �޽� ������Ʈ���� ������. ���� ������ ����Ѵ�.

};
