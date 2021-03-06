// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "../../QuestSystem.h"
#include "Quest_Base.generated.h"


class UQuestWidget;
class UQuestListEntryWidget;
class AQuestManager;

UCLASS()
class TUTORIAL_API AQuest_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest_Base();

	void Initialize(AQuestManager* _pQuestManager);
	void UpdateSubGoals();
	void SetupStartingGoals();
	bool GoToNextSubGoals();

	bool CompleteSubGoal(int _SubGoalIndex, bool _bFail);
	bool SelectedInJournal();

	void OnGoalCompleted(int _GoalIndex);
	void OnGoalFailed(int _GoalIndex);
	void OnQuestCancelled();

	FGoalInfo GoalAtIndex(int _Index);

	bool GoalAlreadyFound(int _GoalIndex);

	void AddGoalForIndex(int _Index);

	void RemoveWidgets();


	/* Get */
	const FQuestInfo&   GetQuestInfo()            const { return m_QuestInfo; }
	const FText&        GetCurrDescription()      const { return m_CurrDescription; }
	const EQuestStates& GetCurrState()            const { return m_CurrState; }
	const int&          GetSelectedSubGoalIndex() const { return m_SelectedSubGoalIndex; }

	UQuestWidget* GetQuestWidget()      const { return m_pQuestWidget; }

	TArray<int>&            GetCurrHuntedAmounts() { return m_CurrHuntedAmounts; }
	TArray<FGoalInfo>&      GetCurrGoals()         { return m_CurrGoals;}
	TArray<FCompletedGoal>& GetCompletedSubGoals() { return m_CompletedSubGoals; }
	TArray<int>&            GetCurrGoalIndices()   { return m_CurrGoalIndices; }


	/* Set */
	void SetQuestInfo(const FQuestInfo& _Info)     { m_QuestInfo = _Info; }
	void SetCurrDescription(const FText& _Text)    { m_CurrDescription = _Text; }
	void SetCurrState(const EQuestStates& _States) { m_CurrState = _States; }
	void SetSelectedSubGoalIndex(int _Index)       { m_SelectedSubGoalIndex = _Index; }

	void SetQuestWidget(UQuestWidget* _pNewQuestWidget)      { m_pQuestWidget = _pNewQuestWidget; }
	void SetListEntryWidget(UQuestListEntryWidget* _pWidget) { m_pListEntryWidget = _pWidget; }

	void SetCurrHuntedAmounts(const TArray<int>& _Values)            { m_CurrHuntedAmounts = _Values; }
	void SetCurrGoals(const TArray<FGoalInfo>&  _Values)             { m_CurrGoals = _Values;}
	void SetCompletedSubGoals(const TArray<FCompletedGoal>& _Values) { m_CompletedSubGoals = _Values; }
	void SetCurrGoalIndices(const TArray<int>& _Values)              { m_CurrGoalIndices = _Values; }

protected :
	void _EndQuest(bool _bFail);

protected :
	UPROPERTY(EditAnywhere, Category = "Quest_Base")
	FQuestInfo m_QuestInfo;

	UPROPERTY(EditAnywhere, Category = "Quest_Base")
	TArray<int> m_StartingSubGoalIndices;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	TArray<int> m_CurrGoalIndices;
	
	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	TArray<FGoalInfo> m_CurrGoals;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	TArray<int> m_CurrHuntedAmounts;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	int m_SelectedSubGoalIndex;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	UQuestWidget* m_pQuestWidget;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	UQuestListEntryWidget* m_pListEntryWidget;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	TArray<FCompletedGoal> m_CompletedSubGoals;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	EQuestStates m_CurrState;

	UPROPERTY(VisibleAnywhere, Category = "Quest_Base|DoNotTouch!")
	FText m_CurrDescription;


	AQuestManager* m_pQuestManager;


};
