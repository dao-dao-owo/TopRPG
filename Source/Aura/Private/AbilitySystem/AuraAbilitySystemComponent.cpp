


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//受到GE时触发委托
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//标签容器
	FGameplayTagContainer TagContainer;
	//GE所有资产标签传入容器
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAsseTags.Broadcast(TagContainer);
	

}
