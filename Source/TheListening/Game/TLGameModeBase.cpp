// The Listening Game. Made for Game Box

#include "TLGameModeBase.h"
#include "../Player/TLPlayerController.h"
#include "../Player/TLCharacter.h"

ATLGameModeBase::ATLGameModeBase() 
{
    DefaultPawnClass = ATLCharacter::StaticClass();
    PlayerControllerClass = ATLPlayerController::StaticClass();
}

void ATLGameModeBase::StartPlay() 
{
    Super::StartPlay();

    SetMatchState(ETLMatchState::InProgress);
}

void ATLGameModeBase::GameOver() 
{
    SetMatchState(ETLMatchState::GameOver);
}

void ATLGameModeBase::SetMatchState(ETLMatchState State)
{
    if (MatchState == State) return;

    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}

bool ATLGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    if (MatchState != ETLMatchState::InProgress) return false;

    const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        SetMatchState(ETLMatchState::Pause);
    }

    return PauseSet;
}

bool ATLGameModeBase::ClearPause()
{
    if (MatchState != ETLMatchState::Pause) return false;

    const bool PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(ETLMatchState::InProgress);
    }

    return PauseCleared;
}