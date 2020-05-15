// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnLib.h"

// Sets default values for this component's properties
USpawnLib::USpawnLib()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USpawnLib::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void USpawnLib::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor *USpawnLib::MySpawnActor(const FString &ClassName, FTransform actorTransform)
{
	UClass *asActor = nullptr;
	AActor *oSpawnedActor = nullptr;
	bool bIsOk = false;

	UClass *FoundClass = LoadObject<UClass>(NULL, *ClassName, NULL, LOAD_None, NULL);

	if (FoundClass->IsChildOf(AActor::StaticClass()))
	{
		bIsOk = true;
	}
	else
	{
		FoundClass = nullptr;
		bIsOk = false;
	}

	if (bIsOk)
	{
		asActor = DynamicMetaCast(AActor::StaticClass(), FoundClass);
		bIsOk = (asActor != nullptr);
	}

	if (bIsOk)
	{
		AActor *oStartSpawnedActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(
			this,
			asActor,
			actorTransform,
			ESpawnActorCollisionHandlingMethod::Undefined,
			((AActor *)nullptr));

		oSpawnedActor = UGameplayStatics::FinishSpawningActor (
			oStartSpawnedActor,
			actorTransform
		);
	}

	return oSpawnedActor;
}
