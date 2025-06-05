// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "TLInteractiveObject.h"
#include "TLRadioObject.generated.h"

class UTLRadioWidget;

UCLASS()
class THELISTENING_API ATLRadioObject : public ATLInteractiveObject
{
    GENERATED_BODY()

public:
    void OnInteract_Implementation() override;
};
