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
	int CurrentIndex = 0;
	TArray<FVector> Positions;
	//FVector Positions;
};
