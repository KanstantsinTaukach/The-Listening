// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Lib/TLCoreTypes.h"
#include "TLRecordsWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class UButton;
class UTLRecordItem;

UCLASS()
class THELISTENING_API UTLRecordsWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* RecordListView;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* FrequencyText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MessageText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* AnomalyStatusText;

    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SubmitButton;

    UPROPERTY(meta = (BindWidget))
    UWidget* WarningPanel;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* WarningText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TSubclassOf<UUserWidget> RecordItemClass;    

    virtual void NativeOnInitialized() override;

public:
    UFUNCTION(BlueprintCallable)
    void SetRecordList(const TArray<FSignalRecord>& Records);

    UFUNCTION()
    void OnRecordItemSelected(UTLRecordItem* SelectedItem);
    UFUNCTION()
    void OnRecordSelected(FSignalRecord SelectedRecord);

    UFUNCTION()
    void OnCloseButtonClicked();

    UFUNCTION()
    void OnSubmitButtonClicked();

private:
    TArray<FSignalRecord> RecordList;

    FTimerHandle WarningTimerHandle;
    FTimerHandle BlinkTimerHandle;

    int32 BlinkCount = 0;
    bool bHasIgnoredAnomaly = false;

    bool bIsMissionSuccess = false;

    // effects
    void ShowWarning(const FString& Message, bool bIsWarning = true, float Duration = 2.0f);
    void StartBlinkEffect();
    void ProcessBlinkEffect();
};
