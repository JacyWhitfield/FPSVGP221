// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSGameModeBase.h"
#include "Engine/Engine.h"

void AFPSGameModeBase::StartPlay()
{
    Super::StartPlay();

    check(GEngine != nullptr);

    // Display a debug message for five seconds. 
    // The -1 "Key" value argument prevents the message from being updated or refreshed.
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));

    UE_LOG(LogTemp, Warning, TEXT("Hello World, this is FPSGameMode"));
}
