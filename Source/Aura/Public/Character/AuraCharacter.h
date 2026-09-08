

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class AAuraHUD;


UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	//服务器设置
	virtual void PossessedBy(AController* NewController) override;
	//客户端设置
	virtual void OnRep_PlayerState() override;
	
	/* Players Interface函数 begin */
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	/* Players Interface函数 end */
	
	/* CombatInterface函数  begin */
	virtual int32 GetPlayerLevel_Implementation() override;
	/* CombatInterface函数  end */
	
protected:

	virtual void BeginPlay() override;
	

		
private:
	virtual void InitAbilityActorInfo() override;
public:

	virtual void Tick(float DeltaTime) override;
};
