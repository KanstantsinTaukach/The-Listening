// The Listening Game. Made for Game Box

#include "TLAnomalyEvent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLAnomalyEvent, All, All);

ATLAnomalyEvent::ATLAnomalyEvent()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATLAnomalyEvent::BeginPlay()
{
    Super::BeginPlay();
}

void ATLAnomalyEvent::ActivateAnomaly() 
{
    UE_LOG(LogTLAnomalyEvent, Warning, TEXT("Anomaly Activated with intensity: %f"), Intensity);
}