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
	FVector RandomLocation = FVector(FMath::RandRange(-3000, 3000), FMath::RandRange(-3000, 3000), FMath::RandRange(-3000, 3000));
	FVector RandomRotation = FVector(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), FMath::RandRange(-100, 100));

	GetWorld()->SpawnActor<AActorToSpawn>(SpawnLocation, SpawnRotation);
	GetWorld()->SpawnActor<AMovingActor>(SpawnLocation, SpawnRotation);
	GetWorld()->SpawnActor<ARotatingActor>(SpawnLocation, SpawnRotation);
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

