// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TLGameInstance.generated.h"

UCLASS()
class THELISTENING_API UTLGameInstance : public UGameInstance
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game") 
    FName MenuLevelName = NAME_None;

    public:
    UFUNCTION(BlueprintCallable)
    FName GetStartupLevelName() const { return StartupLevelName; }

    UFUNCTION(BlueprintCallable)
    FName GetMenuLevelName() const { return MenuLevelName; }
};
