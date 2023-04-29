// Copyright Epic Games, Inc. All Rights Reserved.


#include "LDJAMGameModeBase.h"


void ALDJAMGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Spawn the initial roads these have no houses spawn so player can get adjusted 
	for (int i = 0; i < 2; ++i)
		SpawnRoadTile(false);

	//These start the spawning of houses
	for (int i = 0; i < 6; ++i)
		SpawnRoadTile(true);
}


void ALDJAMGameModeBase::SpawnRoadTile(bool bSpawnHouses)
{
	auto NewRoad = GetWorld()->SpawnActor<ARoad>(RoadClass, NextAttachPoint);
	NextAttachPoint = NewRoad->GetAttachPointTransform();
	if (bSpawnHouses)
		NewRoad->SpawnHouses();
}
