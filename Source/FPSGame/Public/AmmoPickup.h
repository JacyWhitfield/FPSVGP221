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
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    int32 AmmoAmount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
    UStaticMeshComponent* StaticMeshComponent;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
