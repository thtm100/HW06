// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "Components/BoxComponent.h"
#include "TimerMovingActor.generated.h"

UCLASS()
class HW06_API ATimerMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerMovingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimerMoving|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerMoving|Components")
	UStaticMeshComponent* StaticMeshComp;

	FVector StartLocation;
	FVector EndLocation;
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	// 얼마나 가까우면 목표에 도달했다고 판단할지 수치
	float TargetReachedTolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	// 액터 이동에 쓰이는 타이머 간격 
	float MoveDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	// 액터 랜덤 이동에 쓰이는 타이머 간격 
	float WarpDuration;
	
	// 액터가 사라진 상태인지 확인하는 변수
	bool bDisappeared;

	// 랜덤 워프 범위를 위한 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warp Settings")
	float RandParamA;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warp Settings")
	float RandParamB;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimerMoving|Components")
	UBoxComponent* OverlapBox;*/
public:	

	UFUNCTION(BlueprintCallable, Category = "TimerMove|Actions")
	void MoveActor();

	UFUNCTION(BlueprintCallable, Category = "TimerMove|Actions")
	void Disappear();

	UFUNCTION(BlueprintCallable, Category = "TimerMove|Actions")
	void Appear();

	/*UFUNCTION(BlueprintCallable, Category = "TimerMove|Actions")
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);*/

	UFUNCTION(BlueprintCallable, Category = "TimerMove|Actions")
	void RandomWarp();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
