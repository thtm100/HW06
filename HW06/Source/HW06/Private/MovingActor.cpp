// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// �޽� ����, ��Ƽ������ �����Ϳ����� ���� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Potion_A.SM_Potion_A"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Debuff_A.M_Debuff_A"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	
	// �ڼ��� ��ġ�� �����Ϳ��� ����
	MoveSpeed = FMath::RandRange(0, 100);
	MaxRange = FVector(FMath::RandRange(0, 100), FMath::RandRange(0, 100), FMath::RandRange(0, 100));
	TargetReachedTolerance = 1.0f;
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + MaxRange;
	TargetLocation = EndLocation;
}

void AMovingActor::MoveActor(float DeltaTime)
{
	// ���� ��ġ���� ��ǥ �������� ���� ���͸� ���ϰ� ����ȭ
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
															// ����ȭ: ���� ������ 1��

	// �̵��� ���: ���� * �ӵ� * DeltaTime
	FVector Movement = Direction * MoveSpeed * DeltaTime;

	SetActorLocation(GetActorLocation() + Movement);

	// ��ǥ�� ����������� Ȯ��
	if (FVector::DistSquared(GetActorLocation(), TargetLocation) <
		FMath::Square(TargetReachedTolerance))
	{
		// ��ǥ�� �����ߴٸ� ��ǥ ���� ����
		if (TargetLocation.Equals(EndLocation, TargetReachedTolerance))
		{
			TargetLocation = StartLocation;
		}
		// StartLocation �� �����ߴٸ�, 
		// �ٽ� �� ������ ��ĥ �� TargetLocation�� EndLocation�� �ƴ϶�� ������ ����� �´�
		else
		{
			TargetLocation = EndLocation;
		}
	}
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveActor(DeltaTime);

}

