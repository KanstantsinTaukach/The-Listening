// The Listening Game. Made for Game Box

#include "TLRecordsWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TLRecordItem.h"

void UTLRecordsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UTLRecordsWidget::OnCloseButtonClicked);
    }

    if (SubmitButton)
    {
        SubmitButton->OnClicked.AddDynamic(this, &UTLRecordsWidget::OnSubmitButtonClicked);
    }

    if (WarningPanel)
    {
        WarningPanel->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UTLRecordsWidget::SetRecordList(const TArray<FSignalRecord>& Records)
{
    if (!GetWorld() || !RecordListView) return;

    RecordListView->ClearChildren();

    RecordList = Records;

    for (const FSignalRecord& Record : Records)
    {
        const auto RecordItem = CreateWidget<UTLRecordItem>(GetWorld(), RecordItemClass);

        if (RecordItem && RecordListView)
        {
            RecordItem->SetRecordData(Record);
            // RecordItem->OnRecordItemSelected.AddDynamic(this, &UTLRecordsWidget::OnRecordSelected);
            RecordItem->OnRecordItemSelected.AddDynamic(this, &UTLRecordsWidget::OnRecordItemSelected);

            RecordListView->AddChild(RecordItem);
        }
    }

    if (RecordList.Num() > 0)
    {
        OnRecordSelected(RecordList[0]);
    }
}

void UTLRecordsWidget::OnRecordItemSelected(UTLRecordItem* SelectedItem)
{
    if (!SelectedItem) return;

    const FSignalRecord& Record = SelectedItem->GetRecordData();
    OnRecordSelected(Record);
}

void UTLRecordsWidget::OnRecordSelected(FSignalRecord SelectedRecord)
{
    if (FrequencyText)
    {
        FrequencyText->SetText(FText::FromString(FString::Printf(TEXT("%.1f MHz"), SelectedRecord.Frequency)));
    }

    if (MessageText)
    {
        MessageText->SetText(FText::FromString(SelectedRecord.Message));
    }

    if (AnomalyStatusText)
    {
        AnomalyStatusText->SetText(SelectedRecord.bIsAnomalous ? FText::FromString("Anomaly") : FText::FromString("Normal"));
    }
}

void UTLRecordsWidget::OnCloseButtonClicked()
{
    GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(WarningTimerHandle);

    for (UWidget* Child : RecordListView->GetAllChildren())
    {
        if (UTLRecordItem* Item = Cast<UTLRecordItem>(Child))
        {
            Item->SetSelected(false);
        }
    }

    SetVisibility(ESlateVisibility::Hidden);
}

void UTLRecordsWidget::OnSubmitButtonClicked()
{
    TArray<FSignalRecord> SelectedRecords;
    bool bHasAnomalous = false;
    bHasIgnoredAnomaly = false;

    for (UWidget* Child : RecordListView->GetAllChildren())
    {
        if (UTLRecordItem* Item = Cast<UTLRecordItem>(Child))
        {
            const FSignalRecord& Record = Item->GetRecordData();

            if (Item->IsSelected())
            {
                SelectedRecords.Add(Record);
                if (Record.bIsAnomalous) bHasAnomalous = true;
            }
            else if (Record.bIsAnomalous)
            {
                bHasIgnoredAnomaly = true;
            }
        }
    }

    if (SelectedRecords.Num() == 0)
    {
        ShowWarning("Please select at least one signal");
        return;
    }

    if (bHasAnomalous)
    {
        ShowWarning("Error: unreadable signal detected");
    }
    else
    {
        ShowWarning("Report successfully sent!", false);

        if (!bHasIgnoredAnomaly)
        {
            GetWorld()->GetTimerManager().SetTimer(
                WarningTimerHandle,
                [this]()
                {
                    OnCloseButtonClicked();  
                },
                3.0f, false);
        }
        else
        {
            GetWorld()->GetTimerManager().SetTimer(
                WarningTimerHandle, [this]() { StartBlinkEffect(); }, 3.0f, false);
            //StartBlinkEffect();
        }
    }
}

void UTLRecordsWidget::StartBlinkEffect()
{
    GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);

    BlinkCount = 5;

    if (WarningPanel && WarningText)
    {
        WarningText->SetText(FText::FromString(""));
        WarningPanel->SetVisibility(ESlateVisibility::Hidden);
    }

    ProcessBlinkEffect();
}

void UTLRecordsWidget::ProcessBlinkEffect()
{
    if (BlinkCount <= 0)
    {
        if (WarningPanel && WarningText)
        {
            WarningText->SetText(FText::FromString("A crucial transmission was ignored..."));
            WarningText->SetColorAndOpacity(FColor::Red);
            WarningPanel->SetVisibility(ESlateVisibility::Visible);

            GetWorld()->GetTimerManager().SetTimer(
                WarningTimerHandle,
                [this]()
                {
                    OnCloseButtonClicked();
                },
                3.0f, false);
        }
        return;
    }

    if (WarningPanel)
    {
        if (BlinkCount == 5)
        {
            WarningPanel->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            WarningPanel->SetVisibility(WarningPanel->GetVisibility() == ESlateVisibility::Visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
        }
    }

    BlinkCount--;

    GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &UTLRecordsWidget::ProcessBlinkEffect, 0.3f, false);
}

void UTLRecordsWidget::ShowWarning(const FString& Message, bool bIsWarning, float Duration)
{
    GetWorld()->GetTimerManager().ClearTimer(WarningTimerHandle);

    if (WarningPanel && WarningText)
    {
        WarningText->SetText(FText::FromString(Message));
        if (bIsWarning)
        {
            WarningText->SetColorAndOpacity(FColor::Red);
        }
        else
        {
            WarningText->SetColorAndOpacity(FColor::Green);
        }

        WarningPanel->SetVisibility(ESlateVisibility::Visible);

        if (Duration > 0)
        {
            GetWorld()->GetTimerManager().SetTimer(
                WarningTimerHandle,
                [this]()
                {
                    if (WarningPanel)
                    {
                        WarningPanel->SetVisibility(ESlateVisibility::Hidden);
                    }
                },
                Duration, false);
        }
    }
}