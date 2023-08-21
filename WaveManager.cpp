// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "NiagaraComponent.h"


// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	PopulateSpawnLocations();
	InitializePools();
	StartWave();
}

void AWaveManager::PopulateSpawnLocations()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnLocationReference, OutActors);

	for (int i = 0; i < OutActors.Num(); i++)
	{
		SpawnLocations.Add(OutActors[i]->GetTransform());
	}
	
	RepopulateAvailableSpawnLocations();
}

void AWaveManager::RepopulateAvailableSpawnLocations()
{
	AvailableSpawnLocations.Append(SpawnLocations);
}

void AWaveManager::InitializePools()
{
	// Loops through the TMap storing the different pools for enemies and initializes them.
	
	for (auto Pool : EnemyPools)
	{
		Pool.Value->PoolAtBegin();
	}
}

FTransform AWaveManager::GetAvailableSpawnPosition()
{
	FTransform SpawnPos;
	
	if(AvailableSpawnLocations.Num() > 0)
	{
		SpawnPos =  AvailableSpawnLocations[0];
		AvailableSpawnLocations.RemoveAt(0);
	
		return SpawnPos;	
	}
	else
	{
		return SpawnPos;
	}
}

void AWaveManager::RemoveDeadEnemyFromWave(APooledCharacter* PooledCharacter)
{
	RemainingEnemiesAmount -= 1;
	PooledCharacter->OnPooledCharacterDelegateDespawn.RemoveDynamic(this, &AWaveManager::RemoveDeadEnemyFromWave);

	CurrentWaveEnemies.Remove(PooledCharacter);
	CurrentWaveEnemies.Shrink();
	
	if(RemainingEnemiesAmount == 0)
	{
		RepopulateAvailableSpawnLocations();

		OnWaveDone();
	}
}

void AWaveManager::StartSpawnVfx()
{
	UE_LOG(LogTemp, Warning, TEXT("StartSpawnVfx"));
	FEnemyWave CurrentWave = Waves[CurrentWaveIndex];

	int AmountOfVfxToStart = 0;
	
	for(int i = 0; i < CurrentWave.EnemiesToSpawn.Num(); i++)
	{
		for (int j = 0; j < CurrentWave.EnemiesToSpawn[i].AmountOfEnemies; j++)
		{
			AmountOfVfxToStart++;
		}
	}

	UNiagaraComponent* SpawnLocationVfx = nullptr;
	
	for(int i = 0; i < AmountOfVfxToStart; i++)
	{
		if(i >= AvailableSpawnLocations.Num())
		{
			break;
		}
		SpawnLocationVfx = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnVfx,AvailableSpawnLocations[i].GetLocation());
	}

	if(SpawnLocationVfx != nullptr)
	{
		SpawnLocationVfx->OnSystemFinished.AddDynamic(this, &AWaveManager::SpawnEnemyAfterVfxDone);
	}
}

void AWaveManager::SpawnEnemyAfterVfxDone(UNiagaraComponent* Test)
{

	FEnemyWave CurrentWave = Waves[CurrentWaveIndex];

	UE_LOG(LogTemp, Warning, TEXT("Wave num: %d"), Waves.Num());

	
	EEnemyType CurrentEnemyType;
	FEnemyToSpawn CurrentEnemyToSpawn;
	
	for(int i = 0; i < CurrentWave.EnemiesToSpawn.Num(); i++)
	{
		CurrentEnemyToSpawn = CurrentWave.EnemiesToSpawn[i];
		CurrentEnemyType = CurrentEnemyToSpawn.EnemyType;

		
		UE_LOG(LogTemp, Warning, TEXT("Current enemy type: %s"), *EnemyPools[CurrentEnemyType]->GetName());

		for (int j = 0; j < CurrentEnemyToSpawn.AmountOfEnemies; j++)
		{

			FTransform CurrentSpawnTransform = GetAvailableSpawnPosition();
			
			APooledCharacter* CurrentChar = EnemyPools[CurrentEnemyType]->SpawnPooledObject(CurrentSpawnTransform);
			
			if(CurrentChar == nullptr)
			{
				continue;
			}

			CurrentChar->OnPooledCharacterDelegateDespawn.AddDynamic(this, &AWaveManager::RemoveDeadEnemyFromWave);

			CurrentWaveEnemies.Add(CurrentChar);

			RemainingEnemiesAmount += 1;
			
		}
	}

	CurrentWaveIndex += 1;
}

void AWaveManager::StartWave()
{
	if(CurrentWaveIndex == Waves.Num())
	{
		OnLevelDone();
		return;
	}
	StartSpawnVfx();
}

