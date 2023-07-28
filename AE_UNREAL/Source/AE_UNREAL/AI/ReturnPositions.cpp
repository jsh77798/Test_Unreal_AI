// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ReturnPositions.h"
#include "AI/BTTask_IDLE.h"

void UReturnPositions::SetPos(FVector _Pos)
{
	this;

	PrePos = _Pos;
	A++;
}

FVector UReturnPositions::GetPos()
{
	if (A == 1)
	{
		PPrePos = PrePos;
		return PPrePos;
	}
	else
	{
		return PPrePos;
	}

}

