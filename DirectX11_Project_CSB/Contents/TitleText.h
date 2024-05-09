#pragma once

// Ό³Έν :
class TitleText
{
public:
	// constrcuter destructer
	TitleText();
	~TitleText();

	// delete Function
	TitleText(const TitleText& _Other) = delete;
	TitleText(TitleText&& _Other) noexcept = delete;
	TitleText& operator=(const TitleText& _Other) = delete;
	TitleText& operator=(TitleText&& _Other) noexcept = delete;

protected:

private:

};

