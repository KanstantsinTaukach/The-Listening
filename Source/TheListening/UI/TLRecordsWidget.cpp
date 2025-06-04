// The Listening Game. Made for Game Box

#include "TLRecordsWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "TLRecordItem.h"

void UTLRecordsWidget::SetRecordList(const TArray<FSignalRecord>& Records)
{
    if (!GetWorld() || !RecordListView) return;

    for (const FSignalRecord& Record : Records)
    {
        const auto RecordItem = CreateWidget<UTLRecordItem>(GetWorld(), RecordItemClass);

        RecordItem->SetRecordData(Record);
    }
}

void UTLRecordsWidget::OnRecordSelected(FSignalRecord SelectedRecord)
{
    if (FrequencyText)
    {
        FrequencyText->SetText(FText::FromString(FString::Printf(TEXT("%.1 MHz"), SelectedRecord.Frequency)));
    }

    if (MessageText)
    {
        MessageText->SetText(FText::FromString(SelectedRecord.Message));
    }

    if (TimeText)
    {
        TimeText->SetText(FText::AsNumber(SelectedRecord.Time));
    }

    if (AnomalyStatusText)
    {
        AnomalyStatusText->SetText(SelectedRecord.bIsAnomalous ? FText::FromString("Anomaly") : FText::FromString("Normal"));
    }
}
