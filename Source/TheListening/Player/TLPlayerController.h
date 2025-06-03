// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TLPlayerController.generated.h"

class UTLRadioWidget;
class UTLRadio;

UCLASS()
class THELISTENING_API ATLPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ATLPlayerController();

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void RecordCurrentSignal();

protected:
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> RadioClass;

    UPROPERTY()
    UAudioComponent* RadioAudioComponent;

    UPROPERTY()
    UTLRadioWidget* RadioWidget;

    UFUNCTION(BlueprintCallable, Category = "Input")
    void OnIncreaseFrequency();

    UFUNCTION(BlueprintCallable, Category = "Input")
    void OnDecreaseFrequency();

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void UpdateRadio();

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

private:
    float CurrentFrequency = 87.5f;
    const float FrequencyStep = 0.1f;
    const float MinFrequency = 87.5f;
    const float MaxFrequency = 108.0f;
};