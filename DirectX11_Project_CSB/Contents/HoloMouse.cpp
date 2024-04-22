#include "PreCompile.h"
#include "Player.h"
#include "HoloMouse.h"

FVector AHoloMouse::MousePos = FVector::Zero;
bool AHoloMouse::MouseCursorOn = false;

AHoloMouse::AHoloMouse()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	InputOn();
}

AHoloMouse::~AHoloMouse()
{
}

void AHoloMouse::BeginPlay()
{
	Super::BeginPlay();

	
	Renderer->SetSprite("GameCursor_0.png");
	Renderer->SetAutoSize(0.75f, true);
	Renderer->SetOrder(ERenderingOrder::MouseCursor);

	//MousePos = GEngine->EngineWindow.GetScreenMousePos();
}

void AHoloMouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	MouseCursorOff();
	
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
		if (true != MouseCursorOn)
		{
			MouseCursorOn = true;
		}
		else
		{
			MouseCursorOn = false;
		}
	}
}

// 마우스 커서가 하늘색과 핑크색으로 전환되게 해주는 것을 체크해본다.
void AHoloMouse::CheckCursorAimMode()
{
	if (true != MouseCursorOn)
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
	FVector MyPos = APlayer::PlayerPos;
	MousePos = GEngine->EngineWindow.GetScreenMousePos();
	FVector MouseLocation = FVector{ MyPos.X + MousePos.X - 640,MyPos.Y - MousePos.Y + 360 };
	SetActorLocation(MouseLocation);

}
