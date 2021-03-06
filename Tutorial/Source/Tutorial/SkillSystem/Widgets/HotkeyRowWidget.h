// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HotkeyRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UHotkeyRowWidget : public UUserWidget
{
	GENERATED_BODY()	

public :

	UFUNCTION(BlueprintCallable, Category="HotkeyRowWidget")
	TArray<class USkillHotkeyWidget*> GenerateHotkeyRow();

	/* Get */
	UFUNCTION(BlueprintPure, Category = "HotkeyRowWidget")
	const TArray<FKey>& GetHotkeys() const { return m_Hotkeys; }

	UFUNCTION(BlueprintPure, Category = "HotkeyRowWidget")
	const TArray<class USkillHotkeyWidget*>& GetSkillHotkeyWidgets() const { return m_SkillHotkeyWidgets; }

	/* Set */
	UFUNCTION(BlueprintCallable, Category = "HotkeyRowWidget")
	void SetHotkeys(const TArray<FKey>& _Key);

protected :
	UPROPERTY(BlueprintReadWrite, Category = "HotkeyRowWidget")
	TArray<FKey> m_Hotkeys;
	
	UPROPERTY(BlueprintReadWrite, Category = "HotkeyRowWidget")
	TArray<class USkillHotkeyWidget*> m_SkillHotkeyWidgets;

	UPROPERTY()
	class UHorizontalBox* m_pBox;
	
};
