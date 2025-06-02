// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLCharacter.generated.h"

UCLASS()
class THELISTENING_API ATLCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ATLCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
