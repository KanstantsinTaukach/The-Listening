// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TLCharacter.generated.h"

class UCameraComponent;
class UAudioComponent;

UCLASS()
class THELISTENING_API ATLCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ATLCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    UAudioComponent* RadioAudioComponent;

    virtual void BeginPlay() override;
};
