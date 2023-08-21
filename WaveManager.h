// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnLocation.h"
#include "PoolsCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "WaveManager.generated.h"

UENUM()
enum class EEnemyType : uint8
{
	None,
	SmallMeleeEnemy UMETA(DisplayName = "SmallMeleeEnemy"),
	MeleeEnemy UMETA(DisplayName = "MeleeEnemy"),
	BigMeleeEnemy UMETA(DisplayName = "BigMeleeEnemy"),
	RangedEnemy UMETA(DisplayName = "RangedEnemy"),
	BigRangedEnemy UMETA(DisplayName = "BigRangedEnemy")
};

USTRUCT()
struct FEnemyToSpawn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	EEnemyType EnemyType;

	UPROPERTY(EditAnywhere)
	int AmountOfEnemies;
};


USTRUCT()
struct FEnemyWave
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FEnemyToSpawn> EnemiesToSpawn;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpawnVfxSystemFinished, EEnemyType, CurrentEnemyType,AActor*, CurrentEnemySpawnLocation);

UCLASS()
class GAMEPROJECT3_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
	void PopulateSpawnLocations();

	void RepopulateAvailableSpawnLocations();

	void InitializePools();

	FTransform GetAvailableSpawnPosition();

	UFUNCTION()
	void RemoveDeadEnemyFromWave(APooledCharacter* PooledCharacter);
	void StartSpawnVfx();

	UFUNCTION()
	void SpawnEnemyAfterVfxDone(UNiagaraComponent* Test);
	
	


	UPROPERTY(EditAnywhere)
	UNiagaraSystem* SpawnVfx;

public:	
	// Sets default values for this actor's properties
	AWaveManager();

	// UPROPERTY(EditAnywhere)
	TArray<APooledCharacter*> CurrentWaveEnemies;
	
	FOnSpawnVfxSystemFinished FOnSpawnVfxSystemFinished;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	int CurrentWaveIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category = "WaveManager Category")
	int RemainingEnemiesAmount = 0;
	
	UPROPERTY(EditAnywhere)
	TArray<FEnemyWave> Waves;	

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EEnemyType>, APoolsCharacter*> EnemyPools;

	// UPROPERTY(EditAnywhere)
	TArray<FTransform> SpawnLocations;
	
	TArray<FTransform> AvailableSpawnLocations;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnLocationReference;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWaveDone();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLevelDone();
	
	UFUNCTION(BlueprintCallable)
	void StartWave();

	
	
};
