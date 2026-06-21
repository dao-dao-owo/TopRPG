

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()



	

protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

public:

	virtual void Tick(float DeltaTime) override;
	AAuraEnemy();
	
	/* 敌人敌人接口函数  begin */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/* 敌人敌人接口函数  end */
	
	/* CombatInterface函数  begin */
	virtual int32 GetPlayerLevel() override;
	/* CombatInterface函数  end */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
};
