// Made by Max Ekberg.
// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

#include "HPComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// void AWeapon::SetMeshPointer(USkeletalMeshComponent* ReferencedMesh)
// {
// 	WeaponMesh = ReferencedMesh;
// }


float AWeapon::CalculateFinalStat(float StatBase, float MultiplicationModifier)
{
	return StatBase * MultiplicationModifier;
}

void AWeapon::SetActorsToIgnore(TArray<AActor*> ActorsToIgnore)
{
	IgnoreActors.Append(ActorsToIgnore);
	
}


void AWeapon::SetCanAttack(bool bNewValue)
{
	bCanAttack = bNewValue;
}

void AWeapon::SetCanAttackTrue()
{
	SetCanAttack(true);
}

void AWeapon::SetDontDamageTag(FName PassedTag)
{
	DontDamageTag = PassedTag;
}


void AWeapon::Attack()
{
	if (!bCanAttack)
	{
		return;
	}

	bCanAttack = false;

	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AWeapon::SetCanAttackTrue, AttackSpeed, false);

	Hits.Empty();
	GetHitTargets();

	if (Hits.IsEmpty())
	{
		return;
	}

	for (int i = 0; i < Hits.Num(); i++)
	{
		IHPInterface::Execute_ModifyHealth(Hits[i], CalculateFinalStat(Damage, 1), false);
	}
}

void AWeapon::GetHitTargets()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	//TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	
	TArray<AActor*> OutActors;

	float Radius = 250.0f;

	FVector SphereSpawnLocation = GetActorLocation();

	UClass* SeekClass = AActor::StaticClass();

	if(bDrawDebugSphere)
	{
		DrawDebugSphere(GetWorld(), SphereSpawnLocation, Radius, 8, FColor::Red, false, 5, 0, 2);
	}

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SphereSpawnLocation, Radius, TraceObjectTypes, SeekClass,
	                                              IgnoreActors, OutActors))
	{
		AActor* CurrentActor;

		TSet<UActorComponent*> ParentComponents;

		for (int i = 0; i < OutActors.Num(); i++)
		{
			CurrentActor = OutActors[i];

			if(CurrentActor->ActorHasTag(DontDamageTag))
			{
				continue;
			}
			
			ParentComponents.Append(CurrentActor->GetComponents());

			// UE_LOG(LogTemp, Warning, TEXT("Checking: %s, Amount of components: %d"), *CurrentActor->GetName(),
			//        ParentComponents.Num());
		}

		for (const auto& Component : ParentComponents)
		{
			if (Component->GetClass()->ImplementsInterface(UHPInterface::StaticClass()))
			{
				// UE_LOG(LogTemp, Warning, TEXT("Added: %s"), *Component->GetName());

				Hits.Add(Component);
			}
			else
			{
				// UE_LOG(LogTemp, Warning, TEXT("Child did not have HP: %s"), *Component->GetName());
			}
		}
	}
	else
	{
		// if (GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("No overlap found"));
		// }
	}

	Hits.Shrink();
}
