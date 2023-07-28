// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReturnPositions.generated.h"

/**
 * 
 */
UCLASS()
class AE_UNREAL_API UReturnPositions : public UObject
{
	GENERATED_BODY()

public:
	void SetPos(FVector _Pos);
	FVector GetPos();

	FVector PPrePos;
	FVector PrePos;
	int A = 0;

	//FVector Positions;
	//FVector Positions;
};
