// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "SBGameStateBase.h"

ACoinItem::ACoinItem()
{

}

void ACoinItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
		if (UWorld* World = GetWorld())
		{
			if (ASBGameStateBase* GameState = World->GetGameState<ASBGameStateBase>())
			{
				GameState->AddScore(PointValue);
			}
		}

        DestroyItem();
    }
}
