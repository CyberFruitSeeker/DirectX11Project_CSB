#pragma once

// Ό³Έν :
class ATitleBack
{
public:
	// constrcuter destructer
	ATitleBack();
	~ATitleBack();

	// delete Function
	ATitleBack(const ATitleBack& _Other) = delete;
	ATitleBack(ATitleBack&& _Other) noexcept = delete;
	ATitleBack& operator=(const ATitleBack& _Other) = delete;
	ATitleBack& operator=(ATitleBack&& _Other) noexcept = delete;

protected:

private:

};

