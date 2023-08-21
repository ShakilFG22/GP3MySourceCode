// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_EnemyChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT3_API UMyBTTask_EnemyChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UMyBTTask_EnemyChasePlayer();
	
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	float ValidAttackDistance = 100.0f;
	
public:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
