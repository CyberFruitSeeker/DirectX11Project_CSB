#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>

// 구라의 움직임, 애니메이션의 실질적인 기능은 이곳에다가 구현한다.

void APlayer::StateUpdate()
{
	// 구라 스테이트 세팅
	GuraState.CreateState("Idle");
	GuraState.CreateState("Run");
	GuraState.CreateState("Die");


	// 함수들을 세팅
	GuraState.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	// 콜백을 배열 처럼 관리하고 불러온다.
	// ex) 콜백[0] 콜백[1] 콜백[2][3][4][5][6]...[8]
	
	Renderer->SetFrameCallback("Run", 0, [=] 
		{
			int a = 0; 
		});


	// 람다 함수(캡쳐) 사용 해본다.
	GuraState.SetStartFunction("Idle", [this]()
		{
			this->Renderer->ChangeAnimation("GuraIdle");
		});

	GuraState.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	GuraState.SetUpdateFunction("Run", std::bind(&APlayer::RunStart, this));


	GuraState.ChangeState("Idle");
}



