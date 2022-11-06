// Placeholder

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Http.h"
#include "HttpTestGameMode.generated.h"

UCLASS(minimalapi)
class AHttpTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHttpTestGameMode();

	virtual void StartPlay() override;

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};

