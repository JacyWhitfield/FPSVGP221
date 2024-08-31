#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "AmmoPickup.generated.h"

UCLASS()
class FPSGAME_API AAmmoPickup : public APickup
{
    GENERATED_BODY()

public:
    AAmmoPickup();

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    int32 AmmoAmount;
};
