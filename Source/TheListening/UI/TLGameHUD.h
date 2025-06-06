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
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ETLMatchState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;

    void OnMatchStateChanged(ETLMatchState State);
};
