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

    UPROPERTY(EditDefaultsOnly, Category = "Highlight", meta = (DisplayName = "Highlight Material"))
    UMaterialInterface* HighlightMaterial;

    UPROPERTY()
    TArray<UMaterialInstanceDynamic*> DynamicMaterials;

    UPROPERTY()
    TArray<UMaterialInterface*> OriginalMaterials;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
