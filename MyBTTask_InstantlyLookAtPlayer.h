// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "GameFramework/Character.h"
#include "MyBTTask_InstantlyLookAtPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT3_API UMyBTTask_InstantlyLookAtPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	
	FRotator FindNewLookDirection(ACharacter* ControlledCharacter, ACharacter* TargetCharacter);
	
	void SetNewRotation(ACharacter* CharToRotate, FRotator FinalRotation);

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
