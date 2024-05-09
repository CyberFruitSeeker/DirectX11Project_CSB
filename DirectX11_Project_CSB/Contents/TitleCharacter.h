#pragma once

// Ό³Έν :
class ATitleCharacter : public AActor
{

	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATitleCharacter();
	~ATitleCharacter();

	// delete Function
	ATitleCharacter(const ATitleCharacter& _Other) = delete;
	ATitleCharacter(ATitleCharacter&& _Other) noexcept = delete;
	ATitleCharacter& operator=(const ATitleCharacter& _Other) = delete;
	ATitleCharacter& operator=(ATitleCharacter&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	USpriteRenderer* Ame;
	USpriteRenderer* Bae;
	USpriteRenderer* Mumei;
	USpriteRenderer* Gura;
	USpriteRenderer* Ina;
	USpriteRenderer* Kiara;
	USpriteRenderer* Kronii;
	USpriteRenderer* Fauna;
	USpriteRenderer* Suisei;
	USpriteRenderer* Sana;
	USpriteRenderer* Shion;
	USpriteRenderer* Sora;
	USpriteRenderer* Subaru;
	USpriteRenderer* Mio;
	USpriteRenderer* Okayu;
	USpriteRenderer* Roboco;
	USpriteRenderer* Matsuri;
	USpriteRenderer* Mel;
	USpriteRenderer* Miko;
	USpriteRenderer* Irys;
	USpriteRenderer* Korone;
	USpriteRenderer* Fubuki;
	USpriteRenderer* Haato;
	USpriteRenderer* Azki;
	USpriteRenderer* Calli;
	USpriteRenderer* Choco;
	USpriteRenderer* Aki;
	USpriteRenderer* Ayame;
	USpriteRenderer* Aqua;
	USpriteRenderer* Melpitsa;
	USpriteRenderer* Olri;
	USpriteRenderer* Rice;
	USpriteRenderer* Eopiputin;
	USpriteRenderer* Hosinoba;
	USpriteRenderer* Laine;
	USpriteRenderer* Kanaeru;
	USpriteRenderer* Cobalskia;
	USpriteRenderer* Zeta;



};

