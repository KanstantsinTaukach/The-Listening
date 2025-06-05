// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Records/TLRecordLog.h"
#include "TLRecordItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordItemSelectedSignature, FSignalRecord, SelectedRecord);

class UTextBlock;
class UImage;

UCLASS()
class THELISTENING_API UTLRecordItem : public UUserWidget
{
    GENERATED_BODY()

protected:
    FSignalRecord RecordData;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* FrequencyLabel;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MessagePreview;

    UPROPERTY(meta = (BindWidget))
    UImage* AnomalyIndicatorImage;

public:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRecordItemSelectedSignature OnRecordItemSelected;

    UFUNCTION(BlueprintCallable)
    void SetRecordData(const FSignalRecord& Record);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnListItemClicked();
};
