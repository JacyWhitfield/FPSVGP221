
#include "FPSProjectile.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFPSProjectile::AFPSProjectile()
{
    PrimaryActorTick.bCanEverTick = true;
    
    if (!RootComponent)
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(15.0f);
    CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
    RootComponent = CollisionComponent;

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = BulletSpeed;
    ProjectileMovementComponent->MaxSpeed = BulletSpeed;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->Bounciness = 0.3f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Game/Meshes/Projectiles/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        ProjectileMeshComponent->SetStaticMesh(SphereMesh.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("/Game/Materials/M_Projectile.M_Projectile"));
    if (SphereMaterial.Succeeded())
    {
        ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(SphereMaterial.Object, ProjectileMeshComponent);
        ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
    }

    ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
    ProjectileMeshComponent->SetupAttachment(RootComponent);

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
    ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * ShootDirection;
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
    {
        OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    }

    Destroy();
}