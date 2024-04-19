#include "PreCompile.h"
#include "Player.h"
#include "HoloMouse.h"

float4 AHoloMouse::MousePosZero = FVector::Zero;
bool AHoloMouse::MouseAimOn = false;

AHoloMouse::AHoloMouse()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);

	InputOn();
}

AHoloMouse::~AHoloMouse()
{
}

void AHoloMouse::BeginPlay()
{
	Super::BeginPlay();

	MouseCursorOff();
	Renderer->SetSprite("GameCursor_0.png");
	Renderer->SetAutoSize(0.75f, true);
	Renderer->SetOrder(ERenderingOrder::MouseCursor);

	MousePosZero = GEngine->EngineWindow.GetScreenMousePos();
}

void AHoloMouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ChangeCursorAimMode();
	CheckCursorAimMode();

	SetMousePos();

}

// 윈도우 제공 함수 및 매크로를 이용해본다.
void AHoloMouse::MouseCursorOff()
{
	ShowCursor(FALSE);
}

void AHoloMouse::ChangeCursorAimMode()
{
	if (true == IsDown(VK_LBUTTON))
	{
		if (true != MouseAimOn)
		{
			MouseAimOn = true;
		}
		else
		{
			MouseAimOn = false;
		}
	}
}

// 마우스 커서가 하늘색과 핑크색으로 전환되게 해주는 것을 체크해본다.
void AHoloMouse::CheckCursorAimMode()
{
	if (true != MouseAimOn)
	{
		MouseCursorOff();
		Renderer->SetSprite("GameCursor_0.png");
		//Renderer->SetPivot(EPivot::);
	}
	else
	{
		MouseCursorOff();
		Renderer->SetSprite("GameCursor_1.png");
		Renderer->SetPivot(EPivot::MAX);
	}

}

void AHoloMouse::SetMousePos()
{
	FVector MyPos = APlayer::PlayerPosZero;
	MousePosZero = GEngine->EngineWindow.GetScreenMousePos();
	FVector MouseLocation = FVector{ MyPos.X + MousePosZero.X - 640,MyPos.Y - MousePosZero.Y + 360 };


}
