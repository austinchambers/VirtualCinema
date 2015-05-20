#pragma once
#include "BluEye.generated.h"

class BrowserClient;
class RenderHandler;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScriptEvent, const FString&, EventName, const FString&, EventMessage);

struct FBluTextureParams
{

	// Pointer to our Texture's resource
	FTexture2DResource* Texture2DResource;

	// Regions we need to update (for now, the whole image)
	FUpdateTextureRegion2D* UpdateRegions;

};

UCLASS(ClassGroup = Blu, Blueprintable)
class BLU_API UBluEye : public UObject
{

	GENERATED_UCLASS_BODY()

	/* Initialize function, should be called after properties are set */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void init();

	/* The default URL this UI component will load */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blu")
		FString DefaultURL;

	/* Is this UI component current active? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blu")
		bool bEnabled;

	/* Should this be rendered in game to be transparent? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blu")
		bool bIsTransparent;

	/* Width of the view resolution */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blu")
		int32 Width;

	/* Height of the view resolution */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blu")
		int32 Height;

	/* Material that will be instanced to load UI texture into it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blu")
		UMaterialInterface* BaseMaterial;

	/* Name of parameter to load UI texture into material */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blu")
		FName TextureParameterName = "BluTexture";

	/* Get the texture data from our UI component */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		UTexture2D* GetTexture() const;

	/** Material instance that contains texture inside it */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		UMaterialInstanceDynamic* GetMaterialInstance() const;

	/* Execute JS code inside the browser */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void ExecuteJS(const FString& code);

	UFUNCTION(BlueprintCallable, Category = "Blu")
		void LoadURL(const FString& newURL);

	/* Trigger a LEFT click in the browser via a Vector2D */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerLeftClick(const FVector2D& pos, const float scale = 1);

	/* Trigger a RIGHT click in the browser via a Vector2D */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerRightClick(const FVector2D& pos, const float scale = 1);

	/* Trigger a LEFT MOUSE DOWN in the browser via a Vector2D */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerLeftMouseDown(const FVector2D& pos, const float scale = 1);

	/* Trigger a RIGHT MOUSE DOWN in the browser via a Vector2D */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerRightMouseDown(const FVector2D& pos, const float scale = 1);

	/* Trigger a LEFT MOUSE DOWN in the browser via a Vector2D */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerLeftMouseUp(const FVector2D& pos, const float scale = 1);

	/* Trigger a RIGHT MOUSE DOWN in the browser via a Vector2D */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerRightMouseUp(const FVector2D& pos, const float scale = 1);

	/* Move the mouse in the browser */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerMouseMove(const FVector2D& pos, const float scale = 1);

	/* Move the mouse in the browser */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void TriggerMouseWheel(const float MouseWheelDelta, const FVector2D& pos, const float scale = 1);

	/* Javascript event emitter */
	UPROPERTY(BlueprintAssignable)
		FScriptEvent ScriptEventEmitter;

	/* Trigger a key down event */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void KeyDown(FKeyEvent InKey);

	/* Trigger a key down event */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void KeyUp(FKeyEvent InKey);

	/* Trigger a key press event */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void KeyPress(FKeyEvent InKey);

	/* Trigger a character key event */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void CharKeyPress(FCharacterEvent CharEvent);

	UFUNCTION(BlueprintCallable, Category = "Blu", meta = (AdvancedDisplay = "2"))
		void RawCharKeyPress(const FString charToPress, bool isRepeat,
								bool LeftShiftDown,
								bool RightShiftDown,
								bool LeftControlDown,
								bool RightControlDown,
								bool LeftAltDown,
								bool RightAltDown,
								bool LeftCommandDown,
								bool RightCommandDown,
								bool CapsLocksOn);

	/* Close the browser */
	UFUNCTION(BlueprintCallable, Category = "Blu")
		void CloseBrowser();

	CefRefPtr<CefBrowser> browser;

	void TextureUpdate(const void* buffer);

	void BeginDestroy() override; //

	protected:
		CefWindowInfo info;
		CefRefPtr<BrowserClient> g_handler;
		CefBrowserSettings browserSettings;
		RenderHandler* renderer;

		void ResetTexture();
		void DestroyTexture();
		void ResetMatInstance();
		
		// Parse UE4 key events, helper
		void processKeyCode(FKeyEvent InKey);

		// Helper for processing key modifiers
		void processKeyMods(FInputEvent InKey);

		// Store UI state in this UTexture2D
		UTexture2D* Texture;
		UMaterialInstanceDynamic* MaterialInstance;

		CefMouseEvent mouse_event;
		CefKeyEvent key_event;

	private:

		FBluTextureParams RenderParams;

};