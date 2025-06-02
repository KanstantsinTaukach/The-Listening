// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TLRadioManager.generated.h"

class ATLRadioStation;

UCLASS()
class THELISTENING_API UTLRadioManager : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Statios")
    TArray<ATLRadioStation*> Stations;

    UPROPERTY()
    ATLRadioStation* CurrentStation;

public:
    UFUNCTION(BlueprintCallable, Category = "Radio")
    void FindNearestStation(float TargetFrequency);

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void PlayCurrentStation(UAudioComponent* AudioComponent);

    UFUNCTION(BlueprintCallable, Category = "Radio")
    void TriggerAnomaly();
};
