// The Listening Game. Made for Game Box


#include "TLGoToMenuWidget.h"
#include "Components/Button.h"
#include "../Game/TLGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UTLGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &UTLGoToMenuWidget::OnGoToMenu);
    }
}

void UTLGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld()) return;

    const auto TLGameInstance = GetWorld()->GetGameInstance<UTLGameInstance>();
    if (!TLGameInstance) return;

    if (!TLGameInstance->GetMenuLevelName().IsNone())
    {
        UGameplayStatics::OpenLevel(this, TLGameInstance->GetMenuLevelName());
    }
}
