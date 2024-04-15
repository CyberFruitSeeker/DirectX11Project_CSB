#pragma once

// Ό³Έν :
class Monster_DeadbeatBat
{
public:
	// constrcuter destructer
	Monster_DeadbeatBat();
	~Monster_DeadbeatBat();

	// delete Function
	Monster_DeadbeatBat(const Monster_DeadbeatBat& _Other) = delete;
	Monster_DeadbeatBat(Monster_DeadbeatBat&& _Other) noexcept = delete;
	Monster_DeadbeatBat& operator=(const Monster_DeadbeatBat& _Other) = delete;
	Monster_DeadbeatBat& operator=(Monster_DeadbeatBat&& _Other) noexcept = delete;

protected:

private:

};

