// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelComp = CreateDefaultSubobject<UStaticMeshComponent>("BarrelComp");
	BarrelComp->SetSimulatePhysics(true);
	BarrelComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = BarrelComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(BarrelComp);

	// Leaving this on applies small constant force via component 'tick' (Optional)
	RadialForceComp->SetAutoActivate(false);

	RadialForceComp->Radius = 750.0f;
	RadialForceComp->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other  objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	RadialForceComp->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	// add an on event binding function
	BarrelComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at gametime: 124.4" 
	///
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);

	// Detailed info on logging in ue4
	// https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-messages-to-yourself-during-runtime.html

}