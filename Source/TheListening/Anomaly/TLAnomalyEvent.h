// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLAnomalyEvent.generated.h"

class USoundWave;
class UCameraShakeBase;

UCLASS()
class THELISTENING_API ATLAnomalyEvent : public AActor
{
    GENERATED_BODY()

public:
    ATLAnomalyEvent();

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void ActivateAnomaly();

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void OnAnomalyStart(AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void OnAnomalyEnd(AActor* Actor);

protected:
    UPROPERTY(EditAnywhere, Category = "Anomaly | Effects")
    float Intensity = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Anomaly | Settings")
    float Duration = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Anomaly | Audio")
    USoundWave* AnomalySound;

    UPROPERTY(EditAnywhere, Category = "Anomaly | Affected Actors")
    TArray<AActor*> AffectedActors;

    UPROPERTY(EditDefaultsOnly, Category = "Anomaly | Shake")
    TSubclassOf<UCameraShakeBase> AnomalyCameraShake;

    virtual void BeginPlay() override;

private:
    void PlayCameraShake();
    void PlayAnomalySound();
};
