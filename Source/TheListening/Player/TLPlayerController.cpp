// The Listening Game. Made for Game Box

#include "TLPlayerController.h"
#include "../UI/TLRadioWidget.h"
#include "../Radio/TLRadio.h"
#include "../Radio/TLRadioStation.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogATLPlayerController, All, All);

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

    const auto Radio = Cast<ATLRadio>(UGameplayStatics::GetActorOfClass(GetWorld(), ATLRadio::StaticClass()));
    if (!Radio)
    {
        UE_LOG(LogATLPlayerController, Error, TEXT("Radio not found in level!"));
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
    auto Radio = Cast<ATLRadio>(UGameplayStatics::GetActorOfClass(GetWorld(), ATLRadio::StaticClass()));
    Radio->FindStation(CurrentFrequency);
    Radio->PlayCurrentStation(RadioAudioComponent);
   
    if (RadioWidget)
    {
        RadioWidget->UpdateMessageDisplay(Radio->GetCurrentStation()->GetMessage());
        RadioWidget->UpdateFrequencyDisplay(CurrentFrequency);
    }
}
