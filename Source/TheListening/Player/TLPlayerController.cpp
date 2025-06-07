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
#include "../Game/TLGameModeBase.h"

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

    if (GetWorld())
    {
        if (const auto GameMode = Cast<ATLGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ATLPlayerController::OnMatchStateChanged);
            CurrentMatchState = GameMode->GetMatchState();
        }
    }

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

    if (CurrentMatchState != ETLMatchState::InProgress) return;
    if (IsAnyUIVisible()) return;

    CheckHighlightActor();
    HandleInput();
}

void ATLPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent) return;

    InputComponent->BindAction("IncreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnIncreaseFrequency);
    InputComponent->BindAction("DecreaseFrequency", IE_Pressed, this, &ATLPlayerController::OnDecreaseFrequency);
    InputComponent->BindAction("RecordSignal", IE_Pressed, this, &ATLPlayerController::RecordCurrentSignal);
    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ATLPlayerController::OnPauseGame);
}

void ATLPlayerController::OnIncreaseFrequency()
{
    ChangeFrequency(FrequencyStep);
}

void ATLPlayerController::OnDecreaseFrequency()
{
    ChangeFrequency(-FrequencyStep);
}

void ATLPlayerController::ChangeFrequency(float Delta)
{
    if (CurrentMatchState != ETLMatchState::InProgress) return;

    if (RadioWidget && RadioWidget->GetVisibility() == ESlateVisibility::Visible)
    {
        CurrentFrequency = FMath::Clamp(CurrentFrequency + Delta, MinFrequency, MaxFrequency);
        UpdateRadio();
    }
}

void ATLPlayerController::UpdateRadio()
{
    if (!Radio || !RadioAudioComponent) return;

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
    if (CurrentMatchState != ETLMatchState::InProgress) return;

    if (!Radio || !Radio->GetCurrentStation() || !RadioLog) return;

    if (RadioWidget && RadioWidget->IsInViewport())
    {
        if (const auto CurrentStation = Radio->GetCurrentStation())
        {
            if (CurrentStation->GetCanRecord())
            {
                RadioLog->AddRecord(CurrentStation->GetFrequency(), CurrentStation->GetMessage(), CurrentStation->GetIsAnomalous());
                if (RecordsWidget && RecordsWidget->IsInViewport())
                {
                    RecordsWidget->SetRecordList(RadioLog->GetAllRecords());
                }
            }

            RadioWidget->SetMessageRecordSuccessText(CurrentStation->GetCanRecord());
        }

        RadioWidget->ShowRecordFeedback();
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

    if (RecordsWidget)
    {
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
    if (CurrentMatchState != ETLMatchState::InProgress) return;

    AActor* HoveredActor = GetHoveredActor();
    if (HoveredActor && HoveredActor->IsA<ATLInteractiveObject>())
    {
        Cast<ATLInteractiveObject>(HoveredActor)->OnInteract();
    }
}

void ATLPlayerController::CheckHighlightActor()
{
    AActor* HoveredActor = GetHoveredActor();

    static AActor* LastHoveredActor = nullptr;

    if (LastHoveredActor && LastHoveredActor != HoveredActor)
    {
        if (LastHoveredActor->IsA<ATLInteractiveObject>())
        {
            Cast<ATLInteractiveObject>(LastHoveredActor)->Highlight(false);
        }
    }
    if (HoveredActor && HoveredActor->IsA<ATLInteractiveObject>())
    {
        Cast<ATLInteractiveObject>(HoveredActor)->Highlight(true);
        LastHoveredActor = HoveredActor;
    }
    else
    {
        LastHoveredActor = nullptr;
    }
}

void ATLPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ATLPlayerController::OnMatchStateChanged(ETLMatchState State)
{
    CurrentMatchState = State;

    if (State == ETLMatchState::Pause)
    {
        SetInputMode(FInputModeUIOnly());

        CloseRadioUI();
        CloseRecordLogUI();
    }
    else
    {
        SetInputMode(FInputModeGameAndUI());
    }
}

bool ATLPlayerController::IsAnyUIVisible() const
{
    bool bRadioVisible = RadioWidget && RadioWidget->GetVisibility() == ESlateVisibility::Visible;
    bool bRecordsWidget = RecordsWidget && RecordsWidget->GetVisibility() == ESlateVisibility::Visible;

    return bRadioVisible || bRecordsWidget;
}
