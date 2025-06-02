// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLRadio.generated.h"

class ATLRadioStation;

UCLASS()
class THELISTENING_API ATLRadio : public AActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stations")
    TArray<ATLRadioStation*> Stations;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stations")
    ATLRadioStation* CurrentStation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stations")
    ATLRadioStation* DefaultStation;

    virtual void BeginPlay() override;

public:
    ATLRadio();

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void InitializeStations();

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void FindStation(float TargetFrequency);

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void PlayCurrentStation(UAudioComponent* AudioComponent);

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void TriggerAnomaly();

    ATLRadioStation* GetCurrentStation() const { return CurrentStation; };
};