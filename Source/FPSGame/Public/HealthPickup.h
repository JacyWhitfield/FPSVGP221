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
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float HealthAmount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
    UStaticMeshComponent* StaticMeshComponent;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
