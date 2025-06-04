// The Listening Game. Made for Game Box

#include "TLRecordLog.h"

void UTLRecordLog::AddRecord(float InFrequency, const FString& InMessage, float InTime, bool InbIsAnomalous) 
{
    FSignalRecord NewRecord;
    NewRecord.Frequency = InFrequency;
    NewRecord.Message = InMessage;
    NewRecord.Time = InTime;
    NewRecord.bIsAnomalous = InbIsAnomalous;

    Records.Add(NewRecord);
}
