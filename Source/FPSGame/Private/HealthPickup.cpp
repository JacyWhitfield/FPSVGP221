#include "HealthPickup.h"
#include "Player/FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AHealthPickup::AHealthPickup()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

   
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(CubeMesh.Object);
    }

    
    static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
    if (DefaultMaterial.Succeeded())
    {
        StaticMeshComponent->SetMaterial(0, DefaultMaterial.Object);
    }

 
    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    StaticMeshComponent->SetGenerateOverlapEvents(true);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    HealthAmount = 50.0f;
}

void AHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        PlayerCharacter->AddHealth(HealthAmount);
        Destroy();
    }
}

void AHealthPickup::BeginPlay()
{
    Super::BeginPlay();
}

void AHealthPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
