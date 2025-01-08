#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

AMyActor::AMyActor()
{
    PrimaryActorTick.bCanEverTick = true; // Tick 함수 활성화
    CurrentPosition = FVector2D(0.0f, 0.0f);
    PreviousPosition = FVector2D(0.0f, 0.0f);
    MoveCount = 0;
    TotalDistance = 0.0f;
    EventCount = 0;
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Starting position: (%f, %f)"), CurrentPosition.X, CurrentPosition.Y);
}

void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (MoveCount < 10)
    {
        Move();
        MoveCount++;
    }
    else
    {
        // 10회 이동 후 총 결과 출력
        UE_LOG(LogTemp, Warning, TEXT("Total Distance Traveled: %f"), TotalDistance);
        UE_LOG(LogTemp, Warning, TEXT("Total Events Occurred: %d"), EventCount);
    }
}

int32 AMyActor::Step()
{
    return FMath::RandRange(0, 1); // 0 또는 1 반환
}

void AMyActor::Move()
{
    // 현재 위치를 이전 위치로 저장
    PreviousPosition = CurrentPosition;

    // 랜덤 이동 거리 계산
    int32 StepX = Step();
    int32 StepY = Step();

    // 이동 후 좌표 계산
    float NewX = CurrentPosition.X + StepX;
    float NewY = CurrentPosition.Y + StepY;

    // 좌표 제한 조건 확인
    if (NewX <= 20.0f) CurrentPosition.X = NewX;
    if (NewY <= 20.0f) CurrentPosition.Y = NewY;

    // 이동 거리 계산
    float DistanceTraveled = Distance(PreviousPosition, CurrentPosition);
    TotalDistance += DistanceTraveled;

    // 현재 좌표 및 이동 거리 출력
    UE_LOG(LogTemp, Warning, TEXT("Moved to: (%f, %f), Distance: %f"), CurrentPosition.X, CurrentPosition.Y, DistanceTraveled);

    // 랜덤 이벤트 발생
    if (CreateEvent())
    {
        EventCount++;
        UE_LOG(LogTemp, Warning, TEXT("Event occurred at step %d!"), MoveCount + 1);
    }
}

float AMyActor::Distance(FVector2D First, FVector2D Second)
{
    return UKismetMathLibrary::Sqrt(FMath::Pow(Second.X - First.X, 2) + FMath::Pow(Second.Y - First.Y, 2));
}

bool AMyActor::CreateEvent()
{
    if (FMath::RandRange(0, 1) == 1) // 50% 확률로 이벤트 발생
    {
        int32 EventType = FMath::RandRange(1, 3); // 1~3 랜덤 이벤트 선택

        switch (EventType)
        {
        case 1:
            UE_LOG(LogTemp, Warning, TEXT("Event occurred: Found a health potion!"));
            break;
        case 2:
            UE_LOG(LogTemp, Warning, TEXT("Event occurred: The weather changed to rain!"));
            break;
        case 3:
            UE_LOG(LogTemp, Warning, TEXT("Event occurred: A wild monster appeared!"));
            break;
        default:
            UE_LOG(LogTemp, Warning, TEXT("Event occurred: Unknown event."));
            break;
        }

        return true; // 이벤트 발생
    }
    return false; // 이벤트 미발생
}
