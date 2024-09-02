#include "AmmoPickup.h"
#include "Player/FPSCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AAmmoPickup::AAmmoPickup()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(SphereMesh.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
    if (DefaultMaterial.Succeeded())
    {
        StaticMeshComponent->SetMaterial(0, DefaultMaterial.Object);
    }

    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    StaticMeshComponent->SetGenerateOverlapEvents(true);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    AmmoAmount = 30;
}

void AAmmoPickup::BeginPlay()
{
    Super::BeginPlay();
}

void AAmmoPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAmmoPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        PlayerCharacter->AddAmmo(AmmoAmount);
        Destroy();
    }
}
