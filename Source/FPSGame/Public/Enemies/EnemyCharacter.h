#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class FPSGAME_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    void Shoot();

    UFUNCTION()
    void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

private:
    FTimerHandle ShootingTimer;

    float Health;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<class AFPSProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float ShootingRange = 1000.0f;

    bool IsPlayerInRange();

    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    UAISenseConfig_Sight* SightConfig;
};