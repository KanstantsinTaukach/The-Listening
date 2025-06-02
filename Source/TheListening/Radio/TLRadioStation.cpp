// The Listening Game. Made for Game Box

#include "TLRadioStation.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"

ATLRadioStation::ATLRadioStation()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATLRadioStation::BeginPlay()
{
    Super::BeginPlay();
}

void ATLRadioStation::PlaySignal(UAudioComponent* AudioComponent)
{
    if (AudioComponent && SignalSound)
    {
        AudioComponent->SetSound(SignalSound);
        AudioComponent->Play();
    }
}