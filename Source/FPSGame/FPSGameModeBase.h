// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameModeBase.generated.h"

UCLASS()
class FPSGAME_API AFPSGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void StartPlay() override;
};
