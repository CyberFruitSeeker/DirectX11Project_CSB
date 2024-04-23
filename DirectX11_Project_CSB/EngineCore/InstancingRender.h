#pragma once

// Ό³Έν :
class InstancingRender
{
public:
	// constrcuter destructer
	InstancingRender();
	~InstancingRender();

	// delete Function
	InstancingRender(const InstancingRender& _Other) = delete;
	InstancingRender(InstancingRender&& _Other) noexcept = delete;
	InstancingRender& operator=(const InstancingRender& _Other) = delete;
	InstancingRender& operator=(InstancingRender&& _Other) noexcept = delete;

protected:

private:

};

