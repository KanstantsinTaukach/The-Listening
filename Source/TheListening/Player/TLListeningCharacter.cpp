// Fill out your copyright notice in the Description page of Project Settings.


#include "TLListeningCharacter.h"

// Sets default values
ATLListeningCharacter::ATLListeningCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATLListeningCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATLListeningCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATLListeningCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

