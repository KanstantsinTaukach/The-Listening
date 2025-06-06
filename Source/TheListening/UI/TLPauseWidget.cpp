// The Listening Game. Made for Game Box

#include "TLPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void UTLPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UTLPauseWidget::OnClearPause);
    }
}

void UTLPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
