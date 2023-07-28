// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_AIBase.h"
#include "Kismet/GameplayStatics.h"

UBTTask_AIBase::UBTTask_AIBase()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;


}

void UBTTask_AIBase::OnGameplayTaskActivated(class UGameplayTask&)
{
	
}

float UBTTask_AIBase::GetStateTime(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return 0.0f;
	}

	float StateTime = BlockBoard->GetValueAsFloat(TEXT("StateTime"));

	return StateTime;
}

AIState UBTTask_AIBase::GetAiState(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return AIState::NONE;
	}

	uint8 Enum = BlockBoard->GetValueAsEnum(TEXT("AIState"));

	return static_cast<AIState>(Enum);

}

void UBTTask_AIBase::ResetStateTime(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	BlockBoard->SetValueAsFloat(TEXT("StateTime"), 0.0f);
}

AGlobalCharacter* UBTTask_AIBase::GetGlobalCharacter(UBehaviorTreeComponent& OwnerComp)
{
	AAICon* AiCon = OwnerComp.GetOwner<AAICon>();
	if (nullptr == AiCon || false == AiCon->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// 정상적이지 않은 뭔가가 
		return nullptr;
	}

	// 컨트롤러에게 내가 조작하는 Pawn은 GetPawn을 사용한다.
	AGlobalCharacter* Character = AiCon->GetPawn<AGlobalCharacter>();
	//PrePos = Character->GetActorLocation();
	//A++;
	//BTPrePos();

	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Chracter || false == Chracter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		// 정상적이지 않은 뭔가가 
		return nullptr;
	}

	return Character;
}
/*
FVector UBTTask_AIBase::BTPrePos()
{
	if (A == 2)
	{
		MainPrePos = PrePos;
	    return MainPrePos;

	}
	
	return MainPrePos;
}

FVector UBTTask_AIBase::GetPrePos()
{
	return MainPrePos;
}
*/
UBlackboardComponent* UBTTask_AIBase::GetBlackboardComponent(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return BlockBoard;
}

EBTNodeResult::Type UBTTask_AIBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type::InProgress;
}

void UBTTask_AIBase::SetStateChange(UBehaviorTreeComponent& OwnerComp, uint8 _State)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	BlockBoard->SetValueAsEnum(TEXT("AIState"), _State);

	ResetStateTime(OwnerComp);

	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
}


void UBTTask_AIBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	UBlackboardComponent* BlockBoard = OwnerComp.GetBlackboardComponent();

	if (nullptr == BlockBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BlockBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	float StateTime = BlockBoard->GetValueAsFloat(TEXT("StateTime"));
	StateTime += DelataSeconds;
	BlockBoard->SetValueAsFloat(TEXT("StateTime"), StateTime);
}




class AActor* UBTTask_AIBase::GetTargetSearch(UBehaviorTreeComponent& OwnerComp)
{
	FString TargetTag = GetBlackboardComponent(OwnerComp)->GetValueAsString(TEXT("TargetTag"));
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

	AGlobalCharacter* Pawn = GetGlobalCharacter(OwnerComp);

	float SearchRange = GetBlackboardComponent(OwnerComp)->GetValueAsFloat(TEXT("SearchRange"));


	AActor* ResultActor = nullptr;

	if (0 != TargetActors.Num())
	{
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < TargetActors.Num(); i++)
		{
			float Dis = (Pawn->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

			if (SearchRange <= Dis)
			{
				continue;
			}

			if (Range > Dis)
			{
				Range = Dis;
				ResultActor = TargetActors[i];
			}
		}
	}

	return ResultActor;
}


//MonsterPrePos();

//void UBTTask_AIBase::MonsterPrePos(_Pos)
//{
	//Test 코드( 초기위치 )
//	AActor* Pos = _Pos;
//	_PrePos = Pos->GetActorLocation();    /*GetTransform().GetLocation();*/
//	_PrePos.Z = 0.0f;
	//_PrePos = OriginPos;
//}

//FVector UBTTask_AIBase::GetPrePos()
//{
//	return _PrePos;
//}

void UBTTask_AIBase::SetPos(FVector& _Pos, UBehaviorTreeComponent& OwnerComp)
{
	if (this == nullptr)
	{
		return;
	}

	PrePos = _Pos;
	SPrePos = PrePos;

	//TargetObject = _Pos;
	//GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("PrePos"))= _Pos;
	//FVector TargetObject = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("PrePos"));
}

FVector UBTTask_AIBase::GetPos()
{

	if (A == 1)
	{
		PPrePos = SPrePos;
		return PPrePos;
	}
	else
	{
		return PPrePos;
	}

}