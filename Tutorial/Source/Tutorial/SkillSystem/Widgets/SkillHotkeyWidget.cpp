// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillHotkeyWidget.h"
#include "SkillDragWidget.h"
#include "../SkillActors/Base_Skill.h"
#include "../DragDropOperations/SkillDragDropOperation.h"

#include "WidgetTree.h"
#include "Materials/MaterialInstanceDynamic.h "
#include "Input/Reply.h"
#include "Kismet/KismetTextLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void USkillHotkeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

#define LOCTEXT_NAMESPACE "USkillHotkeyWidget"
	FText DisplayName = FText::Format(LOCTEXT("DisplayName", "[{0}]"), m_Hotkey.GetDisplayName());
	m_pHotkeyName->SetText(DisplayName);
#undef LOCTEXT_NAMESPACE

	m_pDynamicMaterial = m_pCooldownImage->GetDynamicMaterial();

	m_pSkillButton->OnClicked.AddDynamic(this, &USkillHotkeyWidget::_OnSkillButtonClicked);
}

FReply USkillHotkeyWidget::NativeOnPreviewMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (m_pAssignedSpell)
	{
		if (!m_pAssignedSpell->GetOnCooldown() && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);		
			Result = EventReply.NativeReply;
		}
	}

	return Result;
}

void USkillHotkeyWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UClass* pWBP_SkillDragClass = LoadClass<USkillDragWidget>(nullptr, TEXT("WidgetBlueprint'/Game/TutorialContent/SkillSystem/Widgets/WBP_SkillDrag.WBP_SkillDrag_C'"));
	USkillDragWidget* pWidget = CreateWidget<USkillDragWidget>(GetWorld(), pWBP_SkillDragClass);

	if (m_pAssignedSpell->GetCurrStage().pOverrideIcon)
	{
		pWidget->SetSkillTexture(m_pAssignedSpell->GetCurrStage().pOverrideIcon);
	}
	else
	{
		pWidget->SetSkillTexture(m_pAssignedSpell->GetSkillInfo().pIcon);
	} 
	
	UDragDropOperation* Oper = UWidgetBlueprintLibrary::CreateDragDropOperation(USkillDragDropOperation::StaticClass());
	USkillDragDropOperation* pSkillOper = Cast<USkillDragDropOperation>(Oper);	
	
	pSkillOper->DefaultDragVisual = pWidget;
	pSkillOper->SetFromHotkey(this);
	pSkillOper->SetSkillActor(m_pAssignedSpell);

	OutOperation = pSkillOper;
}

bool USkillHotkeyWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	USkillDragDropOperation* pOperation = Cast<USkillDragDropOperation>(InOperation);

	if (!m_bDraggedOver && 
		(pOperation->GetFromHotkey() != this) && 
		!m_pAssignedSpell)
	{
		m_bDraggedOver = true;
		m_pBaseImage->SetColorAndOpacity(m_DragOverColor);

		return true;
	}
	return false;
}

bool USkillHotkeyWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USkillDragDropOperation* pSkillOper = Cast<USkillDragDropOperation>(InOperation);
	if (pSkillOper)
	{
		if (pSkillOper->GetFromHotkey() != this)
		{
			if (m_pAssignedSpell)
			{
				if (m_pAssignedSpell->GetOnCooldown())
				{
					return true;
				}

				ABase_Skill* pTempAssignedSpell = m_pAssignedSpell;
				ClearAssignedSpell();

				if (pSkillOper->GetFromHotkey())
				{
					pSkillOper->GetFromHotkey()->ClearAssignedSpell();
					AssignSpell(pSkillOper->GetSkillActor());
					pSkillOper->GetFromHotkey()->AssignSpell(pTempAssignedSpell);
				}
				else
				{
					AssignSpell(pSkillOper->GetSkillActor());
				}

				ResetStyle();
				return true;
			}
			else
			{
				if (pSkillOper->GetFromHotkey())
				{
					pSkillOper->GetFromHotkey()->ClearAssignedSpell();
				}

				AssignSpell(pSkillOper->GetSkillActor());
				return true;
			}
		}
	}
	return false;
}

void USkillHotkeyWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	if (m_bDraggedOver)
	{
		USkillDragDropOperation* pOperation = Cast<USkillDragDropOperation>(InOperation);
		ResetStyle();
	}
}

void USkillHotkeyWidget::_OnSkillButtonClicked()
{
	GetAssignedSpell()->OnTryCastSpell();
}

void USkillHotkeyWidget::SetDynamicMaterial(UMaterialInstanceDynamic* _pMaterial)
{
	m_pDynamicMaterial = _pMaterial;
}

void USkillHotkeyWidget::ClearAssignedSpell()
{
	m_bDeactivated = false;
	if (!m_pAssignedSpell->GetOnCooldown())
	{
		m_pAssignedSpell = nullptr;
		m_pSkillButton->SetIsEnabled(false);
		m_pSkillIcon->SetVisibility(ESlateVisibility::Hidden);
		m_pSkillIcon->SetColorAndOpacity(FLinearColor(FColor(0xFFFFFFFF)));
		m_pCooldownImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USkillHotkeyWidget::EnableHotkey()
{
	m_bDeactivated = false;
	if (!m_pAssignedSpell->GetOnCooldown())
	{
		m_pSkillButton->SetIsEnabled(true);
		m_pSkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pSkillIcon->SetColorAndOpacity(FLinearColor(FColor(0xFFFFFFFF)));
		m_pCooldownImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USkillHotkeyWidget::DisableHotkey()
{
	m_bDeactivated = true;
	if (!m_pAssignedSpell->GetOnCooldown())
	{
		m_pDynamicMaterial->SetScalarParameterValue("Percent", 1.0f);
		m_pSkillButton->SetIsEnabled(false);
		m_pSkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pCooldownImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void USkillHotkeyWidget::AssignSpell(ABase_Skill * _Spell)
{
	m_pAssignedSpell = _Spell;

	m_pAssignedSpell->SetHotkeyWidget(this);
	m_pSkillButton->SetIsEnabled(true);
	m_pSkillIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (m_pAssignedSpell->GetCurrStage().pOverrideIcon)
	{
		m_pSkillIcon->SetBrushFromTexture(m_pAssignedSpell->GetCurrStage().pOverrideIcon);
	}
	else
	{
 		m_pSkillIcon->SetBrushFromTexture(m_pAssignedSpell->GetSkillInfo().pIcon);
	}	
	
}

void USkillHotkeyWidget::ResetStyle()
{
	m_bDraggedOver = false;
	m_pBaseImage->SetColorAndOpacity(m_DefaultColor);
}

void USkillHotkeyWidget::SetHotkey(FKey _Key)
{
	m_Hotkey = _Key;
}

void USkillHotkeyWidget::SetAssignedSpell(ABase_Skill * _pSpell)
{
	m_pAssignedSpell = _pSpell;
}

void USkillHotkeyWidget::SetDeactivated(bool _bBool)
{
	m_bDeactivated = _bBool;
}
