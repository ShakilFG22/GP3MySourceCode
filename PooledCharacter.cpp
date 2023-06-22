// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledCharacter.h"

#include "PooledCharacterComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APooledCharacter::APooledCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APooledCharacter::SetIsAttacking(bool bValue)
{
	UE_LOG(LogTemp, Warning, TEXT("IsAttacking: %s"), bValue ? TEXT("True") : TEXT("False"));
	bIsAttacking = bValue;
}

void APooledCharacter::Deactivate()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	SetIsAttacking(false);
	OnPooledCharacterDelegateDespawn.Broadcast(this);
	SetActive(false);
}

void APooledCharacter::SetActive(bool IsActive)
{
	bIsActive = IsActive;
	SetActorHiddenInGame(!IsActive);
	SetActorTickEnabled(IsActive);
	SetActorEnableCollision(IsActive);
	GetCharacterMovement()->GravityScale = IsActive ? 1.0f : 0.0f; //So It does not fall down before it get spawned

	OnSetActiveCalled(IsActive);
	
}

void APooledCharacter::SetLifeSpan(float LifeTime) { LifeSpan = LifeTime; }

void APooledCharacter::SetPoolIndex(int32 Index) { PoolIndex = Index; }

bool APooledCharacter::IsActive()  { return bIsActive; }

int APooledCharacter::GetPoolIndex() { return PoolIndex; }

// Called when the game starts or when spawned
void APooledCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APooledCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APooledCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APooledCharacter::StartAttackTimer(float TimerLength)
{
	SetIsAttacking(true);
	
	FTimerDelegate TimerDelegate;

	TimerDelegate.BindUFunction(this, "SetIsAttacking", false);
	
	GetWorldTimerManager().SetTimer(AnimationTimerHandle, TimerDelegate,GetWorld()->DeltaTimeSeconds, false, TimerLength);
}

