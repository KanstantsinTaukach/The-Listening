// The Listening Game. Made for Game Box

#include "TLRadioWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../Player/TLPlayerController.h"

void UTLRadioWidget::UpdateFrequencyDisplay(const float TargetFrequency)
{
    if (!FrequencyText) return;
    FString FrequencyStr = FString::Printf(TEXT("%.1f MHz "), TargetFrequency);
    FrequencyText->SetText(FText::FromString(FrequencyStr));
}

void UTLRadioWidget::UpdateMessageDisplay(const FString& TargetMessage)
{
    if (!MessageText) return;
    MessageText->SetText(FText::FromString(TargetMessage));
}

void UTLRadioWidget::OnRecordButtonClicked()
{
    if (const auto PC = GetOwningPlayer())
    {
        if (const auto ListeningPC = Cast<ATLPlayerController>(PC))
        {
            ListeningPC->RecordCurrentSignal();
        }
    }
}
