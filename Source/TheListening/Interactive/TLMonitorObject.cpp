// The Listening Game. Made for Game Box

#include "TLMonitorObject.h"
#include "../UI/TLRecordsWidget.h"
#include "../Player/TLPlayerController.h"

void ATLMonitorObject::OnInteract_Implementation() 
{
    Super::OnInteract_Implementation();

    if (!GetWorld()) return;

    if (const auto PC = Cast<ATLPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        PC->OpenRecordLogUI();
    }
}
