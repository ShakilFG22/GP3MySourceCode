// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolsCharacter.h"

// Sets default values
APoolsCharacter::APoolsCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}



APooledCharacter* APoolsCharacter::SpawnPooledObject(FTransform SpawnTransform)
{

	if(!SpawnTransform.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("No available spawn position"))
		return nullptr;
	}
	
	for (APooledCharacter* SpawnChar : PooledCharacters)
	{
		if (SpawnChar != nullptr && SpawnChar->IsActive() == false)
		{
			SpawnChar->TeleportTo(SpawnTransform.GetLocation(), FRotator::ZeroRotator);
			SpawnChar->SetLifeSpan(PooledCharacterLifeSpan);
			SpawnChar->SetActive(true);
			SpawnedCharacterIndexes.Add(SpawnChar->GetPoolIndex());
			return SpawnChar;
		}
	}
	if (SpawnedCharacterIndexes.Num() > 0)
	{
		int SpawnCharIndex = SpawnedCharacterIndexes[0];
		SpawnedCharacterIndexes.Remove(SpawnCharIndex);
		APooledCharacter* SpawnChar = PooledCharacters[SpawnCharIndex];
		
		if (SpawnChar != nullptr)
		{
			SpawnChar->TeleportTo(SpawnTransform.GetLocation(), FRotator::ZeroRotator);
			SpawnChar->SetLifeSpan(PooledCharacterLifeSpan);
			SpawnChar->SetActive(true);
			SpawnedCharacterIndexes.Add(SpawnChar->GetPoolIndex());

			return SpawnChar;
		}
	}
	return nullptr;
}

APooledCharacter* APoolsCharacter::PoolAtBegin()
{
	if (PooledCharacter != nullptr)
	{
		for (int i = 0; i < PoolSize; i++)
		{
			APooledCharacter* PoolsChar = GetWorld()->SpawnActor<APooledCharacter>(PooledCharacter, PoolLocation, FRotator::ZeroRotator);
			if (PoolsChar != nullptr)
			{
				PoolsChar->SetActive(false);
				PoolsChar->SetPoolIndex(i);
				PoolsChar->OnPooledCharacterDelegateDespawn.AddDynamic(this, &APoolsCharacter::OnPooledCharacterDelegateDespawn);
				PooledCharacters.Add(PoolsChar);
			
				
				PoolsChar->PoolsChar = this; //Creates a reference to this component. Not using currently, but good to have in case.
			}
		}
		
	}
	return nullptr;
}

void APoolsCharacter::OnPooledCharacterDelegateDespawn(APooledCharacter* PooledChar)
{
	SpawnedCharacterIndexes.Remove(PooledChar->GetPoolIndex());
}

// Called when the game starts or when spawned
void APoolsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoolsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

