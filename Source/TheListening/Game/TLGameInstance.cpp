// The Listening Game. Made for Game Box

#include "TLGameInstance.h"
#include "Kismet/GameplayStatics.h"

UTLGameInstance::UTLGameInstance() 
{
    ItitializeLevelSequence();
}

void UTLGameInstance::ItitializeLevelSequence() 
{
    LevelSequence.Reset();

    for (int32 i = 1; i < 10; ++i)
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
        // open game over widget
    }
    else
    {
        CurrentLevelIndex++;
    }

    UGameplayStatics::OpenLevel(GetWorld(), LevelSequence[CurrentLevelIndex]);
}
