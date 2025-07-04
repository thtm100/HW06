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
	// �󸶳� ������ ��ǥ�� �����ߴٰ� �Ǵ����� ��ġ
	float TargetReachedTolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	// ���� �̵��� ���̴� Ÿ�̸� ���� 
	float MoveDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	// ���� ���� �̵��� ���̴� Ÿ�̸� ���� 
	float WarpDuration;
	
	// ���Ͱ� ����� �������� Ȯ���ϴ� ����
	bool bDisappeared;

	// ���� ���� ������ ���� ����
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
