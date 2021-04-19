// Copyright Olivia Mikler 2020-2021


#include "MyBTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_ClearBlackboardValue::UMyBTTask_ClearBlackboardValue() 
{
	NodeName = TEXT("Clear Blackboard Value");
}
	
EBTNodeResult::Type UMyBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);

	return EBTNodeResult::Succeeded;
}