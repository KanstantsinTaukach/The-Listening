// The Listening Game. Made for Game Box

#include "TLPlayerController.h"
#include "../UI/TLRadioWidget.h"
#include "../Radio/TLRadioManager.h"
#include "../Radio/TLRadioStation.h"
#include "Components/AudioComponent.h"

ATLPlayerController::ATLPlayerController() 
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
}

void ATLPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (RadioClass)
    {
        RadioWidget = CreateWidget<UTLRadioWidget>(this, RadioClass);
        if (RadioWidget)
        {
            RadioWidget->AddToViewport();
        }
    }

    const auto ControllerPawn = GetPawn();
    if (ControllerPawn)
    {
        RadioAudioComponent = ControllerPawn->FindComponentByClass<UAudioComponent>();
    }

    RadioManager = NewObject<UTLRadioManager>(this);
    if (RadioManager)
    {
        RadioManager->InitializeStations(GetWorld());
    }
}

void ATLPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent) return;

    InputComponent->BindAction("IncreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnIncreaseFrequency);
    InputComponent->BindAction("DecreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnDecreaseFrequency);
}

void ATLPlayerController::OnIncreaseFrequency()
{
    CurrentFrequency = FMath::Clamp(CurrentFrequency + FrequencyStep, MinFrequency, MaxFrequency);
    UpdateRadio();
}

void ATLPlayerController::OnDecreaseFrequency() 
{
    CurrentFrequency = FMath::Clamp(CurrentFrequency - FrequencyStep, MinFrequency, MaxFrequency);
    UpdateRadio();
}

void ATLPlayerController::UpdateRadio() 
{
    RadioManager->FindNearestStation(CurrentFrequency);
    RadioManager->PlayCurrentStation(RadioAudioComponent);

    FString Message = RadioManager->GetCurrentStation() ? RadioManager->GetCurrentStation()->GetMessage() : "No signal";
    if (RadioWidget)
    {
        RadioWidget->UpdateMessageDisplay(Message);
        RadioWidget->UpdateFrequencyDisplay(CurrentFrequency);
    }
}
