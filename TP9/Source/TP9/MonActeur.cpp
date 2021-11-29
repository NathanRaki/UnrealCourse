// Fill out your copyright notice in the Description page of Project Settings.


#include "MonActeur.h"

// Sets default values
AMonActeur::AMonActeur()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MyMesh->SetupAttachment(RootComponent);
	MyParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	MyParticleSystem->SetupAttachment(MyMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		MyMesh->SetStaticMesh(CubeVisualAsset.Object);
		MyMesh->SetRelativeLocation(FVector(0.0f));
	}

	ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse"));
	if (MeshMaterial.Succeeded())
	{
		MyMesh->SetMaterial(0, MeshMaterial.Object);
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("/Game/StarterContent/Particles/P_Sparks"));
	if (ParticleSystem.Succeeded())
	{
		MyParticleSystem->SetTemplate(ParticleSystem.Object);
	}
}

// Called when the game starts or when spawned
void AMonActeur::BeginPlay()
{
	Super::BeginPlay();
	
	FString nom = FString::Printf(TEXT("Actor Name : %s"), *(this->GetName()));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *nom);
}

// Called every frame
void AMonActeur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isStatic)
	{
		FVector NewLocation = GetActorLocation();
		FRotator NewRotation = GetActorRotation();
		float SpeedScale = VitesseDeplacement * DeltaTime;
		float RotationScale = VitesseRotation * DeltaTime;

		float RunningTime = GetGameTimeSinceCreation();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

		NewLocation.Z += DeltaHeight * SpeedScale;
		NewLocation.X += FMath::Sin(RunningTime) * (FMath::Rand() % 5) * SpeedScale;
		NewLocation.Y += FMath::Sin(RunningTime) * (FMath::Rand() % 5) * SpeedScale;

		NewRotation.Yaw = FMath::Sin(RunningTime) * 180 * RotationScale;

		SetActorLocation(NewLocation);
		SetActorRotation(NewRotation);
	}

	if (SparkEffect)
	{
		MyParticleSystem->Activate();
	}
	else
	{
		MyParticleSystem->Deactivate();
	}
}

bool AMonActeur::LeveCube(float Distance)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += Distance;
	SetActorLocation(NewLocation);
	return NewLocation.Z > 0;
}
