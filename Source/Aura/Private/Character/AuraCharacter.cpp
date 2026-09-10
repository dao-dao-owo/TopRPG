


#include "Character/AuraCharacter.h"
#include "UI/HUD/AuraHUD.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"


AAuraCharacter::AAuraCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//角色旋转速度
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.f, 0.0f);
	//限制角色在平面上移动
	GetCharacterMovement()->bConstrainToPlane = true;
	//在开始时将到平面上
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	//禁用控制器旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CharacterClass = ECharacterClass::Elementalist;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//服务器初始化能力系统组件和属性集信息
	InitAbilityActorInfo();
	AddCharacterAbilities();

}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//客户端初始化能力系统组件和属性集信息
	InitAbilityActorInfo();
}

void AAuraCharacter::AddToXP_Implementation(int32 InXP)
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToXP(InXP);
}

void AAuraCharacter::LevelUp_Implementation()
{
	Super::LevelUp_Implementation();
}

void AAuraCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	Super::AddToAttributePoints_Implementation(InAttributePoints);
}

void AAuraCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	Super::AddToSpellPoints_Implementation(InSpellPoints);
}

void AAuraCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToLevel(InPlayerLevel);
}

int32 AAuraCharacter::GetXP_Implementation()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetXP();
}

int32 AAuraCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AAuraCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
}

int32 AAuraCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
}


int32 AAuraCharacter::GetPlayerLevel_Implementation()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}


void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	//设置拥有者（玩家状态）和化身（玩家）
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	//绑定委托函数调用
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
	
	//初始化UI
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttribute();
	
}


void AAuraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

