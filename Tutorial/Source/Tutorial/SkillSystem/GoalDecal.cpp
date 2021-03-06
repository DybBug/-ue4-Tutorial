// Fill out your copyright notice in the Description page of Project Settings.

#include "GoalDecal.h"
#include "SkillSystem.h"

#include <Components/SceneComponent.h>
#include <Components/DecalComponent.h>
#include <Components/BoxComponent.h>
		
#include <Engine/World.h>
#include <Engine/GameEngine.h>
#include <Kismet/GameplayStatics.h>


// Sets default values
AGoalDecal::AGoalDecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = m_pScene;

	m_pDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	m_pDecal->SetupAttachment(RootComponent);

	m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	m_pBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_pBox->SetCollisionObjectType(UEngineTypes::ConvertToCollisionChannel(ETT_Misc));
	m_pBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	m_pBox->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(EOT_Player), ECollisionResponse::ECR_Overlap);
	m_pBox->OnComponentBeginOverlap.AddDynamic(this, &AGoalDecal::_OnComponentBeginOverlap);
	m_pBox->SetupAttachment(m_pDecal);
}

// Called when the game starts or when spawned
void AGoalDecal::BeginPlay()
{
	Super::BeginPlay();

	if (m_pController == nullptr)
	{
		m_pController = Cast<ASkillPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
	
}


void AGoalDecal::_OnComponentBeginOverlap(
	UPrimitiveComponent * _pOverlappedComponent, 
	AActor * _pOtherActor, 
	UPrimitiveComponent * _pOtherComp, 
	int _OtherBodyIndex, 
	bool _bFromSweep, 
	const FHitResult & _SweepResult)
{	
	AActor* pOwner = m_pController->GetPawn();
	if (_pOtherActor == pOwner)
	{
		m_pController->CancelMovementCommand();
	}

}

