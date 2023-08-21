// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Roam.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"

UMyBTTask_Roam::UMyBTTask_Roam()
{
	NodeName = "Roam";
}

void UMyBTTask_Roam::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMyBTTask_Roam::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

EBTNodeResult::Type UMyBTTask_Roam::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AiController = OwnerComp.GetAIOwner();
	const ACharacter* ControlledCharacter = AiController->GetCharacter();

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	FNavLocation NewMovementLocation;
	
	NavSystem->GetRandomPointInNavigableRadius(ControlledCharacter->GetActorLocation(), 1000,NewMovementLocation);

	AiController->MoveToLocation(NewMovementLocation.Location, 100);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
