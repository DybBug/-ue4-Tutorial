// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillDragWidget.h"
#include "WidgetTree.h"


void USkillDragWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_pSkillIcon = WidgetTree->FindWidget<UImage>(TEXT("SkillIcon"));
	m_pSkillIcon->SetBrushFromTexture(m_pSkillTexture);
}