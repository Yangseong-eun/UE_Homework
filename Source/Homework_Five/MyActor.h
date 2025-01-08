// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class HOMEWORK_FIVE_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    // 생성자
    AMyActor();

protected:
    // 시작 시 호출되는 함수
    virtual void BeginPlay() override;

public:
    // 매 프레임 호출되는 함수
    virtual void Tick(float DeltaTime) override;

private:
    // 현재 위치
    FVector2D CurrentPosition;

    // 이전 위치
    FVector2D PreviousPosition;

    // 이동 횟수
    int32 MoveCount;

    // 총 이동 거리
    float TotalDistance;

    // 이벤트 발생 횟수
    int32 EventCount;

    // 랜덤 이동 거리 반환 (0 또는 1)
    int32 Step();

    // 이동 처리
    void Move();

    // 두 점 간 거리 계산
    float Distance(FVector2D First, FVector2D Second);

    // 랜덤 이벤트 발생
    bool CreateEvent();

};
