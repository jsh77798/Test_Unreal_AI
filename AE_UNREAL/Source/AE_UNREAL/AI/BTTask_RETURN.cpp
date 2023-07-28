// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RETURN.h"
#include <Global/GlobalCharacter.h>
#include <Global/ARGlobal.h>
#include <Global/GlobalEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ReturnPositions.h"
#include "BTTask_IDLE.h"
#include "Monster.h"
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
		MoveCom->MaxWalkSpeed = 600.0f;
	}

	return EBTNodeResult::Type::InProgress;
}


void UBTTask_RETURN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	UObject* TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (nullptr != TargetActor)
	{
		SetStateChange(OwnerComp, AIState::MOVE);
		return;
	}

	{

		UBTTask_AIBase* TargetPrePos = nullptr;
		PrePos=TargetPrePos->GetPos();
		FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		// 혹시라도 z축이 있을 가능성을 없애는게 보통입니다.
		
		ThisPos.Z = 0.0f;

		FVector Dir = PrePos - ThisPos;
		Dir.Normalize();

		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * DelataSeconds });
			GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else 
		{
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}

		if (Dir.X == 0.0f && Dir.Y == 0.0f)
		{
			SetStateChange(OwnerComp, AIState::IDLE);
			return;
		}
	}



	{
		FVector PawnPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		FVector TargetPos = TargetActor->GetActorLocation();

		FVector Dir = TargetPos - PawnPos;

		GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
		//GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

		float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));
		float AttackRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("AttackRange"));

		if (SearchRange >= Dir.Size())
		{
			// 적을 다시 추적
			SetStateChange(OwnerComp, AIState::MOVE);
			return;
		}

	}

}
