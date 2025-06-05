// The Listening Game. Made for Game Box

#include "TLPlayerController.h"
#include "../UI/TLRadioWidget.h"
#include "../UI/TLRecordsWidget.h"
#include "../Radio/TLRadio.h"
#include "../Radio/TLRadioStation.h"
#include "../Records/TLRecordLog.h"
#include "../Interactive/TLInteractiveObject.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogTLPlayerController, All, All);

ATLPlayerController::ATLPlayerController() 
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableTouchEvents = true;

    DefaultMouseCursor = EMouseCursor::Default;

    RadioLog = CreateDefaultSubobject<UTLRecordLog>(TEXT("RadioLog"));
}

void ATLPlayerController::BeginPlay()
{
    Super::BeginPlay();

    const auto ControllerPawn = GetPawn();
    if (ControllerPawn)
    {
        RadioAudioComponent = ControllerPawn->FindComponentByClass<UAudioComponent>();
    }

    Radio = Cast<ATLRadio>(UGameplayStatics::GetActorOfClass(GetWorld(), ATLRadio::StaticClass()));
}

void ATLPlayerController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    HandleInput();
    CheckHighlight();
}

void ATLPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent) return;

    InputComponent->BindAction("IncreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnIncreaseFrequency);
    InputComponent->BindAction("DecreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnDecreaseFrequency);
    InputComponent->BindAction("RecordSignal", IE_Pressed, this, &ATLPlayerController::RecordCurrentSignal);
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
    if (!Radio) return;

    Radio->FindStation(CurrentFrequency);
    Radio->PlayCurrentStation(RadioAudioComponent);
   
    if (RadioWidget && RadioWidget->IsInViewport())
    {
        if (const auto Station = Radio->GetCurrentStation())
        {
            RadioWidget->UpdateMessageDisplay(Station->GetMessage());
            RadioWidget->UpdateFrequencyDisplay(CurrentFrequency);
        }
    }
}

void ATLPlayerController::RecordCurrentSignal()
{    
    if (!Radio || !Radio->GetCurrentStation() || !RadioLog) return;

    if (const auto CurrentStation = Radio->GetCurrentStation())
    {
        RadioLog->AddRecord(CurrentStation->GetFrequency(), CurrentStation->GetMessage(), CurrentStation->GetIsAnomalous());
    }
}

void ATLPlayerController::OpenRecordLogUI()
{
    if (!RecordsWidget && RecordWidgetClass)
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

void ATLPlayerController::OpenRadioUI() 
{
    if (!RadioWidget && RadioWidgetClass)
    {
        RadioWidget = CreateWidget<UTLRadioWidget>(this, RadioWidgetClass);
    }

    if (RadioWidget)
    {
        if (!RadioWidget->IsInViewport())
        {
            RadioWidget->AddToViewport();
        }

        RadioWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void ATLPlayerController::CloseRadioUI() 
{
    if (RadioWidget)
    {
        RadioWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

AActor* ATLPlayerController::GetHoveredActor()
{
    if (!GetWorld()) return nullptr;

    FHitResult Hit;
    FVector Start, Dir, End;
    DeprojectMousePositionToWorld(Start, Dir);
    End = Start + Dir * 10000.0f;
    
    FCollisionQueryParams Params;
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f);

    if (bHit && Hit.GetActor())
    {
        return Hit.GetActor();
    }

    return nullptr;
}

void ATLPlayerController::HandleInput() 
{
    if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
    {
        TryInteract();
    }
}

void ATLPlayerController::TryInteract() 
{
    AActor* HoveredActor = GetHoveredActor();
    if (HoveredActor && HoveredActor->IsA<ATLInteractiveObject>())
    {
        Cast<ATLInteractiveObject>(HoveredActor)->OnInteract();
    }
}

void ATLPlayerController::CheckHighlight() 
{
    AActor* HoveredActor = GetHoveredActor();
    if (HoveredActor && HoveredActor->IsA<ATLInteractiveObject>())
    {
        Cast<ATLInteractiveObject>(HoveredActor)->Highlight(true);
    }
}