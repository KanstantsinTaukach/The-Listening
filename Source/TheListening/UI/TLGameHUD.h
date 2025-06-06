// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../Lib/TLCoreTypes.h"
#include "TLGameHUD.generated.h"

UCLASS()
class THELISTENING_API ATLGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    void OnMatchStateChanged(ETLMatchState State);
};
