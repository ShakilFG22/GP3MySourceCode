// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledCharacterComponent.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UPooledCharacterComponent::UPooledCharacterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// PoolLocation.Z = 1000.0f;
	// ...
}

APooledCharacter* UPooledCharacterComponent::SpawnPooledObject()
{
	for (APooledCharacter* PoolableChar : PooledCharacters)
	{
		if (PoolableChar != nullptr && PoolableChar->IsActive() == false)
		{
			PoolableChar->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableChar->SetLifeSpan(PooledCharacterLifeSpan);
			PoolableChar->SetActive(true);
			SpawnedCharacterIndexes.Add(PoolableChar->GetPoolIndex());
			return PoolableChar; 
		}
	}
	if (SpawnedCharacterIndexes.Num() > 0)
	{
		int PooledCharIndex = SpawnedCharacterIndexes[0];
		SpawnedCharacterIndexes.Remove(PooledCharIndex);
		APooledCharacter* PoolableChar = PooledCharacters[PooledCharIndex];

		if (PoolableChar != nullptr)
		{
			PoolableChar->SetActive(false);
			PoolableChar->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableChar->SetLifeSpan(PooledCharacterLifeSpan);
			PoolableChar->SetActive(true);
			SpawnedCharacterIndexes.Add(PoolableChar->GetPoolIndex());

			return PoolableChar;
		}
	}
	return nullptr;
}

APooledCharacter* UPooledCharacterComponent::SpawnPoolAtBegin()
{
	if (PooledCharacter != nullptr)
	{
		for (int i = 0; i < PoolSize; i++)
		{
			APooledCharacter* PooledChar = GetWorld()->SpawnActor<APooledCharacter>(PooledCharacter, PoolLocation, FRotator::ZeroRotator);
			if (PooledChar != nullptr)
			{
				PooledChar->SetActive(false);
				PooledChar->SetPoolIndex(i);
				PooledChar->OnPooledCharacterDelegateDespawn.AddDynamic(this, &UPooledCharacterComponent::OnPooledCharacterDelegateDespawn);
				UE_LOG(LogTemp, Warning, TEXT("SpawnedCharacterIndexes.Num(): %d"), SpawnedCharacterIndexes.Num());
				PooledChar->CharComp = this; //Creates a reference to this component
				PooledCharacters.Add(PooledChar);
			}
		}
	}
	return nullptr;
}


void UPooledCharacterComponent::OnPooledCharacterDelegateDespawn(APooledCharacter* PooledChar)
{
	SpawnedCharacterIndexes.Remove(PooledChar->GetPoolIndex());
}


// Called every frame
void UPooledCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

