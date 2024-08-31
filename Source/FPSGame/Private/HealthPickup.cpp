#include "HealthPickup.h"
#include "Player/FPSCharacter.h"

AHealthPickup::AHealthPickup()
{
    HealthAmount = 50.0f; // Example value
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
