#include "UGameLoseWidget.h"
#include "Components/Button.h"

void UGameLoseWidget::NativeConstruct()
{
    Super::NativeConstruct();

   
    this->bIsFocusable = true;

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UGameLoseWidget::HandleRestartButtonClicked);
    }
}


void UGameLoseWidget::HandleRestartButtonClicked()
{
    if (OnRestartButtonClicked.IsBound())
    {
        OnRestartButtonClicked.Execute();
    }
}
