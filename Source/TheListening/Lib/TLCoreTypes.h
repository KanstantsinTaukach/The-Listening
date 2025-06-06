// The Listening Game. Made for Game Box

#pragma once

#include "TLCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FSignalRecord
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")
    float Frequency = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")
    FString Message;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record")
    bool bIsAnomalous = false;
};

UENUM(BlueprintType)
enum class ETLMatchState : uint8
{
    WaitingToStart = 0,
    InProgress,
    Pause,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ETLMatchState);
