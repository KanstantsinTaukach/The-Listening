// The Listening Game. Made for Game Box

#include "TLGameHUD.h"
#include "../Game/TLGameModeBase.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLGameHUD, All, All);

void ATLGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    GameWidgets.Add(ETLMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ATLGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ATLGameHUD::OnMatchStateChanged);
        }
    }
}

void ATLGameHUD::OnMatchStateChanged(ETLMatchState State) 
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    UE_LOG(LogTLGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}