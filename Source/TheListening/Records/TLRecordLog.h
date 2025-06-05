// The Listening Game. Made for Game Box

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TLRecordLog.generated.h"

USTRUCT(BlueprintType)
struct FSignalRecord
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")
    float Frequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")
    FString Message;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")
    bool bIsAnomalous;
};

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
