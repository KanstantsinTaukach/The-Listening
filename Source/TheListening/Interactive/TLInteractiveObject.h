// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLInteractiveObject.generated.h"

UCLASS()
class THELISTENING_API ATLInteractiveObject : public AActor
{
    GENERATED_BODY()

public:
    ATLInteractiveObject();

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Highlight(bool bEnable);

    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnInteract();

    virtual void OnInteract_Implementation();

protected:
    UPROPERTY(EditAnywhere, Category = "Interaction")
    UStaticMeshComponent* MeshComponent;
};
