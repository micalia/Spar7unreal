// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SBGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SPA7_PAWN_API ASBGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
    ASBGameStateBase();
 // ���� ������ �����ϴ� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score")
    int32 Score;

    // ���� ������ �д� �Լ�
    UFUNCTION(BlueprintPure, Category="Score")
    int32 GetScore() const;
    // ������ �߰����ִ� �Լ�
    UFUNCTION(BlueprintCallable, Category="Score")
    void AddScore(int32 Amount);	
};
