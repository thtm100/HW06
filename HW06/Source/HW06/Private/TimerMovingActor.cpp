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

	// �޽� ����, ��Ƽ������ �����Ϳ��� ����

	/*OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(SceneRoot);
	OverlapBox->SetGenerateOverlapEvents(true);*/

	// �ڼ��� ��ġ�� �����Ϳ��� ����
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
			//2.0f	// ù ���� �� ���ð�
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
	/* Timer ���� �� ���Ŀ��� MoveActor�� ���ھ��� void Ÿ���Լ��� �ؾ��ϱ� ������
	* �� �Լ� ���ο� DeltaTime�� ������ �� �ִ� �Լ��� ���
	*/
	float DeltaTime = GetWorld()->GetDeltaSeconds();

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

// ������ ��� �� �����
void ATimerMovingActor::Disappear()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bDisappeared = true;

	// ����� �� �ٽ� ��Ÿ���� �� Ÿ�̸� ����
	FTimerHandle ReviveTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		ReviveTimerHandle,
		this,
		&ATimerMovingActor::Appear,
		2.5f,
		false // �� ���� ����
	);
}

// ������� �ٽ� ��Ÿ���� ���ֱ� ���� �Լ�
void ATimerMovingActor::Appear()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bDisappeared = false;
}

// ���� ���� �Լ�
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
