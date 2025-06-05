// The Listening Game. Made for Game Box

#include "TLInteractiveObject.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLInteractiveObject, All, All);

ATLInteractiveObject::ATLInteractiveObject()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void ATLInteractiveObject::Highlight(bool bEnable) 
{
    FString bEnableStr = FString(bEnable ? "Highlight ON" : "Highlight OFF");
    FString Str = FString::Printf(TEXT("%s"), *bEnableStr);
    UE_LOG(LogTLInteractiveObject, Log, TEXT("%s"), *Str);
}

void ATLInteractiveObject::OnInteract_Implementation() 
{
    UE_LOG(LogTLInteractiveObject, Log, TEXT("Interacted with: %s"), *GetName());
}
