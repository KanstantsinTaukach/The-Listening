// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TLRadioWidget.generated.h"

class UTextBlock;
class UButton;
class USlider;
class USoundBase;

UCLASS()
class THELISTENING_API UTLRadioWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* FrequencyText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MessageText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* InterestText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MessageRecordSuccessText;

    UPROPERTY(meta = (Bindwidget))
    UButton* RecordButton;

    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

    UPROPERTY(meta = (BindWidget))
    USlider* FrequencySlider;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundBase* RecordSound;

    virtual void NativeOnInitialized() override;

public:
    UFUNCTION(BlueprintCallable)
    void UpdateFrequencyDisplay(const float TargetFrequency);

    UFUNCTION(BlueprintCallable)
    void UpdateMessageDisplay(const FString& TargetMessage);

    UFUNCTION(BlueprintCallable)
    void UpdateInterestDisplay(const FString& TargetMessage);

    UFUNCTION()
    void OnRecordButtonClicked();

    UFUNCTION()
    void OnCloseButtonClicked();

    UFUNCTION()
    void OnFrequencySliderValueChanged(float Value);

    UFUNCTION()
    void ShowRecordFeedback();

    UFUNCTION()
    void SetMessageRecordSuccessText(bool bSuccess);
};
