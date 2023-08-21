// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PooledCharacter.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_MeleeEnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT3_API UBTTask_MeleeEnemyAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	UFUNCTION()
	void SetIsAttackingFalse(APooledCharacter* Controller);

protected:
	UBTTask_MeleeEnemyAttack();
	
	FTimerHandle AnimationTimerHandle;

	virtual void Attack(APooledCharacter* ControlledPawnCharacter, AAIController* AIController);

	
public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere)
	float AnimationPlayRate = 1.0f;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
