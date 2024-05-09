#pragma once
#include "Weapon.h"

// Ό³Έν :
class AMelee : public AWeapon
{
	GENERATED_BODY(AWeapon);

public:
	// constrcuter destructer
	
	
	AMelee();
	~AMelee();

	// delete Function
	AMelee(const AMelee& _Other) = delete;
	AMelee(AMelee&& _Other) noexcept = delete;
	AMelee& operator=(const AMelee& _Other) = delete;
	AMelee& operator=(AMelee&& _Other) noexcept = delete;





protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetKnifeTypeMeleeLocation(float _DistanceFromPlayer);

	void SetReachTypeMeleeLocation(float _DistanceFromPlayer);


private:
	

	//void AttackDir();
	//void AttackAimDir();
	//void MeleeAttack(float _DeltaTime);
	//
	//float AttackAngle;
	//float AttackTime = 0;
	//float Angle = 0.0f;
	//float Delay = 1.0f;

};

