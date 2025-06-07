// The Listening Game. Made for Game Box

#include "TLInteractiveObject.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLInteractiveObject, All, All);

ATLInteractiveObject::ATLInteractiveObject()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void ATLInteractiveObject::BeginPlay()
{
    Super::BeginPlay();

    if (MeshComponent && HighlightMaterial)
    {
        for (int32 i = 0; i < MeshComponent->GetNumMaterials(); ++i)
        {
            OriginalMaterials.Add(MeshComponent->GetMaterial(i));
        }
    }
}

void ATLInteractiveObject::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
    DynamicMaterials.Empty();
    OriginalMaterials.Empty();

    Super::EndPlay(EndPlayReason);
}

void ATLInteractiveObject::Highlight(bool bEnable) 
{
    if (!MeshComponent || !HighlightMaterial) return;

    if (bEnable)
    {
        DynamicMaterials.Empty();

        const int32 NumMaterials = MeshComponent->GetNumMaterials();
        if (NumMaterials == 0) return;

        for (int32 i = 0; i < NumMaterials; ++i)
        {
            UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(HighlightMaterial, this);
            DynamicMaterials.Add(DynMaterial);
            MeshComponent->SetMaterial(i, DynMaterial);
        }
    }
    else
    {
        for (int32 i = 0; i < OriginalMaterials.Num(); ++i)
        {
            MeshComponent->SetMaterial(i, OriginalMaterials[i]);
        }
        DynamicMaterials.Empty();
    }
}

void ATLInteractiveObject::OnInteract_Implementation() 
{
    UE_LOG(LogTLInteractiveObject, Log, TEXT("Interacted with: %s"), *GetName());
}