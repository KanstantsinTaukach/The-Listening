// The Listening Game. Made for Game Box

#include "TLGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TLGameModeBase.h"

UTLGameInstance::UTLGameInstance() 
{
    ItitializeLevelSequence();
}

void UTLGameInstance::ItitializeLevelSequence() 
{
    LevelSequence.Reset();

    for (int32 i = 1; i <= LevelsNum; ++i)
    {
        FString LevelName = FString::Printf(TEXT("Level_%02d"), i);
        LevelSequence.Add(FName(*LevelName));
    }

    CurrentLevelIndex = LevelSequence.Num() > 0 ? 0 : -1;
}

void UTLGameInstance::LoadNextLevel()
{
    if (!GetWorld() || LevelSequence.Num() == 0) return;
    
    if (CurrentLevelIndex >= LevelSequence.Num() - 1)
    {
        if (const auto TLGameMode = Cast<ATLGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            TLGameMode->GameOver();
        }
    }
    else
    {
        UGameplayStatics::OpenLevel(GetWorld(), LevelSequence[++CurrentLevelIndex]);
    }
}
