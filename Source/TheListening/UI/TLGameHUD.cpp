// The Listening Game. Made for Game Box

#include "TLGameHUD.h"
#include "../Game/TLGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLGameHUD, All, All);

void ATLGameHUD::BeginPlay() 
{
    Super::BeginPlay();

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
    UE_LOG(LogTLGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}