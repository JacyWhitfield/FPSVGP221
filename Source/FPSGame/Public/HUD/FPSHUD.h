#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"

UCLASS()
class FPSGAME_API AFPSHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditAnywhere, Category = "HUD")
    UTexture2D* CrosshairTexture;

    UPROPERTY(EditAnywhere, Category = "HUD")
    UFont* HUDFont; // Added HUDFont declaration
};
