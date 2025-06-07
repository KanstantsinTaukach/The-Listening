// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Lib/TLCoreTypes.h"
#include "TLPlayerController.generated.h"

class UTLRadioWidget;
class ATLRadio;
class UTLRecordsWidget;
class UTLRecordLog;

UCLASS()
class THELISTENING_API ATLPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ATLPlayerController();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void RecordCurrentSignal();

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void SetCurrentFrequency(float NewFrequency) { CurrentFrequency = NewFrequency; };

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OpenRecordLogUI();
    UFUNCTION(BlueprintCallable, Category = "UI")
    void CloseRecordLogUI();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OpenRadioUI();
    UFUNCTION(BlueprintCallable, Category = "UI")
    void CloseRadioUI();

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void UpdateRadio();

protected:
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> RadioWidgetClass;
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> RecordWidgetClass;

    UPROPERTY()
    UAudioComponent* RadioAudioComponent;

    UFUNCTION(BlueprintCallable, Category = "Input")
    void OnIncreaseFrequency();
    UFUNCTION(BlueprintCallable, Category = "Input")
    void OnDecreaseFrequency();

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    float CurrentFrequency = 87.5f;
    const float FrequencyStep = 0.1f;
    const float MinFrequency = 87.5f;
    const float MaxFrequency = 108.0f;

    ETLMatchState CurrentMatchState;

    UPROPERTY()
    UTLRadioWidget* RadioWidget;
    UPROPERTY()
    UTLRecordsWidget* RecordsWidget;

    UPROPERTY()
    UTLRecordLog* RadioLog;

    UPROPERTY()
    ATLRadio* Radio;

    AActor* GetHoveredActor();

    void HandleInput();
    void TryInteract();
    void CheckHighlightActor();

    void OnPauseGame();
    void OnMatchStateChanged(ETLMatchState State);

    bool IsAnyUIVisible() const;
    bool IsRadioWidgetVisible() const;
    bool IsRecordsWidgetVisible() const;

    void ChangeFrequency(float Delta);
};