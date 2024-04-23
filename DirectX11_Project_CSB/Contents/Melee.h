#pragma once

// Ό³Έν :
class AMelee : public AActor
{
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
	void BeginPlay();
	void Tick(float _DeltaTime);




private:




};

