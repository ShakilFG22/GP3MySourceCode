// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledCharacter.h"
#include "Components/ActorComponent.h"
#include "PooledCharacterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROJECT3_API UPooledCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPooledCharacterComponent();
	
	//UPROPERTY()
	UPROPERTY(EditAnywhere, Category="Pooled Object Component Category")
	TSubclassOf<APooledCharacter> PooledCharacter;

	UPROPERTY(EditAnywhere, Category = "Pooled Object Component Category")
	int32 PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Pooled Object Component Category")
	float PooledCharacterLifeSpan = 0.0f;


	//UFUNCTION()
	UFUNCTION(BlueprintCallable, Category = "Pooled Object Component Category")
	APooledCharacter* SpawnPooledObject();

	UFUNCTION(BlueprintCallable, Category = "Pooled Object Component Category")
	APooledCharacter* SpawnPoolAtBegin();

	UFUNCTION(BlueprintImplementableEvent)
	void EnemyWaveEvent();

	UFUNCTION()
	void OnPooledCharacterDelegateDespawn(APooledCharacter* PooledChar);

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooled Object Component Category") //Might not needed
	FVector PoolLocation = FVector(0.0f, 0.0f, 1000.0f);

protected:
	// TArray<APooledCharacter*> PooledCharacters;
	// TArray<int32> SpawnedCharacterIndexes;
public:	
	TArray<APooledCharacter*> PooledCharacters;
	UPROPERTY(BlueprintReadWrite, Category = "Pooled Object Component Category")
	TArray<int32> SpawnedCharacterIndexes;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool bAllEnemiesIsDead = false;

};
