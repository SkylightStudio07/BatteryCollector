// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SpawnVolume.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// DecayRate ���۰�
	DecayRate = 0.01f;
}

void ABatteryCollectorGameMode::BeginPlay() {
	Super::BeginPlay();

	// ��� ���� ���� ���͸� ã�Ƴ�
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors) {
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor) {
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentState(EBatteryPlayState::EPlaying);

	// set the score to best
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) {
		PowerToWin = (MyCharacter->GetInitialPower()) * 1.25f;
	}

	if (HUDWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}

}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

void ABatteryCollectorGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) {
		if (MyCharacter->GetCurrentPower() > PowerToWin) {
			SetCurrentState(EBatteryPlayState::EWon);
		}
		else if (MyCharacter->GetCurrentPower() > 0) { // �÷��̾� ü���� 0 �̻��϶���
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower()));
		}
		else {
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
	

}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const {
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState) {
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState) {
	switch (NewState)
	{
		// ���� �÷������� ���
		case EBatteryPlayState::EPlaying: {
			// ���� ���� Ȱ��ȭ
			for (ASpawnVolume* Volume : SpawnVolumeActors) {
				Volume->SetSpawningActive(true);
			}
		}
		break;
		case EBatteryPlayState::EWon: {
			// ���� ���� ��Ȱ��ȭ
			for (ASpawnVolume* Volume : SpawnVolumeActors) {
				Volume->SetSpawningActive(false);
			}
		}
		break;
		case EBatteryPlayState::EGameOver: {
			// ���� ���� ��Ȱ��ȭ
			// �÷��̾� �Է� ����, �÷��̾� ĳ���� ���׵�
			for (ASpawnVolume* Volume : SpawnVolumeActors) {
				Volume->SetSpawningActive(false);
			}
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController) {
				PlayerController->SetCinematicMode(true, false, false, true, true);
			}
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter) {
				MyCharacter->GetMesh()->SetSimulatePhysics(true);
				MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}
		break;

		default:
		case EBatteryPlayState::EUnknown: {

		}
		break;
	}
}