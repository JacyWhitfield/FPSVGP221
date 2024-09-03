#include "FPSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPSCharacter.h"
#include "Enemies/EnemyCharacter.h"
#include "HUD/FPSHUD.h"
#include "UMainMenuWidget.h"
#include "UGameWinWidget.h"
#include "UGameLoseWidget.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

AFPSGameModeBase::AFPSGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsGameActive = false;
}

void AFPSGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        PlayerController->SetPause(true);
    }

    if (MainMenuWidgetClass)
    {
        MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();
            MainMenuWidget->bIsFocusable = true;

           
            MainMenuWidget->OnStartButtonClicked.BindUObject(this, &AFPSGameModeBase::StartGame);

            
        }
    }
}

void AFPSGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsGameActive)
    {
        CheckGameOver();
    }
}

void AFPSGameModeBase::StartGame()
{
    if (MainMenuWidget)
    {
        MainMenuWidget->RemoveFromViewport();
        
    }

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        PlayerController->SetPause(false);

        
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);

        PlayerController->bShowMouseCursor = false;  
    }

    bIsGameActive = true;
}

void AFPSGameModeBase::CheckGameOver()
{
    AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (!PlayerCharacter || PlayerCharacter->GetHealth() <= 0)
    {
        OnGameLose();
        return;
    }

    TArray<AActor*> Enemies;
    UGameplayStatics::GetAllActorsOfClass(this, AEnemyCharacter::StaticClass(), Enemies);

    if (Enemies.Num() == 0)
    {
        OnGameWin();
    }
}

void AFPSGameModeBase::OnGameWin()
{
    bIsGameActive = false;

    if (GameWinWidgetClass)
    {
        GameWinWidget = CreateWidget<UGameWinWidget>(GetWorld(), GameWinWidgetClass);
        if (GameWinWidget)
        {
            GameWinWidget->AddToViewport();
            GameWinWidget->OnRestartButtonClicked.BindUObject(this, &AFPSGameModeBase::RestartGame);

            APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            if (PlayerController)
            {
                PlayerController->SetPause(true);
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(GameWinWidget->TakeWidget());
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = true;
            }
        }
    }
}

void AFPSGameModeBase::OnGameLose()
{
    bIsGameActive = false;

    if (GameLoseWidgetClass)
    {
        GameLoseWidget = CreateWidget<UGameLoseWidget>(GetWorld(), GameLoseWidgetClass);
        if (GameLoseWidget)
        {
            GameLoseWidget->AddToViewport();
            GameLoseWidget->OnRestartButtonClicked.BindUObject(this, &AFPSGameModeBase::RestartGame);

            APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            if (PlayerController)
            {
                PlayerController->SetPause(true);
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(GameLoseWidget->TakeWidget());
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = true;
            }
        }
    }
}

void AFPSGameModeBase::RestartGame()
{
   
    if (GameLoseWidget && GameLoseWidget->IsInViewport())
    {
        GameLoseWidget->RemoveFromViewport();
    }

    if (GameWinWidget && GameWinWidget->IsInViewport())
    {
        GameWinWidget->RemoveFromViewport();
    }

  

  
    if (!ensure(GetWorld() != nullptr)) return;
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}



