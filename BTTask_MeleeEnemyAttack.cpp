// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeEnemyAttack.h"
#include "PooledCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "AIController.h"
#include "Chaos/CollisionResolutionUtil.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_MeleeEnemyAttack::UBTTask_MeleeEnemyAttack()
{
	NodeName = "Attack";
}

void UBTTask_MeleeEnemyAttack::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTTask_MeleeEnemyAttack::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}


void UBTTask_MeleeEnemyAttack::Attack(APooledCharacter* ControlledPawnCharacter, AAIController* AIController)
{

	AttackAnim = Cast<UAnimMontage>(AIController->GetBlackboardComponent()->GetValueAsObject("AttackAnim"));

	if(AttackAnim == nullptr)
	{
		return;
	}
	
	FVector PlayerLocation =  UGameplayStatics::GetPlayerPawn(ControlledPawnCharacter->GetWorld(), 0)->GetActorLocation();
	FVector ControlledPawnLocation = ControlledPawnCharacter->GetActorLocation();
	PlayerLocation.Z = ControlledPawnLocation.Z;
	FRotator NewFacingRotation = UKismetMathLibrary::FindLookAtRotation(ControlledPawnLocation, PlayerLocation);

	ControlledPawnCharacter->FaceRotation(NewFacingRotation, 0.0f);
	ControlledPawnCharacter->PlayAnimMontage(AttackAnim, AnimationPlayRate);
	
	const float AnimLength = AttackAnim->GetPlayLength();

	ControlledPawnCharacter->StartAttackTimer(AnimLength);
	
}

void UBTTask_MeleeEnemyAttack::SetIsAttackingFalse(APooledCharacter* ControlledCharacter)
{
	ControlledCharacter->SetIsAttacking(false);
}

EBTNodeResult::Type UBTTask_MeleeEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const Controller = OwnerComp.GetAIOwner();

	APooledCharacter* ControlledCharacter = Cast<APooledCharacter>(Controller->GetCharacter());

	if(Controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	if(!ControlledCharacter->bIsAttacking)
	{
		ControlledCharacter->SetIsAttacking(true);
		Attack(ControlledCharacter, Controller);
	}

	Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("TargetInAttackRange"), false);

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
