#pragma once
#include <EngineCore/GameMode.h>
#include "TitleLogo.h"
#include "TitleBack.h"
#include "TitleText.h"
#include "Menu.h"
#include "HoloMouse.h"
#include "TitleCharacter.h"


// 설명 :
class ATitleGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	static std::shared_ptr<class UTitleText> TitleText;
	// constrcuter destructer
	ATitleGameMode();
	~ATitleGameMode();

	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);
	void SpawnTitleBack(float _DeltaTime);



private:
	std::shared_ptr<ATitleLogo> TitleLogo;
	std::list<std::shared_ptr<ATitleBack>> TitleBack;
	std::shared_ptr<AMenu> Menu;
	// 타이틀캐릭터
	std::shared_ptr<ATitleCharacter> Ame;
	std::shared_ptr<ATitleCharacter> Bae;
	std::shared_ptr<ATitleCharacter> Mumei;
	std::shared_ptr<ATitleCharacter> Fauna;
	std::shared_ptr<ATitleCharacter> Gura;
	std::shared_ptr<ATitleCharacter> Kronii;
	std::shared_ptr<ATitleCharacter> Suisei;
	std::shared_ptr<ATitleCharacter> Sana;
	std::shared_ptr<ATitleCharacter> Shion;
	std::shared_ptr<ATitleCharacter> Sora;
	std::shared_ptr<ATitleCharacter> Subaru;
	std::shared_ptr<ATitleCharacter> Mio;
	std::shared_ptr<ATitleCharacter> Okayu;
	std::shared_ptr<ATitleCharacter> Roboco;
	std::shared_ptr<ATitleCharacter> Matsuri;
	std::shared_ptr<ATitleCharacter> Mel;
	std::shared_ptr<ATitleCharacter> Miko;
	std::shared_ptr<ATitleCharacter> Ina;
	std::shared_ptr<ATitleCharacter> Irys;
	std::shared_ptr<ATitleCharacter> Kiara;
	std::shared_ptr<ATitleCharacter> Korone;
	std::shared_ptr<ATitleCharacter> Fubuki;
	std::shared_ptr<ATitleCharacter> Haato;
	std::shared_ptr<ATitleCharacter> Azki;
	std::shared_ptr<ATitleCharacter> Calli;
	std::shared_ptr<ATitleCharacter> Choco;
	std::shared_ptr<ATitleCharacter> Aki;
	std::shared_ptr<ATitleCharacter> Ayame;
	std::shared_ptr<ATitleCharacter> Aqua;
	std::shared_ptr<ATitleCharacter> Melpitsa;
	std::shared_ptr<ATitleCharacter> Olri;
	std::shared_ptr<ATitleCharacter> Rice;
	std::shared_ptr<ATitleCharacter> Eopiputin;
	std::shared_ptr<ATitleCharacter> Hosinoba;
	std::shared_ptr<ATitleCharacter> Laine;
	std::shared_ptr<ATitleCharacter> Kanaeru;
	std::shared_ptr<ATitleCharacter> Cobalskia;
	std::shared_ptr<ATitleCharacter> Zeta;

	std::shared_ptr<AHoloMouse> Mouse;



	float BackSpawnTime = 0;
	void CursorOFF();


};

