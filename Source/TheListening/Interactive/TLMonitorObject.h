// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "TLInteractiveObject.h"
#include "TLMonitorObject.generated.h"

class UTLRecordsWidget;

UCLASS()
class THELISTENING_API ATLMonitorObject : public ATLInteractiveObject
{
    GENERATED_BODY()

public:
    void OnInteract_Implementation() override;
};
