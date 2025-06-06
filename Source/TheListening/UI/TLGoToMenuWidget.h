// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TLGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class THELISTENING_API UTLGoToMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* GoToMenuButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnGoToMenu();
};
