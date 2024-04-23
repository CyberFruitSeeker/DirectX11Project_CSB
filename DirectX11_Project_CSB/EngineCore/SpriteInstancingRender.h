#pragma once

// Ό³Έν :
class SpriteInstancingRender
{
public:
	// constrcuter destructer
	SpriteInstancingRender();
	~SpriteInstancingRender();

	// delete Function
	SpriteInstancingRender(const SpriteInstancingRender& _Other) = delete;
	SpriteInstancingRender(SpriteInstancingRender&& _Other) noexcept = delete;
	SpriteInstancingRender& operator=(const SpriteInstancingRender& _Other) = delete;
	SpriteInstancingRender& operator=(SpriteInstancingRender&& _Other) noexcept = delete;

protected:

private:

};

