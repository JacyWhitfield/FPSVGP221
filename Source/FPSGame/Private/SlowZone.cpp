#include "SlowZone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/FPSCharacter.h"

ASlowZone::ASlowZone()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetBoxExtent(FVector(100.0f, 100.0f, 10.0f)); 
    RootComponent = BoxComponent;

 
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(RootComponent);
    StaticMeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.1f)); 

  
    StaticMeshComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object);

   
    StaticMeshComponent->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")).Object);

    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    StaticMeshComponent->SetVisibility(true);

    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASlowZone::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASlowZone::OnOverlapEnd);
}

void ASlowZone::BeginPlay()
{
    Super::BeginPlay();
}

void ASlowZone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASlowZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
    if (Character)
    {
        Character->ApplySlow(0.5f, 2.0f);
    }
}

void ASlowZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
    if (Character)
    {
        Character->EndSlow();
    }
}
