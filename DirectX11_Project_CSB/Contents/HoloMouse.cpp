#include "PreCompile.h"
#include "Player.h"
#include "HoloMouse.h"

float4 AHoloMouse::CursorPosZero = FVector::Zero;
bool AHoloMouse::MouseAimOn = false;

AHoloMouse::AHoloMouse()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Root);
	Renderer->SetupAttachment(Root);
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

	CursorPosZero = GEngine->EngineWindow.GetScreenMousePos();
}

void AHoloMouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ChangeCursorAimMode();
	CheckCursorAimMode();

}

// ������ ���� �Լ� �� ��ũ�θ� �̿��غ���.
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

// ���콺 Ŀ���� �ϴû��� ��ũ������ ��ȯ�ǰ� ���ִ� ���� üũ�غ���.
void AHoloMouse::CheckCursorAimMode()
{
	if (true != MouseAimOn)
	{
		MouseCursorOff();
		Renderer->SetSprite("GameCursor_0.png");
		Renderer->SetPivot(EPivot::LEFTTOP);
	}
	else
	{
		MouseCursorOff();
		Renderer->SetSprite("GameCursor_1.png");
		Renderer->SetPivot(EPivot::MAX);
	}

}
