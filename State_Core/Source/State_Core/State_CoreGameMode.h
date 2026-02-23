// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "State_CoreGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AState_CoreGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AState_CoreGameMode();
};



