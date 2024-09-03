#include "UGameWinWidget.h"
#include "Components/Button.h"

void UGameWinWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UGameWinWidget::HandleRestartButtonClicked);
    }
}

void UGameWinWidget::HandleRestartButtonClicked()
{
    OnRestartButtonClicked.ExecuteIfBound();  
}
