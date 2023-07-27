// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster.h"
#include <Global/GlobalGameInstance.h>
#include <Global/Data/MonsterData.h>

#include "ReturnPositions.h"
#include "BehaviorTree/BlackboardComponent.h"


void AMonster::BeginPlay()
{
	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != Inst)
	{

		CurMonsterData = Inst->GetMonsterData(DataName);

		SetAllAnimation(CurMonsterData->MapAnimation);
		SetAniState(AIState::DEATH);

	}

	Super::BeginPlay();

	//FuTargetPrePos();
	
	//UReturnPositions* PrePosTargetActor = Cast<UReturnPositions>(PrePosObject);
	//PrePosTargetActor->
	//TArray<FVector>& Positions = PrePosTargetActor->Positions;
	//int PrePosIndex = PrePosTargetActor->PrePosIndex;
	
	//FVector PrePos = Cast<FVector>TargetActor;
	//TargetActor->GetActorLocation;


	//MonsterPrePos();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIState"), static_cast<uint8>(AIState::IDLE));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 1500.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 200.0f);
}

	//몬스터 초기 위치값
    /*
	void AMonster::FuTargetPrePos()
	{
	   UObject* PrePosObject = GetBlackboardComponent()->GetValueAsObject(TEXT("Monster"));
	    AActor* TargetActor = Cast<AActor>(PrePosObject);
	    TargetPrePos = TargetActor->GetActorLocation();
	}

	FVector AMonster::FuGetPrePos()
	{
		return TargetPrePos;
	}
	*/

//void AMonster::Tick()
//{
//	Super::TickActor;
//	MonsterPrePos();
//}



void AMonster::MonsterPrePos()
{
    //Test 코드( 초기위치 )
	_PrePos = GetActorLocation();    //GetTransform().GetLocation();
	_PrePos.Z = 0.0f;
	A++;
    //_PrePos = OriginPos;
}

FVector AMonster::GetPrePos()
{
	if (A == 2)
	{
	  MPrePos = _PrePos;
	  return  MPrePos;
	}
	return MPrePos;
}
