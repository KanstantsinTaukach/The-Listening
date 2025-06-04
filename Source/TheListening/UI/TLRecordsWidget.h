// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Records/TLRecordLog.h"
#include "TLRecordsWidget.generated.h"

class UTextBlock;
class UVerticalBox;

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
    UTextBlock* TimeText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* AnomalyStatusText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TSubclassOf<UUserWidget> RecordItemClass;

    TArray<FSignalRecord> RecordList;

public:
    UFUNCTION(BlueprintCallable)
    void SetRecordList(const TArray<FSignalRecord>& Records);

    UFUNCTION()
    void OnRecordSelected(FSignalRecord SelectedRecord);
};
