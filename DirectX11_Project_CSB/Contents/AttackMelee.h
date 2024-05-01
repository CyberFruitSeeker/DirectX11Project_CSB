#pragma once

// Ό³Έν :
class AttackMelee
{
public:
	// constrcuter destructer
	AttackMelee();
	~AttackMelee();

	// delete Function
	AttackMelee(const AttackMelee& _Other) = delete;
	AttackMelee(AttackMelee&& _Other) noexcept = delete;
	AttackMelee& operator=(const AttackMelee& _Other) = delete;
	AttackMelee& operator=(AttackMelee&& _Other) noexcept = delete;

protected:

private:

};

