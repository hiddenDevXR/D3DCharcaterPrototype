// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Components/D3DHealthComponent.h"
#include "Controllers/D3DPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Gameplay/Interactable.h"
#include "Characters/Components/D3DCharacterAttributeComponent.h"
#include "Abilities/D3DAbilityComponent.h"


#include "Characters/D3DCharacterBase.h"

// Sets default values
AD3DCharacterBase::AD3DCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackTag = FGameplayTag::RequestGameplayTag(FName("Status.PrimaryAttack"));
	InteractionTag = FGameplayTag::RequestGameplayTag(FName("Status.PrimaryInteraction"));
	CharacterTags.Reset();

	HealthComponent = CreateDefaultSubobject<UD3DHealthComponent>(TEXT("Health"));
	CharacterAttributesComponent = CreateDefaultSubobject<UD3DCharacterAttributeComponent>(TEXT("Attributes"));
	AbilityComponent = CreateDefaultSubobject<UD3DAbilityComponent>(TEXT("Abilities"));
}

// Called when the game starts or when spawned
void AD3DCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AD3DCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AD3DCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AD3DCharacterBase::Fire() 
{

}

void AD3DCharacterBase::Jump() {
	Super::Jump();
}

void AD3DCharacterBase::PrimaryInteraction() {

	if (!CharacterTags.HasTag(AttackTag)) {
		CharacterTags.AddTag(InteractionTag);
		UE_LOG(LogTemp, Warning, TEXT("I have Primary Interaction tag"));
		AbilityComponent->TryActiveAbilityByName("PrimaryInteraction");
	}

	if (CharacterTags.HasTag(AttackTag)) {
		UE_LOG(LogTemp, Warning, TEXT("I have Attack tag"));
	}
}

void AD3DCharacterBase::PrimaryAttack()
{
	if (!CharacterTags.HasTag(InteractionTag)) {
		CharacterTags.AddTag(AttackTag);
		UE_LOG(LogTemp, Warning, TEXT("I have Primary Attack tag"));
		AbilityComponent->TryActiveAbilityByName("PrimaryAttack");
	}
}

void AD3DCharacterBase::Die(ED3DDeathCause cause)
{
	if (DeathCause != ED3DDeathCause::None) return;

	DeathCause = cause;

	AD3DPlayerController* PC = GetPlayerController();

	if (PC)
	{
		PC->DisableInput(PC);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	OnDie.Broadcast(cause);
}

bool AD3DCharacterBase::HasCharacterTag(FGameplayTag Tag) const
{
	return CharacterTags.HasTag(Tag);
}

AD3DPlayerController* AD3DCharacterBase::GetPlayerController() const
{
	return Cast<AD3DPlayerController>(GetController());
}

