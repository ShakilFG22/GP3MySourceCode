// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_InstantlyLookAtPlayer.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UMyBTTask_InstantlyLookAtPlayer::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMyBTTask_InstantlyLookAtPlayer::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

FRotator UMyBTTask_InstantlyLookAtPlayer::FindNewLookDirection(ACharacter* ControlledCharacter, ACharacter* TargetCharacter)
{
	FVector ControlledCharPos = ControlledCharacter->GetTransform().GetLocation();
	FVector TargetCharPos = TargetCharacter->GetTransform().GetLocation();

	FRotator FinalLookRotation = UKismetMathLibrary::FindLookAtRotation(ControlledCharPos, TargetCharPos);

	FinalLookRotation.Pitch = 0.0f;
	FinalLookRotation.Roll = 0.0f;

	return FinalLookRotation;
}

void UMyBTTask_InstantlyLookAtPlayer::SetNewRotation(ACharacter* CharToRotate, FRotator FinalRotation)
{
	CharToRotate->SetActorRotation(FinalRotation);
}

EBTNodeResult::Type UMyBTTask_InstantlyLookAtPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* ThisAIController = OwnerComp.GetAIOwner();
	
	if(!ThisAIController)
	{
		return EBTNodeResult::Failed;
	}
	
	ACharacter* ControlledCharacter = ThisAIController->GetCharacter();
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(ControlledCharacter->GetWorld(), 0);

	SetNewRotation(ControlledCharacter, FindNewLookDirection(ControlledCharacter, PlayerCharacter));
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
