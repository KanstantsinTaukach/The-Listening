// The Listening Game. Made for Game Box

#include "TLCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"

ATLCharacter::ATLCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(GetRootComponent());
    CameraComponent->bUsePawnControlRotation = true;
    CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

    RadioAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RadioAudioComponent"));
    RadioAudioComponent->SetupAttachment(CameraComponent);
    RadioAudioComponent->bAutoActivate = false;
}

void ATLCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}