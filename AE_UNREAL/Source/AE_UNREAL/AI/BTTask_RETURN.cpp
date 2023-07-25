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

	// ���ʿ� �������� ������ ���� �־���.
	// ���⿡ �־����Ƿ� ������ ������Ʈ�� �� �޸𸮸� �����ٰ��̴ٸ� �����ϰ� �ִ�.

	return EBTNodeResult::Type::InProgress;

}