// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerMovingActor.h"

// Sets default values
ATimerMovingActor::ATimerMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// 메시 에셋, 머티리얼은 에디터에서 설정

	/*OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(SceneRoot);
	OverlapBox->SetGenerateOverlapEvents(true);*/

	// 자세한 수치는 에디터에서 설정
	MoveSpeed = 0.0f;
	MaxRange = FVector::ZeroVector;
	TargetReachedTolerance = 1.0f;
	MoveDuration = 0.01f;
	WarpDuration = 3.0f;
	RandParamA = -500.0f;
	RandParamB = 500.0f;
}

// Called when the game starts or when spawned
void ATimerMovingActor::BeginPlay()
{
	Super::BeginPlay();

	bDisappeared = false;
	
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + MaxRange;
	TargetLocation = EndLocation;

	FTimerHandle MoveTimerHandle;
	if (!bDisappeared)
	{
		GetWorld()->GetTimerManager().SetTimer(
			MoveTimerHandle,
			this,
			&ATimerMovingActor::MoveActor,
			MoveDuration,
			true
			//2.0f	// 첫 시작 후 대기시간
		);
	}
	FTimerHandle WarpTimerHandle;
	if (!bDisappeared)
	{
		GetWorld()->GetTimerManager().SetTimer(
			WarpTimerHandle,
			this,
			&ATimerMovingActor::RandomWarp,
			WarpDuration,
			true
		);
	}

	/*OverlapBox->OnComponentBeginOverlap.AddDynamic(this,
		&ATimerMovingActor::OnOverlapBegin);*/

	FTimerHandle DeathTimerHandle;
	if (!bDisappeared)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DeathTimerHandle,
			this,
			&ATimerMovingActor::Disappear,
			2.5f,
			true
		);
	}
			
}

void ATimerMovingActor::MoveActor()
{
	/* Timer 지금 이 형식에선 MoveActor를 인자없는 void 타입함수로 해야하기 때문에
	* 이 함수 내부에 DeltaTime을 가져올 수 있는 함수를 사용
	*/
	float DeltaTime = GetWorld()->GetDeltaSeconds();

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

// 밟으면 잠시 뒤 사라짐
void ATimerMovingActor::Disappear()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bDisappeared = true;

	// 사라질 때 다시 나타나게 할 타이머 설정
	FTimerHandle ReviveTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		ReviveTimerHandle,
		this,
		&ATimerMovingActor::Appear,
		2.5f,
		false // 한 번만 실행
	);
}

// 사라졌다 다시 나타나게 해주기 위한 함수
void ATimerMovingActor::Appear()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bDisappeared = false;
}

// 랜덤 워프 함수
void ATimerMovingActor::RandomWarp()
{
	FVector RandomLocation = FVector(
		FMath::RandRange(RandParamA, RandParamB), FMath::RandRange(RandParamA, RandParamB), FMath::RandRange(RandParamA, RandParamB));
	SetActorLocation(StartLocation + RandomLocation);
}

//void ATimerMovingActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
//	const FHitResult& SweepResult)
//{
//	if (OtherActor && OtherActor->ActorHasTag(TEXT("Player")))
//	{
//		FTimerHandle DeathTimerHandle;
//		GetWorld()->GetTimerManager().SetTimer(
//			DeathTimerHandle,
//			this,
//			&ATimerMovingActor::Disappear,
//			2.5f,
//			false
//		);
//	}
//}

// Called every frame
void ATimerMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
