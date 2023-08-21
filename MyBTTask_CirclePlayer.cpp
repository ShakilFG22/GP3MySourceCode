// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_CirclePlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UMyBTTask_CirclePlayer::UMyBTTask_CirclePlayer()
{
	NodeName = "Circle Player";
}

void UMyBTTask_CirclePlayer::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMyBTTask_CirclePlayer::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

EBTNodeResult::Type UMyBTTask_CirclePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AiController = OwnerComp.GetAIOwner();
	ACharacter* ControlledCharacter = AiController->GetCharacter();

	FVector CirclingPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector("CirclingPosition");

	AiController->MoveToLocation(CirclingPosition, 5);

	FVector ControlledCharacterLocation = ControlledCharacter->GetActorLocation();
	FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();

	FRotator NewLookRotation = UKismetMathLibrary::FindLookAtRotation(ControlledCharacterLocation, PlayerLocation);

	ControlledCharacter->SetActorRotation(NewLookRotation);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
