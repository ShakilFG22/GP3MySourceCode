// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_EnemyChasePlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UMyBTTask_EnemyChasePlayer::UMyBTTask_EnemyChasePlayer()
{
	NodeName = "Chase Player";
}

void UMyBTTask_EnemyChasePlayer::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMyBTTask_EnemyChasePlayer::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

EBTNodeResult::Type UMyBTTask_EnemyChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AAIController* AiController = OwnerComp.GetAIOwner();

	ValidAttackDistance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat("ValidAttackDistance");

	const EPathFollowingRequestResult::Type MoveResult = AiController->MoveToActor(PlayerActor, ValidAttackDistance);

	switch (MoveResult)
	{
	case EPathFollowingRequestResult::Failed:
		UE_LOG(LogTemp, Warning, TEXT("Move Failed"));
		break;

	case EPathFollowingRequestResult::AlreadyAtGoal:
		UE_LOG(LogTemp, Warning, TEXT("Move Already At Goal"));
		break;
		
	case EPathFollowingRequestResult::RequestSuccessful:
		UE_LOG(LogTemp, Warning, TEXT("Move Successful"));
		break;
		
	default:
		UE_LOG(LogTemp, Warning, TEXT("Move null"));
		break;
	}
	
	if(MoveResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetInAttackRange", true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("TargetInAttackRange", false);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
