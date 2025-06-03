// The Listening Game. Made for Game Box

#include "TLRadio.h"
#include "TLRadioStation.h"
#include "Kismet/GameplayStatics.h"
#include "../Anomaly/TLAnomalyEvent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLRadio, All, All);

ATLRadio::ATLRadio()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATLRadio::BeginPlay() 
{
    Super::BeginPlay();
    InitializeStations();
}

void ATLRadio::InitializeStations()
{
    Stations.Empty();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(this, ATLRadioStation::StaticClass(), FoundActors);

    for (const auto Actor : FoundActors)
    {
        if (const auto Station = Cast<ATLRadioStation>(Actor))
        {
            Stations.Add(Station);
        }
    }

    UE_LOG(LogTLRadio, Log, TEXT("Found %d radio stations"), Stations.Num());
}

void ATLRadio::FindStation(float TargetFrequency)
{
    if (Stations.Num() == 0) return;
    
    CurrentStation = DefaultStation;

    for (const auto Station : Stations)
    {
        if (FMath::IsNearlyEqual(Station->GetFrequency(), TargetFrequency, 0.01))
        {
            CurrentStation = Station;
            break;
        }
    }

    UE_LOG(LogTLRadio, Log, TEXT("Tuned to %f MHz: %s"), TargetFrequency, *CurrentStation->GetMessage());

    if (CurrentStation && CurrentStation->GetIsAnomalous())
    {
        TriggerAnomaly();
    }
}

void ATLRadio::PlayCurrentStation(UAudioComponent* AudioComponent)
{
    if (CurrentStation && AudioComponent)
    {
        CurrentStation->PlaySignal(AudioComponent);
    }
}

void ATLRadio::TriggerAnomaly()
{
    if (CurrentStation && CurrentStation->GetIsAnomalous())
    {
        const auto Anomaly = Cast<ATLAnomalyEvent>(UGameplayStatics::GetActorOfClass(this, ATLAnomalyEvent::StaticClass()));
        if (Anomaly)
        {
            Anomaly->ActivateAnomaly();
        }
    }
}