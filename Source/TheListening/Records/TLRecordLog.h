// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Lib/TLCoreTypes.h"
#include "TLRecordLog.generated.h"

UCLASS()
class THELISTENING_API UTLRecordLog : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Records")
    TArray<FSignalRecord> Records;

public:
    UFUNCTION(BlueprintCallable, Category = "Records")
    void AddRecord(float InFrequency, const FString& InMessage, bool InbIsAnomalous);

    UFUNCTION(BlueprintCallable, Category = "Records")
    TArray<FSignalRecord> GetAllRecords() const { return Records; };
};
