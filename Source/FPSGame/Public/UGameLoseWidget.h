#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UGameLoseWidget.generated.h"  

DECLARE_DELEGATE(FOnRestartButtonClicked);

UCLASS()
class FPSGAME_API UGameLoseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    FOnRestartButtonClicked OnRestartButtonClicked;

protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void HandleRestartButtonClicked();

    UPROPERTY(meta = (BindWidget))
    class UButton* RestartButton;
};
