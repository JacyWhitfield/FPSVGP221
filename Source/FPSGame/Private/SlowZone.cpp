#include "SlowZone.h"
#include "Components/BoxComponent.h"
#include "Player/FPSCharacter.h"

// Sets default values
ASlowZone::ASlowZone()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    BoxComponent->SetCollisionProfileName("Trigger");
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASlowZone::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASlowZone::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASlowZone::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
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
