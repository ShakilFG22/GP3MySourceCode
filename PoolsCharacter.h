// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledCharacter.h"
#include "GameFramework/Actor.h"
#include "PoolsCharacter.generated.h"

UENUM(BlueprintType)
enum class TestEnum : uint8
{
	PoolMelee	UMETA(DisplayName = "PoolMelee"),
	PoolRanged	UMETA(DisplayName = "PoolRanged"),
	None		UMETA(DisplayName = "None")
};

UCLASS()
class GAMEPROJECT3_API APoolsCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolsCharacter();

	TMap<TSubclassOf<APooledCharacter>, TArray<APooledCharacter*>> PooledCharacterTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pools Character Category")
	TSubclassOf<APooledCharacter> PooledCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pools Character Category")
	int32 PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Pools Character Category")
	float PooledCharacterLifeSpan = 0.0f;



	
	
	UFUNCTION(BlueprintCallable, Category = "Pools Character Category")
	APooledCharacter* SpawnPooledObject(FTransform SpawnTransform);

	UFUNCTION(BlueprintCallable, Category = "Pools Character Category")
	APooledCharacter* PoolAtBegin();

	UFUNCTION()
	void OnPooledCharacterDelegateDespawn(APooledCharacter* PooledChar);

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooled Object Component Category") //Might not needed
	FVector PoolLocation = FVector(0.0f, 0.0f, 10000.0f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Pools Character Category")
	TArray<APooledCharacter*> PooledCharacters;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pools Character Category")
	TArray<int32> SpawnedCharacterIndexes;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bGateKeepPoolSize = false;
	
};
