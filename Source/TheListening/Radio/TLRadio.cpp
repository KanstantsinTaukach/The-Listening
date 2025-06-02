// The Listening Game. Made for Game Box

#include "TLRadio.h"
#include "TLRadioStation.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogRadio, All, All);

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

    UE_LOG(LogRadio, Log, TEXT("Found %d radio stations"), Stations.Num());
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

    UE_LOG(LogRadio, Log, TEXT("Tuned to %f MHz: %s"), TargetFrequency, *CurrentStation->GetMessage());
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
        UE_LOG(LogRadio, Warning, TEXT("ANOMALY DETECTED: %s"), *CurrentStation->GetMessage());
    }
}