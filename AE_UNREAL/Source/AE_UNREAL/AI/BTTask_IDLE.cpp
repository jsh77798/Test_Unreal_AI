// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_IDLE.h"
#include <Global/GlobalCharacter.h>
#include <AI/AICon.h>
#include <Global/GlobalEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ReturnPositions.h"
#include "Kismet/GameplayStatics.h"
#include "Math/NumericLimits.h"

EBTNodeResult::Type UBTTask_IDLE::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::IDLE);


	//AGlobalCharacter* Character = AiCon->GetPawn<AGlobalCharacter>();
	//PrePos = Character->GetActorLocation();
	// 
	//UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("PrePos"));
	//AActor* TargetActor = Cast<AActor>(TargetObject);

	//FVector TargetPos = ThisPos->GetActorLocation();
	//FVector TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("PrePos"));

	ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	UBTTask_AIBase* PPP=0;
	PPP ->SetPos(ThisPos, OwnerComp);
	
	
	return EBTNodeResult::Type::InProgress;
}

void UBTTask_IDLE::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	if (2.0f <= GetStateTime(OwnerComp))
	{
		// 지역변수로 랜덤을 이용하는것.
		FRandomStream Stream;
		// 알아서 시간과 같은 변하는 수를 시드값으로 삼는다.
		Stream.GenerateNewSeed();

		int Value = Stream.RandRange(0, 1);

		// UE_LOG(LogTemp, Error, TEXT("%S(%u)> %d"), __FUNCTION__, __LINE__, Value);

		ResetStateTime(OwnerComp);

		//if (Value == 0)
		//{
		SetStateChange(OwnerComp, AIState::PATROL);
		return;
		//}


		// 그럼 순찰할까?
		// 그냥 5초간 다시 대기하자.
		// SetStateChange(OwnerComp, AIState::MOVE);
		// return;
	}

	AActor* ResultActor = GetTargetSearch(OwnerComp);

	if (nullptr != ResultActor)
	{
		GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
		SetStateChange(OwnerComp, AIState::MOVE);
		return;
	}

	//핵심은 플레이어를 찾아내는것.
	// GetGlobalCharacter(OwnerComp)->GetLevel()->;


	return;
}