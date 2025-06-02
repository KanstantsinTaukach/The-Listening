// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLCharacter.generated.h"

class UCameraComponent;

UCLASS()
class THELISTENING_API ATLCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ATLCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* Camera;


    virtual void BeginPlay() override;
};
