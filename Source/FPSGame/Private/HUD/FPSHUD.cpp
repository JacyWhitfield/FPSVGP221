#include "HUD/FPSHUD.h"
#include "Player/FPSCharacter.h"
#include "Engine/Canvas.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"
#include "Kismet/GameplayStatics.h"

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!CrosshairTexture || !HUDFont) return;

    
    FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
    float CrosshairHalfWidth = (CrosshairTexture->GetSurfaceWidth() * 0.5f);
    float CrosshairHalfHeight = (CrosshairTexture->GetSurfaceHeight() * 0.5f);
    FVector2D CrosshairDrawPos(Center.X - CrosshairHalfWidth, Center.Y - CrosshairHalfHeight);

    FCanvasTileItem TileItem(CrosshairDrawPos, CrosshairTexture->GetResource(), FLinearColor::White);
    TileItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem(TileItem);

   
    AFPSCharacter* Player = Cast<AFPSCharacter>(GetOwningPawn());
    if (Player)
    {
        float Health = Player->GetHealth();
        int32 Ammo = Player->GetAmmo();

        FString HealthString = FString::Printf(TEXT("Health: %d"), FMath::RoundToInt(Health));
        FString AmmoString = FString::Printf(TEXT("Ammo: %d"), Ammo);

        Canvas->K2_DrawText(HUDFont, HealthString, FVector2D(50.0f, 50.0f), FVector2D(1.0f, 1.0f), FLinearColor::White, 1.0f, FLinearColor::Black, FVector2D(1.0f, 1.0f), true, true, true, FLinearColor::Black);
        Canvas->K2_DrawText(HUDFont, AmmoString, FVector2D(50.0f, 100.0f), FVector2D(1.0f, 1.0f), FLinearColor::White, 1.0f, FLinearColor::Black, FVector2D(1.0f, 1.0f), true, true, true, FLinearColor::Black);
    }

}

void AFPSHUD::BeginPlay()
{
    Super::BeginPlay();
    bIsGameOver = false;
}

void AFPSHUD::ShowGameOverScreen(bool bIsWinner)
{
    if (!Canvas || !HUDFont) return; 

    bIsGameOver = true;
    bIsPlayerWinner = bIsWinner;

   
    DrawHUD(); 
}

void AFPSHUD::ResetGame()
{
    bIsGameOver = false;
    DrawHUD();
}
