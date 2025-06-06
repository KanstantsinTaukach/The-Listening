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

private:
    ETLMatchState MatchState = ETLMatchState::WaitingToStart;

    void GameOver();

    void SetMatchState(ETLMatchState State);
};
