// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorSpawner.h"
#include "Components/BoxComponent.h"
#include "ActorToSpawn.h"
#include "MovingActor.h"
#include "RotatingActor.h"

// Sets default values
AMyActorSpawner::AMyActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void AMyActorSpawner::SpawnActor()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	FVector RandomLocation = FVector(FMath::RandRange(-2000, 2000), FMath::RandRange(-2000, 2000), FMath::RandRange(-2000, 2000));
	FRotator RandomRotation = FRotator(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), FMath::RandRange(-100, 100));
	FVector SpawnScale = FVector(0.2f, 0.2f, 0.2f);

	AActor* SpawnedActor = nullptr;
	if (FMath::RandBool())
	{
		SpawnedActor = GetWorld()->SpawnActor<AMovingActor>(SpawnLocation + RandomLocation, SpawnRotation + RandomRotation);
	}
	else
	{
		SpawnedActor = GetWorld()->SpawnActor<ARotatingActor>(SpawnLocation + RandomLocation, SpawnRotation + RandomRotation);
	}

	if (SpawnedActor)
	{
		SpawnedActor->SetActorScale3D(SpawnScale);
	}
}

// Called when the game starts or when spawned
void AMyActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

