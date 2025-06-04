// The Listening Game. Made for Game Box

#include "TLRecordItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UTLRecordItem::SetRecordData(const FSignalRecord& Record)
{
    if (FrequencyLabel)
    {
        FrequencyLabel->SetText(FText::FromString(FString::Printf(TEXT("%.1f MHz"), Record.Frequency)));
    }

    if (MessagePreview)
    {
        MessagePreview->SetText(FText::FromString(Record.Message.Left(30) + "..."));
    }

    if (AnomalyIndicatorImage)
    {
        AnomalyIndicatorImage->SetVisibility(Record.bIsAnomalous ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}