// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "PooledCharacterComponent.h"
#include "GameFramework/Character.h"
#include "Delegates/Delegate.h"
#include "PooledCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledCharacterDelegateDespawn, APooledCharacter*, PooledCharacter);

UCLASS()
class GAMEPROJECT3_API APooledCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APooledCharacter();
	
	FOnPooledCharacterDelegateDespawn OnPooledCharacterDelegateDespawn;

	UFUNCTION(BlueprintCallable, Category="Pooled Character Category")
	void Deactivate();

	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int32 Index);
	int GetPoolIndex();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSetActiveCalled(bool IsActive);

	UFUNCTION(BlueprintImplementableEvent)
	void WaveEvent();

	bool IsActive();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsActive;
	float LifeSpan = 0.0f;
	int32 PoolIndex; // = -1;

	FTimerHandle LifeSpanTimerHandle;
public:

	class UPooledCharacterComponent* CharComp; //Needs to have class in front otherwise errors.
	class APoolsCharacter* PoolsChar;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetIsAttacking(bool bValue);


	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAttacking = false;

	FTimerHandle AnimationTimerHandle;
	
	void StartAttackTimer(float TimerLength);

private:
	
};
