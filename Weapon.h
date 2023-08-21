
// Made by Max Ekberg.
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class GAMEPROJECT3_API AWeapon : public AActor
{
	GENERATED_BODY()


	// UFUNCTION(BlueprintCallable)
	// void SetMeshPointer(USkeletalMeshComponent* ReferencedMesh);
	
	// Trying to figure out how to properly do this for hitboxes.
	// USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	float Damage= 10.0f;

	UPROPERTY(EditAnywhere)
	float AttackSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bDrawDebugSphere = false;

	bool bCanAttack = true;

	FName DontDamageTag;


	// TODO: Figure out how we're doing modifiers design wise.
	
	UFUNCTION(BlueprintCallable)
	float CalculateFinalStat(float StatBase, float MultiplicationModifier);

	void GetHitTargets();

	UFUNCTION(BlueprintCallable)
	void SetCanAttack(bool bNewValue);

	void SetCanAttackTrue();

	UFUNCTION(BlueprintCallable)
	void SetDontDamageTag(FName PassedTag);
	
	UPROPERTY()
	TArray<UActorComponent*> Hits;

	FTimerHandle AttackTimerHandle;

	TArray<AActor*> IgnoreActors;

	UFUNCTION(BlueprintCallable)
	void SetActorsToIgnore(TArray<AActor*> ActorsToIgnore);
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UFUNCTION(BlueprintCallable)
	void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
