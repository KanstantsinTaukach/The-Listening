// The Listening Game. Made for Game Box

#include "TLRecordsWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TLRecordItem.h"

void UTLRecordsWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UTLRecordsWidget::OnCloseButtonClicked);
    }
}

void UTLRecordsWidget::SetRecordList(const TArray<FSignalRecord>& Records)
{
    if (!GetWorld() || !RecordListView) return;

    RecordListView->ClearChildren();

    RecordList = Records;

    for (const FSignalRecord& Record : Records)
    {
        const auto RecordItem = CreateWidget<UTLRecordItem>(GetWorld(), RecordItemClass);

        if (RecordItem && RecordListView)
        {
            RecordItem->SetRecordData(Record);
            RecordItem->OnRecordItemSelected.AddDynamic(this, &UTLRecordsWidget::OnRecordSelected);

            RecordListView->AddChild(RecordItem);
        }
    }

    if (RecordList.Num() > 0)
    {
        OnRecordSelected(RecordList[0]);
    }
}

void UTLRecordsWidget::OnRecordSelected(FSignalRecord SelectedRecord)
{
    if (FrequencyText)
    {
        FrequencyText->SetText(FText::FromString(FString::Printf(TEXT("%.1f MHz"), SelectedRecord.Frequency)));
    }

    if (MessageText)
    {
        MessageText->SetText(FText::FromString(SelectedRecord.Message));
    }

    if (AnomalyStatusText)
    {
        AnomalyStatusText->SetText(SelectedRecord.bIsAnomalous ? FText::FromString("Anomaly") : FText::FromString("Normal"));
    }
}

void UTLRecordsWidget::OnCloseButtonClicked() 
{
    SetVisibility(ESlateVisibility::Hidden);
}
