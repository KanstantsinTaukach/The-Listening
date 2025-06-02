// The Listening Game. Made for Game Box

#include "TLCharacter.h"

ATLCharacter::ATLCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATLCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}