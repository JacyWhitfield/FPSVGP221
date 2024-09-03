#include "FPSProjectile.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPSCharacter.h"
#include "Enemies/EnemyCharacter.h"

AFPSProjectile::AFPSProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(15.0f);
    CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
    RootComponent = CollisionComponent;

    ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
    ProjectileMeshComponent->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Game/Meshes/Projectiles/Sphere.Sphere"));
    if (SphereMesh.Succeeded()) {
        ProjectileMeshComponent->SetStaticMesh(SphereMesh.Object);
    }

    
    ProjectileMeshComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f)); 

    static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("/Game/Materials/M_Projectile.M_Projectile"));
    if (SphereMaterial.Succeeded()) {
        ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(SphereMaterial.Object, ProjectileMeshComponent);
        ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
    }

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = BulletSpeed;
    ProjectileMovementComponent->MaxSpeed = BulletSpeed;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;

    InitialLifeSpan = 3.0f;
}


void AFPSProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AFPSProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor != this)
    {
        if (AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor))
        {
            PlayerCharacter->AddHealth(-10.0f);
        }
        else if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OtherActor))
        {
            EnemyCharacter->AddHealth(-10.0f);
        }

        Destroy();
    }
}
