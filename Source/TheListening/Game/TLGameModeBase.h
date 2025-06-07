// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Lib/TLCoreTypes.h"
#include "TLGameModeBase.generated.h"

UCLASS()
class THELISTENING_API ATLGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATLGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;

    ETLMatchState GetMatchState() const { return MatchState; };

    void GameOver();

private:
    ETLMatchState MatchState = ETLMatchState::WaitingToStart;

    void SetMatchState(ETLMatchState State);
};
