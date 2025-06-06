// The Listening Game. Made for Game Box

#include "TLRadioWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "../Player/TLPlayerController.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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

void UTLRadioWidget::ShowRecordFeedback()
{
    if (RecordSound && GetWorld())
    {
        UGameplayStatics::PlaySound2D(GetWorld(), RecordSound);
    }

    if (MessageRecordSuccessText)
    {
        MessageRecordSuccessText->SetVisibility(ESlateVisibility::Visible);
    }

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() { MessageRecordSuccessText->SetVisibility(ESlateVisibility::Hidden); }, 1.0f, false);
}

void UTLRadioWidget::SetMessageRecordSuccessText(bool bSuccess)
{
    MessageRecordSuccessText->SetText(bSuccess ? FText::FromString("Success") : FText::FromString("Error"));

    bSuccess ? MessageRecordSuccessText->SetColorAndOpacity(FColor::Green) : MessageRecordSuccessText->SetColorAndOpacity(FColor::Red);
}