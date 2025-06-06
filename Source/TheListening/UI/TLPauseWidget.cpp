// The Listening Game. Made for Game Box

#include "TLPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool UTLPauseWidget::Initialize() 
{
    const bool InitStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UTLPauseWidget::OnClearPause);
    }

    return InitStatus;
}

void UTLPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
