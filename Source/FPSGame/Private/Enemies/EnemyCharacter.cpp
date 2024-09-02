#include "Enemies/EnemyCharacter.h"
#include "Player/FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "AIController.h"
#include "Engine/World.h"
#include "FPSProjectile.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "DrawDebugHelpers.h"

AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    Health = 100.0f;

    // Initialize perception components
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 1000.0f;
    SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
    SightConfig->PeripheralVisionAngleDegrees = 360.0f;
    SightConfig->SetMaxAge(5.0f);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerceptionComponent->ConfigureSense(*SightConfig);
    AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyCharacter::OnTargetDetected);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(ShootingTimer, this, &AEnemyCharacter::Shoot, 2.0f, true);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        // Calculate the direction to the player
        FVector DirectionToPlayer = PlayerCharacter->GetActorLocation() - GetActorLocation();
        DirectionToPlayer.Z = 0.0f; // Keep rotation flat on the ground plane

        FRotator NewRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
        SetActorRotation(NewRotation);
    }
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;
    if (Health <= 0.0f)
    {
        Destroy();
    }
    return DamageAmount;
}

void AEnemyCharacter::Shoot()
{
    if (ProjectileClass && IsPlayerInRange())
    {
        FVector MuzzleLocation = GetActorLocation() + FVector(100.0f, 0.0f, GetSimpleCollisionHalfHeight());
        FRotator MuzzleRotation = GetActorRotation();

        AFPSProjectile* Projectile = GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
        if (Projectile)
        {
            Projectile->FireInDirection(MuzzleRotation.Vector());
        }
    }
}

bool AEnemyCharacter::IsPlayerInRange()
{
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());
        return DistanceToPlayer <= ShootingRange;
    }
    return false;
}

void AEnemyCharacter::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
    if (Stimulus.WasSuccessfullySensed())
    {
        UE_LOG(LogTemp, Warning, TEXT("Player detected by enemy!"));
        Shoot();
    }
}

void AEnemyCharacter::AddHealth(float HealthAmount)
{
    Health += HealthAmount;
    if (Health <= 0.0f)
    {
        Destroy();
    }
}
