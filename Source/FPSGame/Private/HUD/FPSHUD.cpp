#include "HUD/FPSHUD.h"
#include "Player/FPSCharacter.h"
#include "Engine/Canvas.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"

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

        Canvas->DrawText(HUDFont, HealthString, 50.0f, 50.0f);
        Canvas->DrawText(HUDFont, AmmoString, 50.0f, 100.0f);
    }
}
