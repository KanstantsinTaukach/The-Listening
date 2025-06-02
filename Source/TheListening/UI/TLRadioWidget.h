// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TLRadioWidget.generated.h"

class UTextBlock;

UCLASS()
class THELISTENING_API UTLRadioWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* FrequencyText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MessageText;

public:
    UFUNCTION(BlueprintCallable)
    void UpdateFrequencyDisplay(const float TargetFrequency);

    UFUNCTION(BlueprintCallable)
    void UpdateMessageDisplay(const FString& TargetMessage);
};
