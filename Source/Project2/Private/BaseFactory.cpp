// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFactory.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseFactory::ABaseFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	BuildingMesh->SetupAttachment(RootComponent);

	HitCollider = CreateDefaultSubobject<UBoxComponent>("HitCollider");
	HitCollider->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	
}

void ABaseFactory::TakeDamage(FDamageData Damage)
{
	if (HealthComponent)
		HealthComponent->TakeDamage(Damage);
}

// Called when the game starts or when spawned
void ABaseFactory::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseFactory::OnTankSpawnTick, SpawnInterval, true);
}

// Called every frame
void ABaseFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseFactory::OnTankSpawnTick()
{
	auto Tank = GetWorld()->SpawnActorDeferred<AEnemyTank_Pawn>(TankClass, SpawnPoint->GetComponentTransform());
	Tank->Waypoints = Waypoints;
	TanksSpawned++;
	Tank->Number = TanksSpawned;
	UGameplayStatics::FinishSpawningActor(Tank, SpawnPoint->GetComponentTransform());
}

