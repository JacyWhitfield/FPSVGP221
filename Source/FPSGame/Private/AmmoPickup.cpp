#include "AmmoPickup.h"
#include "Player/FPSCharacter.h"

AAmmoPickup::AAmmoPickup()
{
    AmmoAmount = 30; // Example value
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
