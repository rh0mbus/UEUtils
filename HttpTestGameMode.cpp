// Placeholder

#include "HttpTestGameMode.h"
#include "HttpTestCharacter.h"
#include "Json.h"
#include "UObject/ConstructorHelpers.h"

AHttpTestGameMode::AHttpTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AHttpTestGameMode::StartPlay()
{
	Super::StartPlay();

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
  /*Request->OnProcessRequestComplete().BindUObject(this, &AHttpTestGameMode::OnResponseReceived);
	Request->SetURL("https://jsonplaceholder.typicode.com/posts/1");
	Request->SetVerb("GET");
	Request->ProcessRequest();*/

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("title", "foo");

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestO`bj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &AHttpTestGameMode::OnResponseReceived);
	Request->SetURL("https://jsonplaceholder.typicode.com/posts");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void AHttpTestGameMode::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
	UE_LOG(LogTemp, Display, TEXT("Title: %s"), *ResponseObj->GetStringField("title"));
}