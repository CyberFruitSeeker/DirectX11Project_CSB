#include "PreCompile.h"
#include "TitleCharacter.h"

ATitleCharacter::ATitleCharacter()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Ame = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Ame->SetupAttachment(Root);
	Ame->SetPivot(EPivot::BOT);

	//Bae = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Bae->SetupAttachment(Root);
	//Bae->SetPivot(EPivot::BOT);

	Gura = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Gura->SetupAttachment(Root);
	Gura->SetPivot(EPivot::BOT);

	//Mumei = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Mumei->SetupAttachment(Root);
	//Mumei->SetPivot(EPivot::BOT);

	//Fauna = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Fauna->SetupAttachment(Root);
	//Fauna->SetPivot(EPivot::BOT);

	//Suisei = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Suisei->SetupAttachment(Root);
	//Suisei->SetPivot(EPivot::BOT);

	//Sana = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Sana->SetupAttachment(Root);
	//Sana->SetPivot(EPivot::BOT);

	//Shion = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Shion->SetupAttachment(Root);
	//Shion->SetPivot(EPivot::BOT);

	//Sora = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Sora->SetupAttachment(Root);
	//Sora->SetPivot(EPivot::BOT);

	//Subaru = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Subaru->SetupAttachment(Root);
	//Subaru->SetPivot(EPivot::BOT);

	//Mio = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Mio->SetupAttachment(Root);
	//Mio->SetPivot(EPivot::BOT);

	//Okayu = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Okayu->SetupAttachment(Root);
	//Okayu->SetPivot(EPivot::BOT);

	//Roboco = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Roboco->SetupAttachment(Root);
	//Roboco->SetPivot(EPivot::BOT);

	//Kronii = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Kronii->SetupAttachment(Root);
	//Kronii->SetPivot(EPivot::BOT);

	//Matsuri = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Matsuri->SetupAttachment(Root);
	//Matsuri->SetPivot(EPivot::BOT);

	//Mel = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Mel->SetupAttachment(Root);
	//Mel->SetPivot(EPivot::BOT);

	//Miko = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Miko->SetupAttachment(Root);
	//Miko->SetPivot(EPivot::BOT);

	//Ina = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Ina->SetupAttachment(Root);
	//Ina->SetPivot(EPivot::BOT);

	//Irys = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Irys->SetupAttachment(Root);
	//Irys->SetPivot(EPivot::BOT);

	//Kiara = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Kiara->SetupAttachment(Root);
	//Kiara->SetPivot(EPivot::BOT);

	//Korone = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Korone->SetupAttachment(Root);
	//Korone->SetPivot(EPivot::BOT);

	//Fubuki = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Fubuki->SetupAttachment(Root);
	//Fubuki->SetPivot(EPivot::BOT);

	//Haato = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Haato->SetupAttachment(Root);
	//Haato->SetPivot(EPivot::BOT);

	//Azki = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Azki->SetupAttachment(Root);
	//Azki->SetPivot(EPivot::BOT);

	//Calli = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Calli->SetupAttachment(Root);
	//Calli->SetPivot(EPivot::BOT);

	//Choco = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Choco->SetupAttachment(Root);
	//Choco->SetPivot(EPivot::BOT);

	//Aki = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Aki->SetupAttachment(Root);
	//Aki->SetPivot(EPivot::BOT);

	//Ayame = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Ayame->SetupAttachment(Root);
	//Ayame->SetPivot(EPivot::BOT);

	//Aqua = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Aqua->SetupAttachment(Root);
	//Aqua->SetPivot(EPivot::BOT);

	//Melpitsa = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Melpitsa->SetupAttachment(Root);
	//Melpitsa->SetPivot(EPivot::BOT);

	//Olri = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Olri->SetupAttachment(Root);
	//Olri->SetPivot(EPivot::BOT);

	//Rice = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Rice->SetupAttachment(Root);
	//Rice->SetPivot(EPivot::BOT);

	//Eopiputin = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Eopiputin->SetupAttachment(Root);
	//Eopiputin->SetPivot(EPivot::BOT);

	//Hosinoba = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Hosinoba->SetupAttachment(Root);
	//Hosinoba->SetPivot(EPivot::BOT);

	//Laine = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Laine->SetupAttachment(Root);
	//Laine->SetPivot(EPivot::BOT);

	//Kanaeru = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Kanaeru->SetupAttachment(Root);
	//Kanaeru->SetPivot(EPivot::BOT);

	//Cobalskia = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Cobalskia->SetupAttachment(Root);
	//Cobalskia->SetPivot(EPivot::BOT);

	//Zeta = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Zeta->SetupAttachment(Root);
	//Zeta->SetPivot(EPivot::BOT);


	SetRoot(Root);

}

ATitleCharacter::~ATitleCharacter()
{
}

void ATitleCharacter::BeginPlay()
{
	Super::BeginPlay();

	Ame->SetSprite("spr_Title_Gura_2.png");
	Ame->SetAutoSize(2.5f, true);
	Ame->SetPosition({ -150.0f,-350.0f });
	Ame->SetOrder(ERenderingOrder::TitleF);

	//Bae->SetSprite("spr_Title_bae_1.png");
	//Bae->SetAutoSize(2.0f, true);
	//Bae->SetPosition({ -241.0f,-330.0f });
	//Bae->SetOrder(ERenderingOrder::TitleF);

	//Mumei->SetSprite("spr_Title_Mumei_3.png");
	//Mumei->SetAutoSize(2.0f, true);
	//Mumei->SetPosition({ -340.0f,-330.0f });
	//Mumei->SetOrder(ERenderingOrder::TitleF);

	//Fauna->SetSprite("spr_Title_Fauna_4.png");
	//Fauna->SetAutoSize(2.0f, true);
	//Fauna->SetPosition({ -440.0f,-330.0f });
	//Fauna->SetOrder(ERenderingOrder::TitleF);

	//Kronii->SetSprite("spr_Title_Kronii_5.png");
	//Kronii->SetAutoSize(2.0f, true);
	//Kronii->SetPosition({ -550.0f,-300.0f });
	//Kronii->SetOrder(ERenderingOrder::TitleF);

	//Gura->SetSprite("spr_Title_Gura_2.png");
	//Gura->SetAutoSize(2.0f, true);
	//Gura->SetPosition({ -55.0f,-330.0f });
	//Gura->SetOrder(ERenderingOrder::TitleF);

	//Ina->SetSprite("spr_Title_Ina_3.png");
	//Ina->SetAutoSize(2.0f, true);
	//Ina->SetPosition({ 40.0f,-320.0f });
	//Ina->SetOrder(ERenderingOrder::TitleF);

	//Kiara->SetSprite("spr_Title_Kiara_0.png");
	//Kiara->SetAutoSize(2.0f, true);
	//Kiara->SetPosition({ 120.0f,-300.0f });
	//Kiara->SetOrder(ERenderingOrder::TitleF);


}

void ATitleCharacter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

