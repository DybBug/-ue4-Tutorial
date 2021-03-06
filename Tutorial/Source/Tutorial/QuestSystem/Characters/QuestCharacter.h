// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../QuestSystem.h"
#include "QuestCharacter.generated.h"


class UQuestSystemHUD;
class USaveLoadWidget;
class UCameraComponent;
class USpringArmComponent;
class UParticleSystemComponent;
class UPaperSpriteComponent;
class AQuestManager;
class AObject_Base;
class UCharacterSave;

UCLASS()
class TUTORIAL_API AQuestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(
		float _DamageAmount,
		FDamageEvent const& _DamageEvent,
		AController* _pEventInstigator,
		AActor* _pDamageCauser) override;


public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void StartGame(bool _Load, int _LoadSlot);
	void ContinueGame();
	void ShowSaveWidget();
	
	void OnLevelUp();
	void UpdateExp();
	void UpdateLevel();
	void UpdateHealth();
	void AddExpPoints(int _Amount);

	void SetupPrestigePoints();
	int GetPrestigeByRegion(ERegions _Region);
	void SetPrestigeByRegion(ERegions _Region, int _Value);
	void UpdateRegionWidget();

	void OnNewRegionEntered(ERegions _Region);

	void SaveGameToSlot(int _ToSlot);
	void LoadGameToSlot(int _ToSlot);

	/* Get */
	UQuestSystemHUD* GetHUD() const { return m_pHUD; }
	AQuestManager* GetQuestManager() const { return m_pQuestManager; }

	TArray<TSubclassOf<AObject_Base>>& GetObtainedObjectClasses() { return m_ObtainedObjectClasses; }
	
	const int& GetCurrLevel() const { return m_CurrLevel; }

	const FString& GetDefaultSlotName() const { return m_DefaultSlotName; }

	const TArray<FSavedQuest>& GetLoadedQuests() const { return m_LoadedQuests; }

protected :
	void _ToggleInputMode();

protected :
	UFUNCTION()
	void _OnBeginOverlap(
		UPrimitiveComponent* _pOverlappedComponent, 
		AActor*              _pOtherActor, 
		UPrimitiveComponent* _pOtherComp, 
		int32                 _OtherBodyIndex,
		bool                  _bFromSweep, 
		const FHitResult&     _SweepResult);

	UFUNCTION()
	void _OnEndOverlap(
		UPrimitiveComponent* _pOverlappedComponent, 
		AActor*              _pOtherActor, 
		UPrimitiveComponent* _pOtherComp, 
		int32                _OtherBodyIndex);

	UFUNCTION()
	void _MoveForward(float _Value);

	UFUNCTION()
	void _MoveRight(float _Value);

	UFUNCTION()
	void _Turn(float _Value);

	UFUNCTION()
	void _BKey();

	UFUNCTION()
	void _EKey();

	UFUNCTION()
	void _HKey();

	UFUNCTION()
	void _IKey();

	UFUNCTION()
	void _JKey();

	UFUNCTION()
	void _MKey();

	UFUNCTION()
	void _RKey();

	UFUNCTION()
	void _TabKey();

	UFUNCTION()
	void _LeftMouseButton();
	
protected :
	UPROPERTY(VisibleDefaultsOnly, Category = "QuestCharacter|Camera")
	UCameraComponent* m_pCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = "QuestCharacter|Camera")
	USpringArmComponent* m_pSpringArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "QuestCharacter|MiniMap")
	USpringArmComponent* m_pMiniMapArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "QuestCharacter|MiniMap")
	UChildActorComponent* m_pMiniMapCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = "QuestCharacter|MiniMap")
	UPaperSpriteComponent* m_pPointer;

	UPROPERTY(VisibleDefaultsOnly, Category = "QuestCharacter|ParticleSystem")
	UParticleSystemComponent* m_pLevelUpEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "QuestCharacter|Collision")
	UCapsuleComponent* m_pInteractionCapsule;


	TSubclassOf<UUserWidget> m_pHUDClass;
	UQuestSystemHUD* m_pHUD;

	USoundBase* m_pLevelUpSound;

	AQuestManager* m_pQuestManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	int m_CurrLevel = 1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	int m_CurrExp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	int m_ExpForNextLevel = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	float m_NextExpMultiplier = 1.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestCharacter|HealthSystem")
	int m_MaxHealth = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestCharacter|HealthSystem")
	int m_CurrHealth = 500;

	bool m_bWidgetInput = false;

	bool m_bCanAttack = true;

	TArray<TSubclassOf<AObject_Base>> m_ObtainedObjectClasses;

	TArray<FRegionPrestige> m_PrestigePoints;

	ERegions m_CurrRegion;

	FString m_DefaultSlotName = "PlayerSave";
	UCharacterSave* m_pSaveGameObject;
	int m_AmountOfSaveSlots = 6;

	USaveLoadWidget* m_pSaveLoadWidget;

	TArray<FSavedQuest> m_LoadedQuests;
};
