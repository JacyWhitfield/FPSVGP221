#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UMainMenuWidget.h"
#include "UGameWinWidget.h"  // Correctly named include
#include "UGameLoseWidget.h" // Correctly named include
#include "FPSGameModeBase.generated.h"

UCLASS()
class FPSGAME_API AFPSGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AFPSGameModeBase();

    virtual void Tick(float DeltaTime) override;

    void CheckGameOver();
    void StartGame();
    void RestartGame();

protected:
    virtual void BeginPlay() override;

private:
    bool bIsGameActive;

    void OnGameWin();
    void OnGameLose();

   
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;

    UPROPERTY()
    class UMainMenuWidget* MainMenuWidget;

    
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UGameWinWidget> GameWinWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UGameLoseWidget> GameLoseWidgetClass;

    UPROPERTY()
    class UGameWinWidget* GameWinWidget;

    UPROPERTY()
    class UGameLoseWidget* GameLoseWidget;
};
