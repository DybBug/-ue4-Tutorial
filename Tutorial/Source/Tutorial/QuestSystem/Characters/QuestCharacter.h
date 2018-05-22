// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QuestCharacter.generated.h"


class UQuestSystemHUD;
class UCameraComponent;
class USpringArmComponent;
class UParticleSystemComponent;
class UPaperSpriteComponent;
class AQuestManager;

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

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnLevelUp();
	void UpdateExp();
	void UpdateLevel();
	void AddExpPoints(int _Amount);

	/* Get */
	UQuestSystemHUD* GetHUD() const { return m_pHUD; };

protected :
	UFUNCTION()
	void _FKey();
	
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


	TSubclassOf<UUserWidget> m_pHUDClass;
	UQuestSystemHUD* m_pHUD;

	USoundBase* m_pLevelUpSound;

	AQuestManager* m_pQuestManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	int m_CurrLevel = 1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	int m_CurrExp = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	int m_ExpForNextLevel = 150;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuestCharacter|ExpSystem")
	float m_NextExpMultiplier = 1.5;

};
