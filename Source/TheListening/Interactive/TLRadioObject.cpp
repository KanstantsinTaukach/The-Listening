// The Listening Game. Made for Game Box

#include "TLRadioObject.h"
#include "../UI/TLRadioWidget.h"
#include "../Player/TLPlayerController.h"

void ATLRadioObject::OnInteract_Implementation() 
{
    Super::OnInteract_Implementation();

    if (!GetWorld()) return;

    if (const auto PC = Cast<ATLPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        PC->OpenRadioUI();
    }
}
