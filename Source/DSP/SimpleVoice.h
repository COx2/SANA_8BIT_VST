﻿/*
  ==============================================================================

    SimpleVoice.h
    Created: 20 Apr 2018 2:08:09am
	Modified: 11 September 2018
	Author:  MasakiMori, COx2

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SimpleSynthParameters.h"
#include "SimpleSound.h"
#include "AmpEnvelope.h"
#include "MIDIEcho.h"
#include "Waveforms.h"

class SimpleVoice : public SynthesiserVoice
{
public:
	SimpleVoice(
		ChipOscillatorParameters* chipOscParams, 
		SweepParameters* sweepParams, 
		VibratoParameters* vibratoParams,
		VoicingParameters* voicingParams,
		OptionsParameters* optionsParams,
		MidiEchoParameters* midiEchoParams,
		WaveformMemoryParameters* waveformMemoryParams
	);

	virtual ~SimpleVoice();

	// 基底クラスで宣言された純粋仮想関数をオーバーライド宣言する。
	virtual bool canPlaySound(SynthesiserSound* sound) override;
	virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	virtual void stopNote(float velocity, bool allowTailOff) override;
	virtual void pitchWheelMoved(int newPitchWheelValue) override;
	virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
	virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
	float calcModulationFactor(float angle);

	float currentAngle, vibratoAngle, angleDelta, portaAngleDelta;
	float level;
	float pitchBend, pitchSweep;
	std::vector<float> echoSamples;
	
	EchoBuffer eb;

	//Waveform用のパラメータ
	Waveforms waveForms;
	//各種エンベロープ， アンプ， ビブラート， ポルタメント用
	AmpEnvelope ampEnv, vibratoEnv, portaEnv;

	// パラメータを管理するオブジェクトのポインタ変数。
	ChipOscillatorParameters* _chipOscParamsPtr;
	SweepParameters* _sweepParamsPtr;
	VibratoParameters* _vibratoParamsPtr;
	VoicingParameters* _voicingParamsPtr;
	OptionsParameters* _optionsParamsPtr;
	MidiEchoParameters* _midiEchoParamsPtr;
	WaveformMemoryParameters* _waveformMemoryParamsPtr;
};