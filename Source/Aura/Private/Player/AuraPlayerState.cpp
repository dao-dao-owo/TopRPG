
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


AAuraPlayerState::AAuraPlayerState()
{
	
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
 	//属性可复制
 	AbilitySystemComponent->SetIsReplicated(true);
	//属性复制模式：Mixed表示属性和效果都复制
 	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
 	
 	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
	 
	
	//网络更新频率：服务端向客户端发送更新频率
	SetNetUpdateFrequency(100.0f);
	

}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
