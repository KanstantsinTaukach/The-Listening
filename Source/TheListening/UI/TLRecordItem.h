// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Records/TLRecordLog.h"
#include "TLRecordItem.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class THELISTENING_API UTLRecordItem : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* FrequencyLabel;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MessagePreview;

    UPROPERTY(meta = (BindWidget))
    UImage* AnomalyIndicatorImage;

public:
    UFUNCTION(BlueprintCallable)
    void SetRecordData(const FSignalRecord& Record);
};
