// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorToSpawn.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AActorToSpawn::AActorToSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��ü ����Ʈ ������Ʈ ����
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

	// ������Ʈ attach �� ������ ����
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetSimulatePhysics(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMeshComp->AttachToComponent(SphereComp, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleComp->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
	
	// ����ƽ�޽� ���缭 ���Ǿ� �ݰ��� �� �۰�
	SphereComp->SetSphereRadius(16.0f);

	// ���Ǿ� �ݰ濡 ���� ����ƽ�޽� Scale, Location ����
	StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -12.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));

	// ������ ���۸� ����� ������Ʈ ���ϴ� �κ��� X, �����Ϳ��� ����
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

