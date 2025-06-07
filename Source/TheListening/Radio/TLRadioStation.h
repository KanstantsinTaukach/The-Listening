// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLRadioStation.generated.h"

class USoundWave;

UCLASS()
class THELISTENING_API ATLRadioStation : public AActor
{
    GENERATED_BODY()

public:
    ATLRadioStation();

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void PlaySignal(UAudioComponent* AudioComponent);

    UFUNCTION()
    float GetFrequency() const { return Frequency; };

    UFUNCTION()
    FString GetMessage() const { return Message; };

    UFUNCTION()
    FString GetInterest() const { return Interest; };

    UFUNCTION()
    bool GetIsAnomalous() const { return bIsAnomalous; };

    UFUNCTION()
    bool GetCanRecord() const { return bCanRecord; };

protected:
    UPROPERTY(EditAnywhere, Category = "Station settings | Radio", meta = (ClampMin = "87.5", ClampMax = "108", Delta = "0.1"))
    float Frequency;

    UPROPERTY(EditAnywhere, Category = "Station settings | Audio")
    USoundWave* SignalSound;

    UPROPERTY(EditAnywhere, Category = "Station settings | Metadata")
    FString Message;

    UPROPERTY(EditAnywhere, Category = "Station settings | Metadata")
    FString Interest;

    UPROPERTY(EditAnywhere, Category = "Station settings | Flags")
    bool bIsAnomalous;

    UPROPERTY(EditAnywhere, Category = "Station settings | Flags")
    bool bCanRecord;

    virtual void BeginPlay() override;
};
