#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMainMenuWidget.generated.h"


DECLARE_DELEGATE(FOnStartButtonClicked);

UCLASS()
class FPSGAME_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    
    FOnStartButtonClicked OnStartButtonClicked; 

   
protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void HandleStartButtonClicked();

 

    UPROPERTY(meta = (BindWidget))
    class UButton* StartButton;

};
