#include "Player/FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Create a CameraComponent
    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    FPSCameraComponent->bUsePawnControlRotation = true;

    // Create a mesh component for the first-person view (arms)
    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FPSMesh->SetupAttachment(FPSCameraComponent);
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    // Only the owning player sees this mesh
    GetMesh()->SetOwnerNoSee(true);

    // Initialize health and ammo
    Health = 100.0f;
    Ammo = 30;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::StartJump()
{
    bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
    bPressedJump = false;
}

void AFPSCharacter::Fire()
{
    if (!ProjectileClass || Ammo <= 0) return;

    FVector CameraLocation;
    FRotator CameraRotation;
    GetActorEyesViewPoint(CameraLocation, CameraRotation);

    FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
    FRotator MuzzleRotation = CameraRotation;

    UWorld* World = GetWorld();
    if (World)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
        if (Projectile)
        {
            FVector LaunchDirection = MuzzleRotation.Vector();
            Projectile->FireInDirection(LaunchDirection);
            Ammo--; // Decrease ammo count
        }
    }
}

float AFPSCharacter::GetHealth() const
{
    return Health;
}

int32 AFPSCharacter::GetAmmo() const
{
    return Ammo;
}

void AFPSCharacter::AddHealth(float HealthAmount)
{
    Health += HealthAmount;
    Health = FMath::Clamp(Health, 0.0f, 100.0f);
}

void AFPSCharacter::AddAmmo(int32 AmmoAmount)
{
    Ammo += AmmoAmount;
}

void AFPSCharacter::ApplySlow(float InSlowAmount, float SlowDuration)
{
    SlowAmount = InSlowAmount;
    GetCharacterMovement()->MaxWalkSpeed *= (1.0f - SlowAmount);

    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFPSCharacter::EndSlow, SlowDuration);
}

void AFPSCharacter::EndSlow()
{
    GetCharacterMovement()->MaxWalkSpeed /= (1.0f - SlowAmount);
}
