// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorToSpawn.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AActorToSpawn::AActorToSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 자체 디폴트 컴포넌트 생성
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

	// 컴포넌트 attach 및 피직스 생성
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetSimulatePhysics(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMeshComp->AttachToComponent(SphereComp, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleComp->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
	
	// 스태틱메시 맞춰서 스피어 반경을 더 작게
	SphereComp->SetSphereRadius(16.0f);

	// 스피어 반경에 맞춰 스태틱메시 Scale, Location 설정
	StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -12.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));

	// 생성자 헬퍼를 사용해 컴포넌트 정하는 부분은 X, 에디터에서 설정
}

// Called when the game starts or when spawned
void AActorToSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

