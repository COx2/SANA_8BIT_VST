﻿/*
  ==============================================================================

    SimpleSynthParameters.h
    Created: 10 May 2018 12:28:18am
	Modified: 11 September 2018
	Author:  MasakiMori, COx2

  ==============================================================================
*/

#pragma once

// ①JUCEライブラリのヘッダをインクルードする。
#include "../JuceLibraryCode/JuceHeader.h"

// ②クラス宣言。複数のパラメータをまとめるクラス群の基底クラス。
class SynthParametersBase
{
public:
	// デストラクタ
	virtual ~SynthParametersBase() {};

	// ③継承クラス側で実装を必須とする関数を純粋仮想関数として宣言する。
	virtual void addAllParameters(AudioProcessor& processor) = 0;
	virtual void saveParameters(XmlElement& xml) = 0; 
	virtual void loadParameters(XmlElement& xml) = 0;
};

class ChipOscillatorParameters : public SynthParametersBase
{
public:
	// ⑤各波形の音量レベルを管理するパラメータのポインタ変数。
	AudioParameterChoice* OscWaveType;
	AudioParameterFloat* VolumeLevel;
	AudioParameterFloat* Attack;
	AudioParameterFloat* Decay;
	AudioParameterFloat* Sustain;
	AudioParameterFloat* Release;

	// ⑥引数付きコンストラクタ。PluginProcessor.h/cpp側で保持するパラメータのポインタ変数を受け取る。
	ChipOscillatorParameters(
		AudioParameterChoice* OscWaveType ,
		AudioParameterFloat* volumeLevel,
		AudioParameterFloat* attack,
		AudioParameterFloat* decay,
		AudioParameterFloat* sustain,
		AudioParameterFloat* release);
	//chipOscillatorParameters(AudioParameterFloat* sineWaveLevel);

	// ⑦基底クラスで宣言されている純粋仮想関数をオーバーライドして実装する。
	virtual void addAllParameters(AudioProcessor& processor) override;
	virtual void saveParameters(XmlElement& xml) override;
	virtual void loadParameters(XmlElement& xml) override;

private:
	// 引数無しコントラクタをprivate領域に置くことで、外から呼び出せないようにする。
	ChipOscillatorParameters() {};
};

class SweepParameters : public SynthParametersBase
{
public:
	AudioParameterChoice* SweepSwitch;
	AudioParameterFloat*  SweepTime;

	SweepParameters(
		AudioParameterChoice* SweepSwitch,
		AudioParameterFloat*  SweepTime
	);

	virtual void addAllParameters(AudioProcessor& processor) override;
	virtual void saveParameters(XmlElement& xml) override;
	virtual void loadParameters(XmlElement& xml) override;

private:
	SweepParameters() {};
};

class VibratoParameters : public SynthParametersBase
{
public:
	AudioParameterBool * VibratoEnable;
	AudioParameterFloat*  VibratoAmount;
	AudioParameterFloat*  VibratoSpeed;

	VibratoParameters(
		AudioParameterBool* vibratoEnable,
		AudioParameterFloat*  vibratoAmount,
		AudioParameterFloat*  vibratoSpeed
	);

	virtual void addAllParameters(AudioProcessor& processor) override;
	virtual void saveParameters(XmlElement& xml) override;
	virtual void loadParameters(XmlElement& xml) override;

private:
	VibratoParameters() {};
};

class OptionsParameters : public SynthParametersBase
{
public:
	AudioParameterBool* IsPolyMode;
	AudioParameterBool* IsVelocitySense;
	AudioParameterInt*	PitchBendRange;
	AudioParameterInt*	PitchStandard;

	OptionsParameters(
		AudioParameterBool* isPolyMode,
		AudioParameterBool* isVelocitySense,
		AudioParameterInt* pitchBendRange,
		AudioParameterInt*	pitchStandard
	);

	virtual void addAllParameters(AudioProcessor& processor) override;
	virtual void saveParameters(XmlElement& xml) override;
	virtual void loadParameters(XmlElement& xml) override;

private:
	OptionsParameters() {};
};

class WaveformMemoryParameters : public SynthParametersBase
{
public:
	AudioParameterInt* WaveSamples0_5;
	AudioParameterInt* WaveSamples6_11;
	AudioParameterInt* WaveSamples12_17;
	AudioParameterInt* WaveSamples18_23;
	AudioParameterInt* WaveSamples24_29;
	AudioParameterInt* WaveSamples30_31;

	WaveformMemoryParameters(
		AudioParameterInt* waveSamples0_5,
		AudioParameterInt* waveSamples6_11,
		AudioParameterInt* waveSamples12_17,
		AudioParameterInt* waveSamples18_23,
		AudioParameterInt* waveSamples24_29,
		AudioParameterInt* waveSamples30_31
	);

	virtual void addAllParameters(AudioProcessor& processor) override;
	virtual void saveParameters(XmlElement& xml) override;
	virtual void loadParameters(XmlElement& xml) override;

private:
};