#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "FPSProjectile.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSGAME_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AFPSCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FPSCameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    USkeletalMeshComponent* FPSMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    FVector MuzzleOffset;

    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<class AFPSProjectile> ProjectileClass;

    UFUNCTION()
    void MoveForward(float Value);

    UFUNCTION()
    void MoveRight(float Value);

    UFUNCTION()
    void StartJump();

    UFUNCTION()
    void EndJump();

    UFUNCTION()
    void Fire();

    // Getter for health
    float GetHealth() const;

    // Getter for ammo
    int32 GetAmmo() const;

    // Function to add health
    void AddHealth(float HealthAmount);

    // Function to add ammo
    void AddAmmo(int32 AmmoAmount);

    // Function to apply slow effect
    void ApplySlow(float InSlowAmount, float SlowDuration);

    // Function to end slow effect
    void EndSlow();

private:
    float Health;
    int32 Ammo;
    float SlowAmount;

    FTimerHandle UnusedHandle;
};
