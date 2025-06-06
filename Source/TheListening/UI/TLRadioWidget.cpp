// The Listening Game. Made for Game Box

#include "TLRadioWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "../Player/TLPlayerController.h"

void UTLRadioWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UTLRadioWidget::OnCloseButtonClicked);
    }

    if (RecordButton)
    {
        RecordButton->OnClicked.AddDynamic(this, &UTLRadioWidget::OnRecordButtonClicked);
    }

    if (FrequencySlider)
    {
        FrequencySlider->OnValueChanged.AddDynamic(this, &UTLRadioWidget::OnFrequencySliderValueChanged);
    }
}

void UTLRadioWidget::UpdateFrequencyDisplay(const float TargetFrequency)
{
    if (!FrequencyText) return;

    FString FrequencyStr = FString::Printf(TEXT("%.1f MHz "), TargetFrequency);
    FrequencyText->SetText(FText::FromString(FrequencyStr));

    if (FrequencySlider)
    {
        FrequencySlider->SetValue((TargetFrequency - 87.5f) / (108.0f - 87.5f));
    }
}

void UTLRadioWidget::UpdateMessageDisplay(const FString& TargetMessage)
{
    if (!MessageText) return;
    MessageText->SetText(FText::FromString(TargetMessage));
}

void UTLRadioWidget::OnRecordButtonClicked()
{
    if (const auto PC = Cast<ATLPlayerController>(GetOwningPlayer()))
    {
        PC->RecordCurrentSignal();
    }
}

void UTLRadioWidget::OnCloseButtonClicked()
{
    SetVisibility(ESlateVisibility::Hidden);
}

void UTLRadioWidget::OnFrequencySliderValueChanged(float Value)
{
    const float MinFreq = 87.5f;
    const float MaxFreq = 108.0f;
    float NewFrequencty = FMath::Lerp(MinFreq, MaxFreq, Value);

    if (const auto PC = Cast<ATLPlayerController>(GetOwningPlayer()))
    {
        PC->SetCurrentFrequency(NewFrequencty);
        PC->UpdateRadio();
    }
}
