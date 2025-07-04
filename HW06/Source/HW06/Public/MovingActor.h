// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class HW06_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Moving|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving|Components")
	UStaticMeshComponent* StaticMeshComp;

	FVector StartLocation;
	FVector EndLocation;
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform Settings")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform Settings")
	FVector MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	// 얼마나 가까우면 목표에 도달했다고 판단할지 수치
	float TargetReachedTolerance;

public:	

	UFUNCTION(BlueprintCallable, Category="Moving|Actions")
	void MoveActor(float DeltaTime);


	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
