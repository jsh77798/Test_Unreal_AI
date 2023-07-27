// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/AICharacter.h"
#include <Global/GlobalEnums.h>
#include <Global/Data/MonsterData.h>
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class AE_UNREAL_API AMonster : public AAICharacter
{
	GENERATED_BODY()

	const struct FMonsterData* CurMonsterData;

	void BeginPlay() override;
	//void Tick();

public:
	void MonsterPrePos(/*FVector _PrePos*/);
	FVector GetPrePos();
	FVector _PrePos;
	FVector MPrePos;
	int A = 0;



	//void FuTargetPrePos();
	//FVector FuGetPrePos();

	//FVector TargetPrePos;
	//FVector CurrentIndex;
	//TArray<FVector> Positions;

private:
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName DataName = "NONE";
};
