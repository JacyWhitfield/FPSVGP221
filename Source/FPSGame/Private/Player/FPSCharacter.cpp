#include "Player/FPSCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "FPSProjectile.h"

AFPSCharacter::AFPSCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    FPSCameraComponent->bUsePawnControlRotation = true;

    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FPSMesh->SetupAttachment(FPSCameraComponent);
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;
    GetMesh()->SetOwnerNoSee(true);

    Health = 100.0f;
    Ammo = 10;
}

void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

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
    if (Ammo <= 0) return; // No ammo to fire

    if (!ProjectileClass) return;

    Ammo--; // Reduce ammo count by 1

    FVector CameraLocation;
    FRotator CameraRotation;
    GetActorEyesViewPoint(CameraLocation, CameraRotation);

    FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
    FRotator MuzzleRotation = CameraRotation;

    UWorld* World = GetWorld();
    if (!World) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
    if (Projectile)
    {
        FVector LaunchDirection = MuzzleRotation.Vector();
        Projectile->FireInDirection(LaunchDirection);
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
    Health = FMath::Clamp(Health, 0.0f, 100.0f);  // Clamps health between 0 and 100

    if (Health <= 0.0f)
    {
        Destroy();
    }
}
// Clamp the add ammo to 32
void AFPSCharacter::AddAmmo(int32 AmmoAmount)
{
    Ammo = FMath::Clamp(Ammo + AmmoAmount, 0, 32);
}

void AFPSCharacter::ApplySlow(float InSlowAmount, float SlowDuration)
{
    // Store the original speed only once when entering the slow zone
    if (SlowAmount == 0.0f)
    {
        OriginalSpeed = GetCharacterMovement()->MaxWalkSpeed;
    }

    SlowAmount = InSlowAmount;
    GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed * SlowAmount;  // Apply the slow effect

    // Log to check the speed when the slow effect is applied
    UE_LOG(LogTemp, Warning, TEXT("ApplySlow - Original Speed: %f, Current Speed: %f"), OriginalSpeed, GetCharacterMovement()->MaxWalkSpeed);

    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFPSCharacter::EndSlow, SlowDuration, false);
}

void AFPSCharacter::EndSlow()
{
    // Set speed to 300 when leaving the slow zone
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;

    // Log to check the speed right after leaving the slow zone
    UE_LOG(LogTemp, Warning, TEXT("EndSlow - Speed set to 300 cm/s for 2 seconds"));

    // Restore the original speed after 2 seconds
    GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFPSCharacter::RestoreOriginalSpeed, 2.0f, false);
}

void AFPSCharacter::RestoreOriginalSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;  // Restore the original speed

    // Log to check the speed when restoring the original speed
    UE_LOG(LogTemp, Warning, TEXT("RestoreOriginalSpeed - Speed restored to: %f"), OriginalSpeed);

    SlowAmount = 0.0f;  // Reset SlowAmount to 0, indicating no slow effect is active
}






