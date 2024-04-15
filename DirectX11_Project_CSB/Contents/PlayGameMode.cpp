#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "PlayBackLayer.h"
#include "HoloCureConstValue.h"
#include <random>
#include <EngineCore/Camera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();



	//Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	// ===== 맵과 무한맵에 관한 것들 =====
	// (스테이지1)무한맵에서 플레이어와 카메라 위치 조절
	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::FindRes("Holo_map_01.png");
	CurIndex = { 0,0 };
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	float4 PlayerStartPos = IndexToCenterPos(CurIndex);
	float4 CameraPos = PlayerStartPos;
	CameraPos.Z = -500.0f;
	Camera->SetActorLocation(CameraPos);
	{
		Player = GetWorld()->SpawnActor<APlayer>("Player");
		Player->SetActorLocation(PlayerStartPos);
	}

	// push back을 사용하여 무한맵을 가동시키는 for문
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			std::shared_ptr<APlayBackLayer> Back = GetWorld()->SpawnActor<APlayBackLayer>("PlayBackLayer");
			Back->SetActorScale3D(HoloCureConstValue::GroundTileSize);

			FIntPoint Point;
			Point.X = x;
			Point.Y = y;

			float4 Pos;
			Pos.X = HoloCureConstValue::GroundTileSize.X * x;
			Pos.Y = HoloCureConstValue::GroundTileSize.X * y;

			Pos.X = HoloCureConstValue::GroundTileSize.hX();
			Pos.Y = HoloCureConstValue::GroundTileSize.hY();
			Back->SetActorLocation(Pos);

			Grounds.push_back(Back);
		}
	}



}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	InfinityGroundCheck();

	// 디버깅용 UI 렌더링
	{
		float4 PlayerPos = Player->GetActorLocation();
		FIntPoint Index = PosToIndex(PlayerPos);
		CurIndex = Index;
		UEngineDebugMsgWindow::PushMsg(std::format("PlayerPos : {}", PlayerPos.ToString()));
		UEngineDebugMsgWindow::PushMsg(std::format("PlayerIndex : {}, {}", Index.X, Index.Y));
	}


}


// ========== 무한 맵 기능이 담긴 함수들==========
// 
// 타일의 크기를 절반으로 해줘서 카메라와 플레이어의 위치를 가운데로 정렬
float4 APlayGameMode::IndexToCenterPos(FIntPoint _Index)
{
	float4 Pos;
	Pos.X = HoloCureConstValue::GroundTileSize.X * _Index.X;
	Pos.X = HoloCureConstValue::GroundTileSize.X * _Index.Y;

	Pos.X = HoloCureConstValue::GroundTileSize.hX();
	Pos.X = HoloCureConstValue::GroundTileSize.hY();

	return Pos;
}

FIntPoint APlayGameMode::PosToIndex(float4 _Pos)
{
	FIntPoint Index;

	float4 Location = _Pos;

	float4 Pos;
	Pos.X = Location.X / HoloCureConstValue::GroundTileSize.X;
	Pos.Y = Location.Y / HoloCureConstValue::GroundTileSize.Y;

	if (0 >= Pos.X)
	{
		Pos.X += -1;
	}
	if (0 >= Pos.Y)
	{
		Pos.Y += -1;
	}

	Index.X = Pos.X;
	Index.Y = Pos.Y;
	return Index;
}

void APlayGameMode::InfinityGroundCheck()
{
	float4 PlayerPos = Player->GetActorLocation();

	FIntPoint Index = PosToIndex(PlayerPos);

	if (Index.X != CurIndex.X || Index.Y != CurIndex.Y)
	{
		int GroundCount = 0;

		float4 MovePos;
		MovePos.X = Index.X * HoloCureConstValue::GroundTileSize.X;
		MovePos.Y = Index.Y * HoloCureConstValue::GroundTileSize.Y;

		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				std::shared_ptr<APlayBackLayer> Back = Grounds[GroundCount];

				Back->SetActorScale3D(HoloCureConstValue::GroundTileSize);
				FIntPoint Point;
				Point.X = x;
				Point.Y = y;

				float4 Pos;
				Pos.X = HoloCureConstValue::GroundTileSize.X * x;
				Pos.Y = HoloCureConstValue::GroundTileSize.Y * y;

				Pos.X += HoloCureConstValue::GroundTileSize.hX();
				Pos.Y += HoloCureConstValue::GroundTileSize.hY();
				Back->SetActorLocation(Pos + MovePos);
				++GroundCount;
			}
		}

		CurIndex = Index;
	}
}


