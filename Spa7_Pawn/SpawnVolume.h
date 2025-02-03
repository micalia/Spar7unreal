#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"       // �츮�� ������ ����ü
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPA7_PAWN_API ASpawnVolume : public AActor
{
    GENERATED_BODY()

public:
    ASpawnVolume();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnRandomItem();

protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
    USceneComponent* Scene;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable;

    FVector GetRandomPointInVolume() const;
    FItemSpawnRow* GetRandomItem() const;
    void SpawnItem(TSubclassOf<AActor> ItemClass);
};