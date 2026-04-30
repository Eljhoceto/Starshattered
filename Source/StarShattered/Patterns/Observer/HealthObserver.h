#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthObserver.generated.h"

class AStarShatteredCharacter;
class UUserWidget;
class UStarShatteredHUD;

/**
 * UHealthObserver
 * Implements the Observer Pattern to listen to player health changes
 * and update the HUD without using Tick.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSHATTERED_API UHealthObserver : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthObserver();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Observer")
	TSubclassOf<UUserWidget> HealthWidgetClass;

	/**
	 * Vincula este observador al delegado de salud del jugador.
	 */
	UFUNCTION(BlueprintCallable, Category = "Observer")
	void BindToPlayer(AStarShatteredCharacter* PlayerCharacter);

	/**
	 * Callback que se ejecuta cuando cambia la salud.
	 * (Firma requerida para AddDynamic con DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam)
	 */
	UFUNCTION(BlueprintCallable, Category = "Observer")
	void OnHealthChanged(float NewHealth);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Transient)
	TObjectPtr<UStarShatteredHUD> HealthWidgetInstance = nullptr;
};
