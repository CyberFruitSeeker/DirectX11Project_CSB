#include "PreCompile.h"
#include "UIManager.h"
#include "Player.h"
#include "PlayGameMode.h"
#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineInput.h>

UIManager::UIManager()
{
	SetBurtonCollision0 = CreateDefaultSubObject<UCollision>("Collision");
	SetBurtonCollision0->SetCollisionGroup(ECollisionOrder::Menu);
	SetBurtonCollision0->SetCollisionType(ECollisionType::Rect);

	SetBurtonCollision1 = CreateDefaultSubObject<UCollision>("Collision");
	SetBurtonCollision1->SetCollisionGroup(ECollisionOrder::Menu);
	SetBurtonCollision1->SetCollisionType(ECollisionType::Rect);

	SetBurtonCollision2 = CreateDefaultSubObject<UCollision>("Collision");
	SetBurtonCollision2->SetCollisionGroup(ECollisionOrder::Menu);
	SetBurtonCollision2->SetCollisionType(ECollisionType::Rect);

	SetBurtonCollision3 = CreateDefaultSubObject<UCollision>("Collision");
	SetBurtonCollision3->SetCollisionGroup(ECollisionOrder::Menu);
	SetBurtonCollision3->SetCollisionType(ECollisionType::Rect);

	SetBurtonCollision4 = CreateDefaultSubObject<UCollision>("Collision");
	SetBurtonCollision4->SetCollisionGroup(ECollisionOrder::Menu);
	SetBurtonCollision4->SetCollisionType(ECollisionType::Rect);

	SetBurtonCollision5 = CreateDefaultSubObject<UCollision>("Collision");
	SetBurtonCollision5->SetCollisionGroup(ECollisionOrder::Menu);
	SetBurtonCollision5->SetCollisionType(ECollisionType::Rect);



	LevelUpCollision0 = CreateDefaultSubObject<UCollision>("Collision");
	LevelUpCollision0->SetCollisionGroup(ECollisionOrder::Menu);
	LevelUpCollision0->SetCollisionType(ECollisionType::Rect);

	LevelUpCollision1 = CreateDefaultSubObject<UCollision>("Collision");
	LevelUpCollision1->SetCollisionGroup(ECollisionOrder::Menu);
	LevelUpCollision1->SetCollisionType(ECollisionType::Rect);

	LevelUpCollision2 = CreateDefaultSubObject<UCollision>("Collision");
	LevelUpCollision2->SetCollisionGroup(ECollisionOrder::Menu);
	LevelUpCollision2->SetCollisionType(ECollisionType::Rect);

	LevelUpCollision3 = CreateDefaultSubObject<UCollision>("Collision");
	LevelUpCollision3->SetCollisionGroup(ECollisionOrder::Menu);
	LevelUpCollision3->SetCollisionType(ECollisionType::Rect);

	InputOn();
}

UIManager::~UIManager()
{
}

void UIManager::BeginPlay()
{
	Super::BeginPlay();
	UISpawn();

	for (int i = 0; i < 4; i++)
	{
		ItemSprites.push_back(CreateWidget<UImage>(GetWorld(), "WeaponSprite"));
		ItemSprites[i]->AddToViewPort(4);
		ItemSprites[i]->SetAutoSize(ContentsValue::MultipleSize, true);
		ItemSprites[i]->SetPosition(FVector(-110.f, 170.f - 130.f * i));
	}

}

void UIManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	TimeUpdate(_DeltaTime);
	KillCountUpdate();
	PauseChack();
	SetBurtonColChack();
	CollisionPos();
	Hp = APlayGameMode::MainPlayer->GetHp();
	HPUpdate();
	ESCPauseChack();
	LevelUpColPos();
	LevelUpColChack();
	LevelPauseChack();
}

void UIManager::UISpawn()
{
	//EXP
	EXPBarBack = CreateWidget<UImage>(GetWorld(), "EXPBarBack");
	EXPBarBack->AddToViewPort(2);
	EXPBarBack->SetSprite("hud_expbar_bg_0.png");
	EXPBarBack->SetAutoSize(ContentsValue::MultipleSize, true);
	EXPBarBack->SetPosition(FVector(10.0f, 340.0f));

	EXPBar = CreateWidget<UImage>(GetWorld(), "EXPBar");
	EXPBar->AddToViewPort(3);
	EXPBar->SetSprite("hud_expbar_gauge_0.png");
	EXPBar->SetAutoSize(ContentsValue::MultipleSize, true);
	EXPBar->SetPosition(FVector(10.0f, 340.0f));

	//HUD
	Character = CreateWidget<UImage>(GetWorld(), "HUDCharacter");
	Character->AddToViewPort(3);
	Character->SetSprite("spr_Gura_Portrait_0.png");
	Character->SetAutoSize(ContentsValue::MultipleSize, true);
	Character->SetPosition(FVector(-590.f, 288.f));

	CharacterFrame = CreateWidget<UImage>(GetWorld(), "HUDCharacterFrame");
	CharacterFrame->AddToViewPort(2);
	CharacterFrame->SetSprite("HUDCharacterFrame.png");
	CharacterFrame->SetAutoSize(ContentsValue::MultipleSize, true);
	CharacterFrame->SetPosition(FVector(-587.f, 293.f));

	HUDHP = CreateWidget<UImage>(GetWorld(), "HUDHP");
	HUDHP->AddToViewPort(2);
	HUDHP->SetSprite("hud_new_HUDHP_0.png");
	HUDHP->SetAutoSize(ContentsValue::MultipleSize, true);
	HUDHP->SetPosition(FVector(-450.f, 269.f));

	HPBar = CreateWidget<UImage>(GetWorld(), "HPBar");
	HPBar->AddToViewPort(2);
	HPBar->SetSprite("hud_HUD_HP_green_0.png");
	HPBar->SetAutoSize(ContentsValue::MultipleSize, true);
	HPBar->SetPosition(FVector(-382.f, 320.f));

	//HUDFrame = CreateWidget<UImage>(GetWorld(), "HUDFrame");
	//HUDFrame->AddToViewPort(2);
	//HUDFrame->SetSprite("hud_new_HUDFrame_0.png");ItemIcon
	//HUDFrame->SetAutoSize(ContentsValue::MultipleSize, true);
	//HUDFrame->SetPosition(FVector(-445.f, 270.0f));

	//WeaponIcon.resize(6);
	//for (int i = 0; i < 6; i++)
	//{
	//	//UImage* WeaponIconBack = CreateWidget<UImage>(GetWorld(), "WeaponIconBack");
	//	//WeaponIconBack->AddToViewPort(1);
	//	//WeaponIconBack->SetSprite("ui_empty_slot_weapon_0.png");
	//	//WeaponIconBack->SetAutoSize(ContentsValue::MultipleSize, true);
	//	//WeaponIconBack->SetPosition(FVector(-520.f + 50.f * i, 275.f));
	//	//WeaponIconBack->SetMulColor({ 1.0f,1.0f,1.0f,0.7f });

	//	//UImage* ITemIcon = CreateWidget<UImage>(GetWorld(), "ITemIconBack");
	//	//ITemIcon->AddToViewPort(1);
	//	//ITemIcon->SetSprite("ui_empty_slot_item_0.png");
	//	//ITemIcon->SetAutoSize(ContentsValue::MultipleSize, true);
	//	//ITemIcon->SetPosition(FVector(-520.f + 50.f * i, 225.f));
	//	//ITemIcon->SetMulColor({ 1.0f,1.0f,1.0f,0.7f });

	//}

	Gold = CreateWidget<UImage>(GetWorld(), "Gold");
	Gold->AddToViewPort(2);
	Gold->SetSprite("ui_holoCoin_0.png");
	Gold->SetAutoSize(ContentsValue::MultipleSize, true);
	Gold->SetPosition(FVector(360.f, 310.0f));

	KillCount = CreateWidget<UImage>(GetWorld(), "KillCount");
	KillCount->AddToViewPort(2);
	KillCount->SetSprite("ui_defeatedEnemies_0.png");
	KillCount->SetAutoSize(ContentsValue::MultipleSize, true);
	KillCount->SetPosition(FVector(360.f, 275.0f));

	TimeUI = CreateWidget<UTextWidget>(GetWorld(), "Time");
	TimeUI->AddToViewPort(5);
	TimeUI->SetScale(ContentsValue::MultipleSize * 15);
	TimeUI->SetFont("Galmuri9");
	TimeUI->SetColor(Color8Bit::White);
	TimeUI->SetPosition(FVector(0.f, 285.f));
	TimeUI->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_CENTER | FW1_TEXT_FLAG::FW1_VCENTER));

	StageText = CreateWidget<UImage>(GetWorld(), "StageText");
	StageText->AddToViewPort(5);
	StageText->SetSprite("STAGE.png");
	StageText->SetAutoSize(1.0f, true);
	StageText->SetPosition(FVector(0.f, 310.f));

	//ESC누른 후
	PauseBack = CreateWidget<UImage>(GetWorld(), "PuaseBack");
	PauseBack->AddToViewPort(1);
	PauseBack->SetSprite("menu_charselecLocked_0.png");
	PauseBack->SetAutoSize(ContentsValue::MultipleSize * 15, true);
	PauseBack->SetPosition(FVector(0.f, 0.f));
	PauseBack->SetActive(false);

	PausedText = CreateWidget<UImage>(GetWorld(), "PausedText");
	PausedText->AddToViewPort(5);
	PausedText->SetSprite("Paused.png");
	PausedText->SetAutoSize(ContentsValue::MultipleSize / 2, true);
	PausedText->SetPosition(FVector(0.f, 200.f));
	PausedText->SetActive(false);

	SetBack = CreateWidget<UImage>(GetWorld(), "SetBack");
	SetBack->AddToViewPort(1);
	SetBack->SetSprite("hud_pausemenu_0.png");
	SetBack->SetAutoSize(ContentsValue::MultipleSize, true);
	SetBack->SetPosition(FVector(0.f, 0.f));
	SetBack->SetActive(false);


	CharacterBack = CreateWidget<UImage>(GetWorld(), "SetBack");
	CharacterBack->AddToViewPort(1);
	CharacterBack->SetSprite("spr_Title_Kiara_0.png");
	CharacterBack->SetAutoSize(ContentsValue::MultipleSize * 1.5, true);
	CharacterBack->SetPosition(FVector(-550.f, 0.f));
	CharacterBack->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
	CharacterBack->SetActive(false);

	for (int i = 0; i < 6; i++)
	{
		UImage* SetBurton = CreateWidget<UImage>(GetWorld(), "SetBurton");
		SetBurton->AddToViewPort(2);
		SetBurton->SetSprite("hud_Button_0.png");
		SetBurton->SetAutoSize(ContentsValue::MultipleSize * 1.3, true);
		SetBurton->SetPosition(FVector(0.f, 120.f - 60.f * i));
		SetBurton->SetActive(false);
		SetBurtonVector.push_back(SetBurton);

	}

	SetBurtonCollision0->SetScale({ 180.0f,50.0f });
	SetBurtonCollision1->SetScale({ 180.0f,50.0f });
	SetBurtonCollision2->SetScale({ 180.0f,50.0f });
	SetBurtonCollision3->SetScale({ 180.0f,50.0f });
	SetBurtonCollision4->SetScale({ 180.0f,50.0f });
	SetBurtonCollision5->SetScale({ 180.0f,50.0f });



	for (int i = 0; i < 6; i++)
	{
		UImage* StatLine = CreateWidget<UImage>(GetWorld(), "StatLine");
		StatLine->AddToViewPort(2);
		StatLine->SetSprite("ui_menu_stats_divider_0.png");
		StatLine->SetAutoSize(ContentsValue::MultipleSize, true);
		StatLine->SetPosition(FVector(-400.f, -10.f - 45.f * i));
		StatLine->SetActive(false);
		StatLineVector.push_back(StatLine);
	}

	HP = CreateWidget<UImage>(GetWorld(), "PuaseHP");
	HP->AddToViewPort(2);
	HP->SetSprite("hud_HPicon_0.png");
	HP->SetAutoSize(ContentsValue::MultipleSize, true);
	HP->SetPosition(FVector(-550.f, 0.f));
	HP->SetActive(false);

	ATK = CreateWidget<UImage>(GetWorld(), "PuaseATK");
	ATK->AddToViewPort(2);
	ATK->SetSprite("hud_atkicon_0.png");
	ATK->SetAutoSize(ContentsValue::MultipleSize, true);
	ATK->SetPosition(FVector(-550.f, -42.f));
	ATK->SetActive(false);

	SPD = CreateWidget<UImage>(GetWorld(), "PuaseSPD");
	SPD->AddToViewPort(2);
	SPD->SetSprite("hud_spdicon_0.png");
	SPD->SetAutoSize(ContentsValue::MultipleSize, true);
	SPD->SetPosition(FVector(-550.f, -84.f));
	SPD->SetActive(false);

	CRT = CreateWidget<UImage>(GetWorld(), "PuaseCRT");
	CRT->AddToViewPort(2);
	CRT->SetSprite("hud_criticon_0.png");
	CRT->SetAutoSize(ContentsValue::MultipleSize, true);
	CRT->SetPosition(FVector(-550.f, -130.f));
	CRT->SetActive(false);

	PickUP = CreateWidget<UImage>(GetWorld(), "PuasePickUP");
	PickUP->AddToViewPort(2);
	PickUP->SetSprite("hud_pickupicon_0.png");
	PickUP->SetAutoSize(ContentsValue::MultipleSize, true);
	PickUP->SetPosition(FVector(-550.f, -178.f));
	PickUP->SetActive(false);

	Haste = CreateWidget<UImage>(GetWorld(), "PuaseHaste");
	Haste->AddToViewPort(2);
	Haste->SetSprite("hud_cooldownicon_0.png");
	Haste->SetAutoSize(ContentsValue::MultipleSize, true);
	Haste->SetPosition(FVector(-550.f, -220.f));
	Haste->SetActive(false);

	// LevelUp UI
	LevelUpText = CreateWidget<UImage>(GetWorld(), "LevelUpText");
	LevelUpText->AddToViewPort(2);
	LevelUpText->SetSprite("ui_menu_upgrade_title_0.png");
	LevelUpText->SetAutoSize(ContentsValue::MultipleSize, true);
	LevelUpText->SetPosition(FVector(-400.f, 130.f));

	LevelUpIconsCross = CreateWidget<UImage>(GetWorld(), "LevelUpIconsCross");
	LevelUpIconsCross->AddToViewPort(3);
	LevelUpIconsCross->SetSprite("CrossIcon.png");
	LevelUpIconsCross->SetAutoSize(ContentsValue::MultipleSize, true);
	LevelUpIconsCross->SetPosition(FVector(-110.f, 170.f));

	//LevelUpIconsItem = CreateWidget<UImage>(GetWorld(), "LevelUpIconsItem");
	//LevelUpIconsItem->AddToViewPort(3);
	//LevelUpIconsItem->SetSprite("ItemIcon.png");
	//LevelUpIconsItem->SetAutoSize(ContentsValue::MultipleSize, true);
	//LevelUpIconsItem->SetPosition(FVector(-110.f, 40.f));

	LevelUpIconsStar = CreateWidget<UImage>(GetWorld(), "LevelUpIconsStar");
	LevelUpIconsStar->AddToViewPort(3);
	LevelUpIconsStar->SetSprite("StarIcon.png");
	LevelUpIconsStar->SetAutoSize(ContentsValue::MultipleSize, true);
	LevelUpIconsStar->SetPosition(FVector(-110.f, -90.f));

	//LevelUpIconsWeapon = CreateWidget<UImage>(GetWorld(), "LevelUpIconsWeapon");
	//LevelUpIconsWeapon->AddToViewPort(3);
	//LevelUpIconsWeapon->SetSprite("WeaponIcon.png");
	//LevelUpIconsWeapon->SetAutoSize(ContentsValue::MultipleSize, true);
	//LevelUpIconsWeapon->SetPosition(FVector(-110.f, -220.f));

	WeaponText = CreateWidget<UTextWidget>(GetWorld(), "WeaponText");
	WeaponText->AddToViewPort(3);
	WeaponText->SetScale(ContentsValue::MultipleSize * 9);
	WeaponText->SetFont("Galmuri9");
	WeaponText->SetColor(Color8Bit::White);
	WeaponText->SetText("Test");
	WeaponText->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	WeaponText->SetPosition(FVector(-140.f, 240.f));

	StarText = CreateWidget<UTextWidget>(GetWorld(), "StarText");
	StarText->AddToViewPort(3);
	StarText->SetScale(ContentsValue::MultipleSize * 9);
	StarText->SetFont("Galmuri9");
	StarText->SetColor(Color8Bit::White);
	StarText->SetText("Test");
	StarText->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	StarText->SetPosition(FVector(-140.f, 110.f));

	CrossText = CreateWidget<UTextWidget>(GetWorld(), "CrossText");
	CrossText->AddToViewPort(3);
	CrossText->SetScale(ContentsValue::MultipleSize * 9);
	CrossText->SetFont("Galmuri9");
	CrossText->SetColor(Color8Bit::White);
	CrossText->SetText("Test");
	CrossText->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	CrossText->SetPosition(FVector(-140.f, -20.f));

	ItemText = CreateWidget<UTextWidget>(GetWorld(), "ItemText");
	ItemText->AddToViewPort(3);
	ItemText->SetScale(ContentsValue::MultipleSize * 9);
	ItemText->SetFont("Galmuri9");
	ItemText->SetColor(Color8Bit::White);
	ItemText->SetText("Test");
	ItemText->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	ItemText->SetPosition(FVector(-140.f, -150.f));

	//ItemTextExplanation = CreateWidget<UTextWidget>(GetWorld(), "ItemTextExplanation");
	//ItemTextExplanation->AddToViewPort(3);
	//ItemTextExplanation->SetScale(ContentsValue::MultipleSize * 9);
	//ItemTextExplanation->SetFont("Galmuri9");
	//ItemTextExplanation->SetColor(Color8Bit::White);
	//ItemTextExplanation->SetText("TestTestTestTestTestTestTestTestTestTestTestTestTest\nTestTestTestTest");
	//ItemTextExplanation->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	//ItemTextExplanation->SetPosition(FVector(-50.f, 200.f));

	//CrossTextExplanation = CreateWidget<UTextWidget>(GetWorld(), "CrossTextExplanation");
	//CrossTextExplanation->AddToViewPort(3);
	//CrossTextExplanation->SetScale(ContentsValue::MultipleSize * 9);
	//CrossTextExplanation->SetFont("Galmuri9");
	//CrossTextExplanation->SetColor(Color8Bit::White);
	//CrossTextExplanation->SetText("TestTestTestTestTestTestTestTestTestTestTestTestTest\nTestTestTestTest");
	//CrossTextExplanation->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	//CrossTextExplanation->SetPosition(FVector(-50.f, 70.f));

	//StarTextExplanation = CreateWidget<UTextWidget>(GetWorld(), "StarTextExplanation");
	//StarTextExplanation->AddToViewPort(3);
	//StarTextExplanation->SetScale(ContentsValue::MultipleSize * 9);
	//StarTextExplanation->SetFont("Galmuri9");
	//StarTextExplanation->SetColor(Color8Bit::White);
	//StarTextExplanation->SetText("TestTestTestTestTestTestTestTestTestTestTestTestTest\nTestTestTestTest");
	//StarTextExplanation->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	//StarTextExplanation->SetPosition(FVector(-50.f, -60.f));

	//WeaponTextExplanation = CreateWidget<UTextWidget>(GetWorld(), "WeaponTextExplanation");
	//WeaponTextExplanation->AddToViewPort(3);
	//WeaponTextExplanation->SetScale(ContentsValue::MultipleSize * 9);
	//WeaponTextExplanation->SetFont("Galmuri9");
	//WeaponTextExplanation->SetColor(Color8Bit::White);
	//WeaponTextExplanation->SetText("TestTestTestTestTestTestTestTestTestTestTestTestTest\nTestTestTestTest");
	//WeaponTextExplanation->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	//WeaponTextExplanation->SetPosition(FVector(-50.f, -190.f));


	New0 = CreateWidget<UTextWidget>(GetWorld(), "New0");
	New0->AddToViewPort(3);
	New0->SetScale(ContentsValue::MultipleSize * 10);
	New0->SetFont("Galmuri9");
	New0->SetColor(Color8Bit::Yellow);
	New0->SetText("신규!");
	New0->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	New0->SetPosition(FVector(300.f, 240.f));

	New1 = CreateWidget<UTextWidget>(GetWorld(), "New1");
	New1->AddToViewPort(3);
	New1->SetScale(ContentsValue::MultipleSize * 10);
	New1->SetFont("Galmuri9");
	New1->SetColor(Color8Bit::Yellow);
	New1->SetText("신규!");
	New1->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	New1->SetPosition(FVector(300.f, 110.f));

	New2 = CreateWidget<UTextWidget>(GetWorld(), "New2");
	New2->AddToViewPort(3);
	New2->SetScale(ContentsValue::MultipleSize * 10);
	New2->SetFont("Galmuri9");
	New2->SetColor(Color8Bit::Yellow);
	New2->SetText("신규!");
	New2->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	New2->SetPosition(FVector(300.f, -20.f));

	New3 = CreateWidget<UTextWidget>(GetWorld(), "New3");
	New3->AddToViewPort(3);
	New3->SetScale(ContentsValue::MultipleSize * 10);
	New3->SetFont("Galmuri9");
	New3->SetColor(Color8Bit::Yellow);
	New3->SetText("신규!");
	New3->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT));
	New3->SetPosition(FVector(300.f, -150.f));

	for (int i = 0; i < 4; i++)
	{
		UImage* LevelUpSelectBack = CreateWidget<UImage>(GetWorld(), "LevelUpSelectBack");
		LevelUpSelectBack->AddToViewPort(2);
		LevelUpSelectBack->SetSprite("ui_menu_upgrade_window_0.png");
		LevelUpSelectBack->SetAutoSize(ContentsValue::MultipleSize, true);
		LevelUpSelectBack->SetPosition(FVector(200.0f, 180.f - 130.f * i));
		LevelUpSelectBackVector.push_back(LevelUpSelectBack);
	}

	LevelUpCollision0->SetScale({ 770.0f,125.0f });
	LevelUpCollision1->SetScale({ 770.0f,125.0f });
	LevelUpCollision2->SetScale({ 770.0f,125.0f });
	LevelUpCollision3->SetScale({ 770.0f,125.0f });

	// UI TEXT
	HPText = CreateWidget<UTextWidget>(GetWorld(), "HP");
	HPText->AddToViewPort(4);
	HPText->SetScale(15.f);
	HPText->SetFont("Galmuri9");
	HPText->SetColor(Color8Bit::White);
	HPText->SetPosition(FVector(-225.f, 320.f));

	HPTextBack = CreateWidget<UTextWidget>(GetWorld(), "HP");
	HPTextBack->AddToViewPort(3);
	HPTextBack->SetScale(ContentsValue::MultipleSize * 8);
	HPTextBack->SetFont("Galmuri9");
	HPTextBack->SetColor(Color8Bit::Black);
	HPTextBack->SetPosition(FVector(-225.f, 320.f));

	KillCountText = CreateWidget<UTextWidget>(GetWorld(), "KillCount");
	KillCountText->AddToViewPort(3);
	KillCountText->SetScale(ContentsValue::MultipleSize * 10);
	KillCountText->SetFont("Galmuri9");
	KillCountText->SetColor(Color8Bit::White);
	KillCountText->SetPosition(FVector(385.f, 275.f));
	KillCountText->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT | FW1_TEXT_FLAG::FW1_VCENTER));

	// StatUI TEXT
	StatHPText = CreateWidget<UTextWidget>(GetWorld(), "StatHPText");
	StatHPText->AddToViewPort(3);
	StatHPText->SetScale(ContentsValue::MultipleSize * 10);
	StatHPText->SetFont("Galmuri9");
	StatHPText->SetColor(Color8Bit::White);
	StatHPText->SetPosition(FVector(-507.f, 4.f));
	StatHPText->SetText("HP");
	StatHPText->SetActive(false);

	StatATKText = CreateWidget<UTextWidget>(GetWorld(), "StatATKText");
	StatATKText->AddToViewPort(3);
	StatATKText->SetScale(ContentsValue::MultipleSize * 10);
	StatATKText->SetFont("Galmuri9");
	StatATKText->SetColor(Color8Bit::White);
	StatATKText->SetPosition(FVector(-504.f, -40.f));
	StatATKText->SetText("ATK");
	StatATKText->SetActive(false);

	StatSPDText = CreateWidget<UTextWidget>(GetWorld(), "StatSPDText");
	StatSPDText->AddToViewPort(3);
	StatSPDText->SetScale(ContentsValue::MultipleSize * 10);
	StatSPDText->SetFont("Galmuri9");
	StatSPDText->SetColor(Color8Bit::White);
	StatSPDText->SetPosition(FVector(-504.f, -84.f));
	StatSPDText->SetText("SPD");
	StatSPDText->SetActive(false);

	StatCRTText = CreateWidget<UTextWidget>(GetWorld(), "StatCRTText");
	StatCRTText->AddToViewPort(3);
	StatCRTText->SetScale(ContentsValue::MultipleSize * 10);
	StatCRTText->SetFont("Galmuri9");
	StatCRTText->SetColor(Color8Bit::White);
	StatCRTText->SetPosition(FVector(-503.f, -128.f));
	StatCRTText->SetText("CRT");
	StatCRTText->SetActive(false);

	StatPickUPText = CreateWidget<UTextWidget>(GetWorld(), "StatPickUPText");
	StatPickUPText->AddToViewPort(3);
	StatPickUPText->SetScale(ContentsValue::MultipleSize * 10);
	StatPickUPText->SetFont("Galmuri9");
	StatPickUPText->SetColor(Color8Bit::White);
	StatPickUPText->SetPosition(FVector(-490.f, -175.f));
	StatPickUPText->SetText("PickUP");
	StatPickUPText->SetActive(false);

	StatHasteText = CreateWidget<UTextWidget>(GetWorld(), "StatHasteText");
	StatHasteText->AddToViewPort(3);
	StatHasteText->SetScale(ContentsValue::MultipleSize * 10);
	StatHasteText->SetFont("Galmuri9");
	StatHasteText->SetColor(Color8Bit::White);
	StatHasteText->SetPosition(FVector(-493.f, -218.f));
	StatHasteText->SetText("Haste");
	StatHasteText->SetActive(false);

	PauseSkillText = CreateWidget<UTextWidget>(GetWorld(), "PuaseSkillText");
	PauseSkillText->AddToViewPort(2);
	PauseSkillText->SetScale(ContentsValue::MultipleSize * 11);
	PauseSkillText->SetFont("Galmuri9");
	PauseSkillText->SetColor(Color8Bit::White);
	PauseSkillText->SetPosition(FVector(0.f, 125.f));
	PauseSkillText->SetText("스킬");
	PauseSkillText->SetActive(false);

	PauseStampText = CreateWidget<UTextWidget>(GetWorld(), "PuaseStampText");
	PauseStampText->AddToViewPort(2);
	PauseStampText->SetScale(ContentsValue::MultipleSize * 11);
	PauseStampText->SetFont("Galmuri9");
	PauseStampText->SetColor(Color8Bit::White);
	PauseStampText->SetPosition(FVector(0.f, 65.f));
	PauseStampText->SetText("스탬프");
	PauseStampText->SetActive(false);

	PauseCollaborationText = CreateWidget<UTextWidget>(GetWorld(), "PuaseCollaborationText");
	PauseCollaborationText->AddToViewPort(2);
	PauseCollaborationText->SetScale(ContentsValue::MultipleSize * 11);
	PauseCollaborationText->SetFont("Galmuri9");
	PauseCollaborationText->SetColor(Color8Bit::White);
	PauseCollaborationText->SetPosition(FVector(0.f, 5.f));
	PauseCollaborationText->SetText("콜라보");
	PauseCollaborationText->SetActive(false);

	PauseContinueText = CreateWidget<UTextWidget>(GetWorld(), "PuaseContinueText");
	PauseContinueText->AddToViewPort(2);
	PauseContinueText->SetScale(ContentsValue::MultipleSize * 11);
	PauseContinueText->SetFont("Galmuri9");
	PauseContinueText->SetColor(Color8Bit::White);
	PauseContinueText->SetPosition(FVector(0.f, -55.f));
	PauseContinueText->SetText("이어서 하기");
	PauseContinueText->SetActive(false);

	PauseSettingText = CreateWidget<UTextWidget>(GetWorld(), "PuaseSettingText");
	PauseSettingText->AddToViewPort(2);
	PauseSettingText->SetScale(ContentsValue::MultipleSize * 11);
	PauseSettingText->SetFont("Galmuri9");
	PauseSettingText->SetColor(Color8Bit::White);
	PauseSettingText->SetPosition(FVector(0.f, -115.f));
	PauseSettingText->SetText("설정");
	PauseSettingText->SetActive(false);

	PauseExitText = CreateWidget<UTextWidget>(GetWorld(), "PuaseExitText");
	PauseExitText->AddToViewPort(2);
	PauseExitText->SetScale(ContentsValue::MultipleSize * 11);
	PauseExitText->SetFont("Galmuri9");
	PauseExitText->SetColor(Color8Bit::White);
	PauseExitText->SetPosition(FVector(0.f, -175.f));
	PauseExitText->SetText("나가기");
	PauseExitText->SetActive(false);
}

void UIManager::TimeUpdate(float _DeltaTime)
{
	ContentsValue::Time += _DeltaTime;

	int Time = static_cast<int>(ContentsValue::Time);
	int Second = Time % 60;
	int Minute = Time / 60;

	std::string SecondZeroPadding = "00" + std::to_string(Second);
	std::string MinuteZeroPadding = "00" + std::to_string(Minute);

	std::string SecondText = SecondZeroPadding.substr(SecondZeroPadding.size() - 2, 2);
	std::string MinuteText = MinuteZeroPadding.substr(MinuteZeroPadding.size() - 2, 2);

	TimeUI->SetText(MinuteText + " : " + SecondText);


}

void UIManager::KillCountUpdate()
{
	KillCountText->SetText(std::to_string(ContentsValue::KillCount));

}

void UIManager::HPUpdate()
{
	HPText->SetText(std::to_string(lround(Hp)));
	HPTextBack->SetText(std::to_string(lround(Hp)));

}

void UIManager::ESCPauseChack()
{
	if (true == APlayGameMode::ESCPauseON)
	{
		PausedText->SetActive(true);
		SetBack->SetActive(true);
		for (SetBurtonIter = SetBurtonVector.begin(); SetBurtonIter != SetBurtonVector.end(); SetBurtonIter++)
		{
			UImage* SetBurton = *SetBurtonIter;

			SetBurton->SetActive(true);
		}
		PauseSkillText->SetActive(true);
		PauseStampText->SetActive(true);
		PauseCollaborationText->SetActive(true);
		PauseContinueText->SetActive(true);
		PauseSettingText->SetActive(true);
		PauseExitText->SetActive(true);
	}
	else
	{
		PausedText->SetActive(false);
		SetBack->SetActive(false);
		for (SetBurtonIter = SetBurtonVector.begin(); SetBurtonIter != SetBurtonVector.end(); SetBurtonIter++)
		{
			UImage* SetBurton = *SetBurtonIter;

			SetBurton->SetActive(false);
		}
		PauseSkillText->SetActive(false);
		PauseStampText->SetActive(false);
		PauseCollaborationText->SetActive(false);
		PauseContinueText->SetActive(false);
		PauseSettingText->SetActive(false);
		PauseExitText->SetActive(false);
	}

}

void UIManager::LevelPauseChack()
{
	if (true == APlayGameMode::LevelUpPasueON)
	{
		LevelUpText->SetActive(true);
		LevelUpIconsCross->SetActive(true);
		//LevelUpIconsItem->SetActive(true);
		LevelUpIconsStar->SetActive(true);
		//LevelUpIconsWeapon->SetActive(true);
		WeaponText->SetActive(true);
		StarText->SetActive(true);
		CrossText->SetActive(true);
		ItemText->SetActive(true);
		ItemTextExplanation->SetActive(true);
		CrossTextExplanation->SetActive(true);
		StarTextExplanation->SetActive(true);
		WeaponTextExplanation->SetActive(true);
		New0->SetActive(true);
		New1->SetActive(true);
		New2->SetActive(true);
		New3->SetActive(true);
		for (int i = 0; i < 4; i++)
		{
			LevelUpSelectBackVector[i]->SetActive(true);

		}

		if (!IsIcon)
		{
			RendomIcon();
			IsIcon = true;
		}
	}
	else
	{
		LevelUpText->SetActive(false);
		LevelUpIconsCross->SetActive(false);
		//LevelUpIconsItem->SetActive(false);
		LevelUpIconsStar->SetActive(false);
		//LevelUpIconsWeapon->SetActive(false);
		WeaponText->SetActive(false);
		StarText->SetActive(false);
		CrossText->SetActive(false);
		ItemText->SetActive(false);
		//ItemTextExplanation->SetActive(false);
		//CrossTextExplanation->SetActive(false);
		//StarTextExplanation->SetActive(false);
		//WeaponTextExplanation->SetActive(false);
		New0->SetActive(false);
		New1->SetActive(false);
		New2->SetActive(false);
		New3->SetActive(false);
		for (int i = 0; i < 4; i++)
		{
			LevelUpSelectBackVector[i]->SetActive(false);

		}
		if (true == IsIcon)
		{
			IsIcon = false;
		}
	}

}

void UIManager::PauseChack()
{
	if (true == APlayGameMode::IsPause)
	{
		PauseBack->SetActive(true);
		HP->SetActive(true);
		ATK->SetActive(true);
		SPD->SetActive(true);
		CRT->SetActive(true);
		PickUP->SetActive(true);
		Haste->SetActive(true);
		CharacterBack->SetActive(true);

		StatHPText->SetActive(true);
		StatATKText->SetActive(true);
		StatSPDText->SetActive(true);
		StatCRTText->SetActive(true);
		StatPickUPText->SetActive(true);
		StatHasteText->SetActive(true);


		for (StatLineIter = StatLineVector.begin(); StatLineIter != StatLineVector.end(); StatLineIter++)
		{
			UImage* StatLine = *StatLineIter;

			StatLine->SetActive(true);
		}
	}
	else
	{
		PauseBack->SetActive(false);
		HP->SetActive(false);
		ATK->SetActive(false);
		SPD->SetActive(false);
		CRT->SetActive(false);
		PickUP->SetActive(false);
		Haste->SetActive(false);
		CharacterBack->SetActive(false);

		StatHPText->SetActive(false);
		StatATKText->SetActive(false);
		StatSPDText->SetActive(false);
		StatCRTText->SetActive(false);
		StatPickUPText->SetActive(false);
		StatHasteText->SetActive(false);

		for (StatLineIter = StatLineVector.begin(); StatLineIter != StatLineVector.end(); StatLineIter++)
		{
			UImage* StatLine = *StatLineIter;

			StatLine->SetActive(false);
		}
	}

}

void UIManager::SetBurtonColChack()
{
	for (SetBurtonIter = SetBurtonVector.begin(); SetBurtonIter != SetBurtonVector.end(); SetBurtonIter++)
	{
		UImage* SetBurton = *SetBurtonIter;

		SetBurtonCollision0->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[0]->SetSprite("hud_Button_1.png");
				PauseSkillText->SetColor(Color8Bit::Black);
			}
		);
		SetBurtonCollision0->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[0]->SetSprite("hud_Button_0.png");
				PauseSkillText->SetColor(Color8Bit::White);
			}
		);

		SetBurtonCollision1->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[1]->SetSprite("hud_Button_1.png");
				PauseStampText->SetColor(Color8Bit::Black);
			}
		);
		SetBurtonCollision1->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[1]->SetSprite("hud_Button_0.png");
				PauseStampText->SetColor(Color8Bit::White);
			}
		);

		SetBurtonCollision2->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[2]->SetSprite("hud_Button_1.png");
				PauseCollaborationText->SetColor(Color8Bit::Black);
			}
		);
		SetBurtonCollision2->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[2]->SetSprite("hud_Button_0.png");
				PauseCollaborationText->SetColor(Color8Bit::White);
			}
		);

		SetBurtonCollision3->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[3]->SetSprite("hud_Button_1.png");
				PauseContinueText->SetColor(Color8Bit::Black);
			}
		);
		SetBurtonCollision3->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[3]->SetSprite("hud_Button_0.png");
				PauseContinueText->SetColor(Color8Bit::White);
			}
		);

		SetBurtonCollision4->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[4]->SetSprite("hud_Button_1.png");
				PauseSettingText->SetColor(Color8Bit::Black);
			}
		);
		SetBurtonCollision4->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[4]->SetSprite("hud_Button_0.png");
				PauseSettingText->SetColor(Color8Bit::White);
			}
		);

		SetBurtonCollision5->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[5]->SetSprite("hud_Button_1.png");
				PauseExitText->SetColor(Color8Bit::Black);
				ExitCheck = true;
			}
		);
		SetBurtonCollision5->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
			{
				SetBurtonVector[5]->SetSprite("hud_Button_0.png");
				PauseExitText->SetColor(Color8Bit::White);
				ExitCheck = false;
			}
		);

		if (true == IsDown(VK_LBUTTON) && true == ExitCheck)
		{
			GEngine->ChangeLevel("TitleLevel");
		}
	}

}

void UIManager::CollisionPos()
{
	SetBurtonCollision0->SetPosition(APlayer::PlayerPos);
	SetBurtonCollision0->AddPosition(FVector::Up * 80);
	SetBurtonCollision1->SetPosition(APlayer::PlayerPos);
	SetBurtonCollision1->AddPosition(FVector::Up * 20);
	SetBurtonCollision2->SetPosition(APlayer::PlayerPos);
	SetBurtonCollision2->AddPosition(FVector::Down * 40);
	SetBurtonCollision3->SetPosition(APlayer::PlayerPos);
	SetBurtonCollision3->AddPosition(FVector::Down * 100);
	SetBurtonCollision4->SetPosition(APlayer::PlayerPos);
	SetBurtonCollision4->AddPosition(FVector::Down * 160);
	SetBurtonCollision5->SetPosition(APlayer::PlayerPos);
	SetBurtonCollision5->AddPosition(FVector::Down * 220);

}

void UIManager::LevelUpColChack()
{
	if (true == APlayGameMode::LevelUpPasueON)
	{
		for (LevelUpSelectBackIter = LevelUpSelectBackVector.begin(); LevelUpSelectBackIter != LevelUpSelectBackVector.end(); LevelUpSelectBackIter++)
		{
			UImage* LevelUpSelectBack = *LevelUpSelectBackIter;


			LevelUpCollision0->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[0]->SetSprite("ui_menu_upgrade_window_1.png");
					PauseCollaborationText->SetColor(Color8Bit::Black);
				}
			);
			LevelUpCollision0->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[0]->SetSprite("ui_menu_upgrade_window_0.png");
					PauseCollaborationText->SetColor(Color8Bit::White);
				}
			);

			LevelUpCollision1->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[1]->SetSprite("ui_menu_upgrade_window_1.png");
					PauseContinueText->SetColor(Color8Bit::Black);
				}
			);
			LevelUpCollision1->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[1]->SetSprite("ui_menu_upgrade_window_0.png");
					PauseContinueText->SetColor(Color8Bit::White);
				}
			);

			LevelUpCollision2->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[2]->SetSprite("ui_menu_upgrade_window_1.png");
					PauseSettingText->SetColor(Color8Bit::Black);
				}
			);
			LevelUpCollision2->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[2]->SetSprite("ui_menu_upgrade_window_0.png");
					PauseSettingText->SetColor(Color8Bit::White);
				}
			);

			LevelUpCollision3->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[3]->SetSprite("ui_menu_upgrade_window_1.png");
					PauseExitText->SetColor(Color8Bit::Black);
				}
			);
			LevelUpCollision3->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
				{
					LevelUpSelectBackVector[3]->SetSprite("ui_menu_upgrade_window_0.png");
					PauseExitText->SetColor(Color8Bit::White);
				}
			);
		}
	}

}

void UIManager::LevelUpColPos()
{
	LevelUpCollision0->SetPosition(APlayer::PlayerPos);
	LevelUpCollision0->AddPosition(FVector::Up * 144);
	LevelUpCollision0->AddPosition(FVector::Right * 200);
	LevelUpCollision1->SetPosition(APlayer::PlayerPos);
	LevelUpCollision1->AddPosition(FVector::Up * 12);
	LevelUpCollision1->AddPosition(FVector::Right * 200);
	LevelUpCollision2->SetPosition(APlayer::PlayerPos);
	LevelUpCollision2->AddPosition(FVector::Down * 117);
	LevelUpCollision2->AddPosition(FVector::Right * 200);
	LevelUpCollision3->SetPosition(APlayer::PlayerPos);
	LevelUpCollision3->AddPosition(FVector::Down * 247);
	LevelUpCollision3->AddPosition(FVector::Right * 200);

}

void UIManager::RendomIcon()
{


}
