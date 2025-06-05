// The Listening Game. Made for Game Box

#include "TLPlayerController.h"
#include "../UI/TLRadioWidget.h"
#include "../UI/TLRecordsWidget.h"
#include "../Radio/TLRadio.h"
#include "../Radio/TLRadioStation.h"
#include "../Records/TLRecordLog.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLPlayerController, All, All);

ATLPlayerController::ATLPlayerController() 
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
}

void ATLPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (RadioWidgetClass)
    {
        RadioWidget = CreateWidget<UTLRadioWidget>(this, RadioWidgetClass);
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

    RadioLog = NewObject<UTLRecordLog>();
}

void ATLPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent) return;

    InputComponent->BindAction("IncreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnIncreaseFrequency);
    InputComponent->BindAction("DecreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnDecreaseFrequency);
    InputComponent->BindAction("RecordSignal", IE_Pressed, this, &ATLPlayerController::RecordCurrentSignal);
    InputComponent->BindAction("OpenRecords", IE_Pressed, this, &ATLPlayerController::OpenRecordLogUI);
    InputComponent->BindAction("CloseRecords", IE_Pressed, this, &ATLPlayerController::CloseRecordLogUI);
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

void ATLPlayerController::RecordCurrentSignal()
{
    const auto Radio = Cast<ATLRadio>(UGameplayStatics::GetActorOfClass(GetWorld(), ATLRadio::StaticClass()));
    if (!GetWorld() || !Radio || !Radio->GetCurrentStation() || !RadioLog) return;

    float Time = GetWorld()->GetTimeSeconds();
    if (const auto CurrentStation = Radio->GetCurrentStation())
    {
        RadioLog->AddRecord(CurrentStation->GetFrequency(), CurrentStation->GetMessage(), Time, CurrentStation->GetIsAnomalous());
    }
}

void ATLPlayerController::OpenRecordLogUI()
{
    if (!RecordWidgetClass) return;

    if (!RecordsWidget)
    {
        RecordsWidget = CreateWidget<UTLRecordsWidget>(this, RecordWidgetClass);
    }

    if (RecordsWidget)
    {
        if (!RecordsWidget->IsInViewport())
        {
            RecordsWidget->AddToViewport();
        }

        RecordsWidget->SetVisibility(ESlateVisibility::Visible);
        RecordsWidget->SetRecordList(RadioLog->GetAllRecords());
    }
}

void ATLPlayerController::CloseRecordLogUI() 
{
    if (RecordsWidget)
    {
        RecordsWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}