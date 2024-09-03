#include "UMainMenuWidget.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleStartButtonClicked);
    }
   
}

void UMainMenuWidget::HandleStartButtonClicked()
{
    OnStartButtonClicked.Execute();

}


