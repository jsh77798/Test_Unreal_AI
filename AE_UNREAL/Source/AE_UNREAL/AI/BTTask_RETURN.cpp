// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RETURN.h"
#include <Global/ARGlobal.h>
#include "PatrolPositions.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_RETURN::UBTTask_RETURN()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_RETURN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::RETURN);


	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetGlobalCharacter(OwnerComp)->GetMovementComponent());

	if (nullptr != MoveCom)
	{
		MoveCom->MaxWalkSpeed = 300.0f;
	}

	UPatrolPositions* PP = NewObject<UPatrolPositions>();
	GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("PatrolPositions"), PP);


	PP->CurrentIndex = 0;
	// TArray<FVector> Positions;

	FVector OriginPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));

	
	PP->Positions.Add(OriginPos);

	// 최초에 포지션을 여러개 만들어서 넣었다.
	// 여기에 넣었으므로 블랙보드 컴포넌트가 이 메모리를 지켜줄것이다를 생각하고 있다.

	return EBTNodeResult::Type::InProgress;

}