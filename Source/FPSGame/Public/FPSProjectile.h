#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class FPSGAME_API AFPSProjectile : public AActor
{
    GENERATED_BODY()

public:
    AFPSProjectile();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float BulletSpeed = 4000;

    UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
    UStaticMeshComponent* ProjectileMeshComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
    UMaterialInstanceDynamic* ProjectileMaterialInstance;

    UFUNCTION()
    void FireInDirection(const FVector& ShootDirection);

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
