#include "PreCompile.h"
#include "Player.h"
#include "HoloMouse.h"

FVector AHoloMouse::MousePos = FVector::Zero;
bool AHoloMouse::MouseCursorOn = false;

AHoloMouse::AHoloMouse()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	//Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//Renderer->SetupAttachment(Root);


	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale({ 5.0f,5.f });
	Collision->SetPosition({ -10.0f,10.0f });
	Collision->SetCollisionGroup(ECollisionOrder::Player);
	Collision->SetCollisionType(ECollisionType::Rect);



	SetRoot(Root);
	InputOn();
}

AHoloMouse::~AHoloMouse()
{
}

void AHoloMouse::BeginPlay()
{
	Super::BeginPlay();

	MouseRenderer = CreateWidget<UImage>(GetWorld(), "MouseCursor");
	MouseRenderer->SetSprite("GameCursor_0.png");
	MouseRenderer->SetAutoSize(1.00f, true);
	//MouseRenderer->SetAutoSize(HoloCureConstValue::MultipleSize, true);
	MouseRenderer->AddToViewPort(10);

	//MouseRenderer->SetOrder(ERenderingOrder::MouseCursor);
	//MousePos = GEngine->EngineWindow.GetScreenMousePos();
}

void AHoloMouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//SetMousePos(_DeltaTime);
	
	MousePos = GEngine->EngineWindow.GetScreenMousePos();
	FVector MyPos = APlayer::PlayerPos;
	FVector MouseLocation = FVector{ MyPos.X + MousePos.X - 640,MyPos.Y - MousePos.Y + 360 };
	if ("PlayLevel" == GetWorld()->GetName())
	{
		CurCursor();
		Collision->SetPosition({ MyPos.X + 5 , MyPos.Y - 40.0f });
	}
	else
	{
		Collision->SetPosition(MouseLocation);
	}
	CheckCurCursor(MousePos);



}

// 윈도우 제공 함수 및 매크로를 이용해본다.
void AHoloMouse::CursorOFf()
{
	ShowCursor(FALSE);
}

void AHoloMouse::CurCursor()
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
void AHoloMouse::CheckCurCursor(FVector _MousePos)
{
	if (true != MouseCursorOn)
	{
		CursorOFf();
		MouseRenderer->SetSprite("GameCursor_0.png");
		MouseRenderer->SetPosition({ _MousePos.X - 595, -_MousePos.Y + 310 });
	}
	else
	{
		CursorOFf();
		MouseRenderer->SetSprite("GameCursor_1.png");
		MouseRenderer->SetPosition({ _MousePos.X - 640, -_MousePos.Y + 360 });
	}



}

void AHoloMouse::SetMousePos()
{
	//MousePos = GEngine->EngineWindow.GetScreenMousePos();
	//FVector MyPos = APlayer::PlayerPos;
	//FVector MouseLocation = FVector{ MyPos.X + MousePos.X - 640,MyPos.Y - MousePos.Y + 360 };
	//if ("PlayLevel" == GetWorld()->GetName())
	//{
	//	CurCursor();
	//	Collision->SetPosition({ MyPos.X + 5 , MyPos.Y - 40.0f });
	//}
	//else
	//{
	//	Collision->SetPosition(MouseLocation);
	//}
	//CheckCurCursor(MousePos);

	//int a = 0;


}
