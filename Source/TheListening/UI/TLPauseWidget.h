// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TLPauseWidget.generated.h"

class UButton;

UCLASS()
class THELISTENING_API UTLPauseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

private:
    UFUNCTION()
    void OnClearPause();
};
