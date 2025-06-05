// The Listening Game. Made for Game Box

#include "TLRecordLog.h"

void UTLRecordLog::AddRecord(float InFrequency, const FString& InMessage, float InTime, bool InbIsAnomalous) 
{
    for (const FSignalRecord& ExistingRecord : Records)
    {
        if (FMath::IsNearlyEqual(ExistingRecord.Frequency, InFrequency, 0.005f))
        {
            return;
        }
    }

    if (InMessage == FString("No signal"))
    {
        return;
    }

    FSignalRecord NewRecord;
    NewRecord.Frequency = InFrequency;
    NewRecord.Message = InMessage;
    NewRecord.bIsAnomalous = InbIsAnomalous;

    Records.Add(NewRecord);
}
