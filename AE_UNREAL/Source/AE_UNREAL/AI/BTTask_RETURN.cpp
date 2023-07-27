// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RETURN.h"
#include <Global/GlobalCharacter.h>
#include <Global/ARGlobal.h>
#include <Global/GlobalEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "ReturnPositions.h"
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
		MoveCom->MaxWalkSpeed = 400.0f;
	}
	


	int PatrolCount = UARGlobal::MainRandom.RandRange(4, 8);

	UReturnPositions* PP = NewObject<UReturnPositions>();
	GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("ReturnPositions"), PP);


	PP->CurrentIndex = 0;
	// TArray<FVector> Positions;

	//FVector OriginPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	AAICon* MyAIController = Cast<AAICon>(OwnerComp.GetAIOwner());
	if (!MyAIController)
	{
		return EBTNodeResult::Failed;
	}
	FVector TargetLocation = MyAIController->AIPrePos; //GetPrePos;

	PP->Positions.Add(TargetLocation);
	//float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));

	
		   //이전위치를 가져와 그 위치로 이동시킨다
		   //이전 위치 가져오기(Monster.h에서 가져왔다)
	     /*
		   AMonster TargetActor;
		   R_PrePos = TargetActor.FuGetPrePos();
		   R_PrePos.Z = 0.0f;
         */
		 // AI 컨트롤러 가져오기

	//AAICharacter* MyAICharacter = Cast<AAICharacter>(MyAIController->GetPawn());
	//if (MyAICharacter)
	//{
	//	MyAICharacter->MoveToLocation(TargetLocation);
	//	return EBTNodeResult::InProgress;
	//}
	//return EBTNodeResult::Failed;
	     
		   //UBTTask_AIBase PTargetActor;
		  // R_PrePos = PTargetActor.GetPrePos();
		   //R_PrePos.Z = 0.0f;
		 
	return EBTNodeResult::Type::InProgress;
}


void UBTTask_RETURN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	UObject* PPObject = GetBlackboardComponent(OwnerComp)->GetValueAsObject(TEXT("ReturnPositions"));

	if (nullptr == PPObject)
	{
		SetStateChange(OwnerComp, AIState::IDLE);
		return;
	}

	UReturnPositions* PP = Cast<UReturnPositions>(PPObject);

	//FVector PrePositions = PP->Positions;
	TArray<FVector>& PrePositions = PP->Positions;
	int CurrentIndex = PP->CurrentIndex;

	//FVector TargetPos = Positions[CurrentIndex];
	FVector TargetPos = PrePositions[CurrentIndex];
	FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();


	AActor* ResultActor = GetTargetSearch(OwnerComp);

	if (nullptr != ResultActor)
	{
		GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
		SetStateChange(OwnerComp, AIState::MOVE);
		return;
	}


	{
		TargetPos.Z = 0.0f;
		ThisPos.Z = 0.0f;

		FVector Dir = TargetPos - ThisPos;
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
		else {
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}
	}

	{
		FVector Dir = TargetPos - ThisPos;

		GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);

		if (50.0f >= Dir.Size())
		{
			++PP->CurrentIndex;
			return;
		}
	}



	  /*
	    {
		   //현재 위치 
		   //UBTTask_AIBase TargetActor;
		   //R_PrePos = TargetActor.GetPrePos();
		   //R_PrePos.Z = 0.0f;

		   FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		   ThisPos.Z = 0.0f;

		   FVector Dir = R_PrePos - ThisPos;
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
		   else {
			   FRotator Rot = Dir.Rotation();
			   GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		   }

	    }

		{
            FVector PawnPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
			

			FVector Dir = R_PrePos - PawnPos;

			GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
			//GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

			float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));

			if (SearchRange < Dir.Size())
			{
				// 원재 자리로 돌아가고
				SetStateChange(OwnerComp, AIState::IDLE);
				return;
			}

		}
		*/
}
