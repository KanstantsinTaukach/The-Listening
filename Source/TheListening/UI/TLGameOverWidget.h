// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TLGameOverWidget.generated.h"

UCLASS()
class THELISTENING_API UTLGameOverWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
};
