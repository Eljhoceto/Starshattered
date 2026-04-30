#include "HealthObserver.h"
#include "StarShattered/StarShatteredCharacter.h"
#include "Engine/Engine.h"

UHealthObserver::UHealthObserver()
{
	// Restricción: NO usar Tick
	PrimaryComponentTick.bCanEverTick = false; 
}

void UHealthObserver::BeginPlay()
{
	Super::BeginPlay();
	
	// Si el owner es el jugador, nos auto-vinculamos
	if (AStarShatteredCharacter* Player = Cast<AStarShatteredCharacter>(GetOwner()))
	{
		BindToPlayer(Player);
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

	// TODO: CONEXIÓN EQUIPO (Desarrollador A)
	// Vincular aquí la actualización visual de la barra de vida (Widget).
	// Ejemplo:
	// if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	// {
	//     if (AMyGameHUD* HUD = Cast<AMyGameHUD>(PC->GetHUD()))
	//     {
	//         HUD->UpdateHealthBar(NewHealth);
	//     }
	// }
}
