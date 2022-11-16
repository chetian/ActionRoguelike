// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{
 	// create mesh comp
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// set mesh comp as root comp (see heirachy inside a blueprint)
	RootComponent = MeshComp;
	// create subcomp AttributeComp
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	// bind AttributeComp to function using the AddDynamic function
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);
}

void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// do something when health is changed:
	// this is working because we bind using AddDynamic in the constructor
	// we know MeshComp is not null because we just created it in the constructor...
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

