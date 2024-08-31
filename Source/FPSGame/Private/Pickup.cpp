#include "Pickup.h"
#include "Player/FPSCharacter.h"

APickup::APickup()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APickup::BeginPlay()
{
    Super::BeginPlay();
}

void APickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        // Logic for what happens when the player overlaps with the pickup
        Destroy(); // Destroy the pickup after collection
    }
}
