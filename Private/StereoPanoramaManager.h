// Copyright 2015 Kite & Lightning.  All rights reserved.

#pragma once

#include "SceneCapturer.h"
#include "FStereoPanoramaManagerBase.h"

class FStereoPanoramaManager:public FStereoPanoramaManagerBase
{
public:

	FStereoPanoramaManager()
		: StartCommand(
			TEXT("SP.Start"),
			*NSLOCTEXT("StereoPanorama", "CommandText_ScreenShot", "Takes a panoramic screenshot").ToString(),
			FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::Start))
		,DisableBinoculusOutputCommand(
			TEXT("SP.DisableBinoculusOutput"),
			*NSLOCTEXT("StereoPanorama", "CommandText_ScreenShot", "Disable Binoculus output.").ToString(),
			FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::DisableBinoculusOutput))
		, PanoramicScreenshotCommand(
			TEXT("SP.PanoramicScreenshot"),
			*NSLOCTEXT("StereoPanorama", "CommandText_ScreenShot", "Takes a panoramic screenshot").ToString(),
			FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicScreenshot))
		, PanoramicMovieCommand(
			TEXT("SP.PanoramicMovie"),
			*NSLOCTEXT("StereoPanorama", "CommandText_MovieCapture", "Takes a sequence of panoramic screenshots").ToString(),
			FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicMovie))
		, PanoramicQualityCommand(
			TEXT("SP.PanoramicQuality"),
			*NSLOCTEXT("StereoPanorama", "CommandText_Quality", "Sets the quality of the panoramic screenshot to 'preview | average | improved'").ToString(),
			FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicQuality))
		, PanoramicPauseCommand(
            TEXT("SP.TogglePause"),
			*NSLOCTEXT("StereoPanorama", "CommandText_PauseGame", "Toggles Pausing/Unpausing of the game through StereoPanorama Plugin").ToString(),
			FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicTogglePause))
		, SceneCapturer(nullptr)
	{ }

public:

	void Start(const TArray<FString>& Args);
	virtual void init_CombineAtlasesOnOutput();
	virtual void DisableBinoculusOutput(const TArray<FString>& Args);

	void Cleanup();
	bool ValidateRendererState() const;

	void PanoramicScreenshot(const TArray<FString>& Args);
	void PanoramicScreenshot(const int32 InStartFrame, const int32 InEndFrame, FStereoCaptureDoneDelegate& InStereoCaptureDoneDelegate);
	void PanoramicMovie(const TArray<FString>& Args);
	void PanoramicQuality(const TArray<FString>& Args);
	void PanoramicTogglePause(const TArray<FString>& Args);


public:

	static IConsoleVariable* HorizontalAngularIncrement;
	static IConsoleVariable* VerticalAngularIncrement;
	// output image resolution ratio
	static IConsoleVariable* StepCaptureWidth;
	static IConsoleVariable* StepCaptureHeight;
	static IConsoleVariable* EyeSeparation;
	static IConsoleVariable* ForceAlpha;
	static IConsoleVariable* GenerateDebugImages;
	static IConsoleVariable* ConcurrentCaptures;
	static IConsoleVariable* CaptureHorizontalFOV;
	static IConsoleVariable* CaptureSlicePixelWidth;
	static IConsoleVariable* EnableBilerp;
	static IConsoleVariable* SuperSamplingMethod;
	static IConsoleVariable* OutputDir;
	static IConsoleVariable* ShouldOverrideInitialYaw;
	static IConsoleVariable* ForcedInitialYaw;
	static IConsoleVariable* FadeStereoToZeroAtSides;

	static bool CombineAtlasesOnOutput;
public:

	/** The scene capturer object. */
	UPROPERTY()
	class USceneCapturer* SceneCapturer;

private:
	FAutoConsoleCommand StartCommand;
	FAutoConsoleCommand DisableBinoculusOutputCommand;
	FAutoConsoleCommand PanoramicScreenshotCommand;
	FAutoConsoleCommand PanoramicMovieCommand;
	FAutoConsoleCommand PanoramicQualityCommand;
	FAutoConsoleCommand PanoramicPauseCommand;
};