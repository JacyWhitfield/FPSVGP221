#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class FPSGAME_API APickup : public AActor
{
    GENERATED_BODY()

public:
    APickup();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
