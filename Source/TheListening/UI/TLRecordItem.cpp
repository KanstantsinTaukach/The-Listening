// The Listening Game. Made for Game Box

#include "TLRecordItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UTLRecordItem::SetRecordData(const FSignalRecord& Record)
{
    RecordData = Record;

    if (FrequencyLabel)
    {
        FrequencyLabel->SetText(FText::FromString(FString::Printf(TEXT("%.1 MHz"), RecordData.Frequency)));
    }

    if (MessagePreview)
    {
        MessagePreview->SetText(FText::FromString(RecordData.Message.Left(30) + "..."));
    }

    if (AnomalyIndicatorImage)
    {
        AnomalyIndicatorImage->SetVisibility(RecordData.bIsAnomalous ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}