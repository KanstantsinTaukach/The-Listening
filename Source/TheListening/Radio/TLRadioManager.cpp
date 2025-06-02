// The Listening Game. Made for Game Box

#include "TLRadioManager.h"
#include "TLRadioStation.h"

DEFINE_LOG_CATEGORY_STATIC(LogRadioManager, All, All);

void UTLRadioManager::FindNearestStation(float TargetFrequency)
{
    if (Stations.Num() == 0) return;

    CurrentStation = Stations[0];
    float MinDiff = FMath::Abs(CurrentStation->GetFrequency() - TargetFrequency);

    for (const auto Station : Stations)
    {
        float Diff = FMath::Abs(Station->GetFrequency() - TargetFrequency);
        if (Diff < MinDiff)
        {
            MinDiff = Diff;
            CurrentStation = Station;
        }
    }

    UE_LOG(LogRadioManager, Log, TEXT("Tuned to %f MHz: %s"), CurrentStation->GetFrequency(), *CurrentStation->GetMessage());
}

void UTLRadioManager::PlayCurrentStation(UAudioComponent* AudioComponent) 
{
    if (CurrentStation && AudioComponent)
    {
        CurrentStation->PlaySignal(AudioComponent);
    }
}

void UTLRadioManager::TriggerAnomaly() 
{
    if (CurrentStation && CurrentStation->GetIsAnomalous())
    {
        UE_LOG(LogRadioManager, Warning, TEXT("ANOMALY DETECTED: %s"), *CurrentStation->GetMessage());
    }
}
