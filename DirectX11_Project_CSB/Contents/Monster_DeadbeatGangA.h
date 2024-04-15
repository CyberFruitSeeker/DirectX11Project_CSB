#pragma once

// Ό³Έν :
class Monster_DeadbeatGangA
{
public:
	// constrcuter destructer
	Monster_DeadbeatGangA();
	~Monster_DeadbeatGangA();

	// delete Function
	Monster_DeadbeatGangA(const Monster_DeadbeatGangA& _Other) = delete;
	Monster_DeadbeatGangA(Monster_DeadbeatGangA&& _Other) noexcept = delete;
	Monster_DeadbeatGangA& operator=(const Monster_DeadbeatGangA& _Other) = delete;
	Monster_DeadbeatGangA& operator=(Monster_DeadbeatGangA&& _Other) noexcept = delete;

protected:

private:

};

