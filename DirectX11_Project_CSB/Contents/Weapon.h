#pragma once

// Ό³Έν :
class AWeapon
{
public:
	// constrcuter destructer
	AWeapon();
	~AWeapon();

	// delete Function
	AWeapon(const AWeapon& _Other) = delete;
	AWeapon(AWeapon&& _Other) noexcept = delete;
	AWeapon& operator=(const AWeapon& _Other) = delete;
	AWeapon& operator=(AWeapon&& _Other) noexcept = delete;

protected:

private:

};

