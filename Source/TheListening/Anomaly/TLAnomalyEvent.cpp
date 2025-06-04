// The Listening Game. Made for Game Box

#include "TLAnomalyEvent.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Camera/CameraShakeBase.h"

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
    if (!GetWorld()) return;

    UE_LOG(LogTLAnomalyEvent, Warning, TEXT("Anomaly Activated with intensity: %f"), Intensity);

    PlayAnomalySound();
    PlayCameraShake();

    for (const auto Actor : AffectedActors)
    {
        if (Actor)
        {
            OnAnomalyStart(Actor);

            FTimerHandle TimerHandle_AnomalyDuration;
            FTimerDelegate Delegate;
            Delegate.BindUFunction(this, "OnAnomalyEnd", Actor);

            GetWorld()->GetTimerManager().SetTimer(TimerHandle_AnomalyDuration, Delegate, Duration, false);
        }
    }
}

void ATLAnomalyEvent::OnAnomalyStart(AActor* Actor)
{
    UE_LOG(LogTLAnomalyEvent, Log, TEXT("Anomaly started on actor: %s"), *Actor->GetName());
}

void ATLAnomalyEvent::OnAnomalyEnd(AActor* Actor)
{
    UE_LOG(LogTLAnomalyEvent, Log, TEXT("Anomaly ended on actor: %s"), *Actor->GetName());
}

void ATLAnomalyEvent::PlayCameraShake()
{
    APlayerCameraManager* CamManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (AnomalyCameraShake && CamManager)
    {
        CamManager->StartCameraShake(AnomalyCameraShake, Intensity);
    }
}

void ATLAnomalyEvent::PlayAnomalySound()
{
    if (GetWorld() && AnomalySound)
    {
        UGameplayStatics::SpawnSound2D(GetWorld(), AnomalySound);
    }
}
