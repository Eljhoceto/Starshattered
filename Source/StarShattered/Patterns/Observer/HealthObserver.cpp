#include "HealthObserver.h"
#include "../../StarShatteredCharacter.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "../../StarShatteredHUD.h"

UHealthObserver::UHealthObserver()
{
	// Restricción: NO usar Tick
	PrimaryComponentTick.bCanEverTick = false; 

	static ConstructorHelpers::FClassFinder<UUserWidget> HUDClassObj(TEXT("/Game/UI/WBP_StarShatteredHUD.WBP_StarShatteredHUD_C"));
	if (HUDClassObj.Succeeded())
	{
		HealthWidgetClass = HUDClassObj.Class;
	}
}

void UHealthObserver::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC && HealthWidgetClass)
	{
		HealthWidgetInstance = CreateWidget<UStarShatteredHUD>(PC, HealthWidgetClass);
		if (HealthWidgetInstance)
		{
			HealthWidgetInstance->AddToViewport();
		}
	}

	// Si el owner es el jugador, nos auto-vinculamos
	if (AStarShatteredCharacter* Player = Cast<AStarShatteredCharacter>(GetOwner()))
	{
		BindToPlayer(Player);
		// Push initial value so HUD starts synced (max health is 100.0f)
		OnHealthChanged(Player->Health);
	}
}

void UHealthObserver::BindToPlayer(AStarShatteredCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		// Vinculación al delegado dinámico
		PlayerCharacter->OnHealthChanged.AddDynamic(this, &UHealthObserver::OnHealthChanged);
	}
}

void UHealthObserver::OnHealthChanged(float NewHealth)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("HUD Update: Player Health is now %f"), NewHealth));
	}

	if (NewHealth <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GAME OVER: Rover ha caido"));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("GAME OVER: Rover ha caido"));
		}
	}

	if (HealthWidgetInstance && HealthWidgetInstance->IsInViewport())
	{
		const float Percent = FMath::Clamp(NewHealth / 100.0f, 0.0f, 1.0f);
		HealthWidgetInstance->UpdateHealth(Percent);
		return;
	}

	if (HealthWidgetClass)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, HealthWidgetClass, false);
		for (UUserWidget* Widget : FoundWidgets)
		{
			if (Widget && Widget->IsInViewport())
			{
				if (UStarShatteredHUD* MyHUD = Cast<UStarShatteredHUD>(Widget))
				{
					const float Percent = FMath::Clamp(NewHealth / 100.0f, 0.0f, 1.0f);
					MyHUD->UpdateHealth(Percent);
				}
			}
		}
	}
}
