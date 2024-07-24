// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	
		CollisionComponent->InitSphereRadius(15.0f);
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnWhateverYouWantToNameIt);
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent){
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = BulletSpeed;
		ProjectileMovementComponent->MaxSpeed = BulletSpeed;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!ProjectileMeshComponent) {
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		// 1. Find the asset
		static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMesh(TEXT("/Game/Meshes/Projectiles/Sphere.Sphere"));
		if (SphereMesh.Succeeded()) {
			ProjectileMeshComponent->SetStaticMesh(SphereMesh.Object);
		}

		// 2. Set the mesh to the component


	// 2. Set the mesh to the component
		// Mini challenge used FObjectFinder to find the M_Projectile
		static ConstructorHelpers::FObjectFinder<UMaterial>SphereMaterial(TEXT("/Game/Materials/M_Projectile.M_Projectile"));
		if (SphereMaterial.Succeeded()) {
			ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(SphereMaterial.Object, ProjectileMeshComponent);
		}

		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	//1. FVector ShooDirection: Pass by value, least efficient
	//2. Fvector& ShootDirection: Pass by ref, memory address. Basically an out. Can possibly change the variable outside this scope
	//3. const FVector& ShootDirection: Pass b ref, memory address, but we can't directly change the parameter

	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * ShootDirection;
}

void AFPSProjectile::OnWhateverYouWantToNameIt(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		Destroy();
	}
}


// Collision with only physics objects




