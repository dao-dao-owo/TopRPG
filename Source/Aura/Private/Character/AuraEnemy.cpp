


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//属性可复制
	AbilitySystemComponent->SetIsReplicated(true);
	//属性复制模式：Minimal表示只复制属性，不复制效果
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
	
	
	
	PrimaryActorTick.bCanEverTick = true;
}


void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AAuraEnemy::InitAbilityActorInfo()
{
	//设置拥有者（敌人）和化身（敌人）
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	//绑定委托函数调用
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}


void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAuraEnemy::HighlightActor()
{
	//打开自定义模板深度
	GetMesh()->SetRenderCustomDepth(true);
	//设置深度
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

