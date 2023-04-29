// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Road.h"
#include "GameFramework/GameModeBase.h"
#include "LDJAMGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LDJAM_API ALDJAMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SpawnRoadTile(bool bSpawnHouses);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Components, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<ARoad> RoadClass;

	FTransform NextAttachPoint;
};
