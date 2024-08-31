#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class FPSGAME_API AHealthPickup : public APickup
{
    GENERATED_BODY()

public:
    AHealthPickup();

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float HealthAmount;
};
