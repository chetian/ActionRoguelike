// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;

	// Directly set bool instead of going through SetReplicates(true) within constructor,
	// Only use SetReplicates() outside constructor
	bReplicates = true;
}


// Called when the user presses "E" to interact
void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	// Pitch the lid up to TargetPitch when it is interacted with
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
	UE_LOG(LogTemp, Warning, TEXT("Interact_Implementation: SetRelativeRotation"));
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

