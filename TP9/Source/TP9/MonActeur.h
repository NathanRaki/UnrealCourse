// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "MonActeur.generated.h"

UCLASS()
class TP9_API AMonActeur : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MyMesh;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* MyParticleSystem;

protected:
	virtual void BeginPlay() override;

public:
	AMonActeur();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool LeveCube(float Distance);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float VitesseDeplacement = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float VitesseRotation = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool isStatic = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	bool SparkEffect = false;

};
