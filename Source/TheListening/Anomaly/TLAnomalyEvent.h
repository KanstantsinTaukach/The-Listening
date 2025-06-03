// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLAnomalyEvent.generated.h"

UCLASS()
class THELISTENING_API ATLAnomalyEvent : public AActor
{
    GENERATED_BODY()

public:
    ATLAnomalyEvent();

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void ActivateAnomaly();

protected:
    UPROPERTY(EditAnywhere, Category = "Anomaly | Effects")
    float Intensity;

    UPROPERTY(EditAnywhere, Category = "Anomaly | Settings")
    float Duration = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Anomaly | Affected Actors")
    TArray<AActor*> AffectedActors;

    virtual void BeginPlay() override;
};
