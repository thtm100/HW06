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

	// 메시 에셋, 머티리얼은 에디터에서도 설정 가능
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/ParagonProps/Agora/Props/Meshes/Mid_Lane_Platforms_1c.Mid_Lane_Platforms_1c"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/ParagonProps/Agora/Props/Materials/M_Rock_Formation_Strip_C.M_Rock_Formation_Strip_C"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	
	//StaticMeshComp->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));
	// 자세한 수치는 에디터에서 설정
	MoveSpeed = FMath::RandRange(-100, 100);
	MaxRange = FVector(FMath::RandRange(-1000, 1000), FMath::RandRange(-1000, 1000), FMath::RandRange(-1000, 1000));
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
	// 현재 위치에서 목표 지점까지 방향 벡터를 구하고 정규화
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
															// 정규화: 벡터 단위를 1로

	// 이동량 계산: 방향 * 속도 * DeltaTime
	FVector Movement = Direction * MoveSpeed * DeltaTime;

	SetActorLocation(GetActorLocation() + Movement);

	// 목표에 가까워졌는지 확인
	if (FVector::DistSquared(GetActorLocation(), TargetLocation) <
		FMath::Square(TargetReachedTolerance))
	{
		// 목표에 도달했다면 목표 지점 변경
		if (TargetLocation.Equals(EndLocation, TargetReachedTolerance))
		{
			TargetLocation = StartLocation;
		}
		// StartLocation 에 도달했다면, 
		// 다시 이 과정을 거칠 때 TargetLocation이 EndLocation이 아니라면 어차피 여기로 온다
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

