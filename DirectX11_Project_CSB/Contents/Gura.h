#pragma once

// Ό³Έν :
class AGura
{
public:
	// constrcuter destructer
	AGura();
	~AGura();

	// delete Function
	AGura(const AGura& _Other) = delete;
	AGura(AGura&& _Other) noexcept = delete;
	AGura& operator=(const AGura& _Other) = delete;
	AGura& operator=(AGura&& _Other) noexcept = delete;

protected:

private:

};

