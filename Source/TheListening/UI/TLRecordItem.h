// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Lib/TLCoreTypes.h"
#include "TLRecordItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecordItemSelectedSignature, UTLRecordItem*, SelectedItem);

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

    UPROPERTY(meta = (BindWidget))
    UImage* SelectionIndicator;

public:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRecordItemSelectedSignature OnRecordItemSelected;

    UFUNCTION(BlueprintCallable)
    void SetRecordData(const FSignalRecord& Record);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnListItemClicked();

    UFUNCTION(BlueprintCallable)
    void SetSelected(bool bIsSelected);

    const FSignalRecord& GetRecordData() const { return RecordData; }
    bool IsSelected() const { return bSelected; }

    virtual void NativeOnInitialized() override;

private:
    bool bSelected = false;
};
