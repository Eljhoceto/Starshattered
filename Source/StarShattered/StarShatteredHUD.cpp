// Fill out your copyright notice in the Description page of Project Settings.


#include "StarShatteredHUD.h"
#include "Components/ProgressBar.h"

void UStarShatteredHUD::UpdateHealth(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}
