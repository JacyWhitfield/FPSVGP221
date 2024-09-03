#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSGAME_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFPSCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void StartJump();
    void EndJump();
    void Fire();

    float GetHealth() const;
    int32 GetAmmo() const;

    void AddHealth(float HealthAmount);
    void AddAmmo(int32 AmmoAmount);
    void ApplySlow(float SlowAmount, float SlowDuration);
    void EndSlow();
    void RestoreOriginalSpeed();

private:
    UPROPERTY(EditAnywhere)
    float Health;

    UPROPERTY(EditAnywhere)
    int32 Ammo;

    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* FPSCameraComponent;

    UPROPERTY(VisibleAnywhere)
    class USkeletalMeshComponent* FPSMesh;

    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<class AFPSProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Combat")
    FVector MuzzleOffset;

    float SlowAmount = 0.0f;
    float OriginalSpeed = 600.0f;  

    FTimerHandle UnusedHandle;
};
