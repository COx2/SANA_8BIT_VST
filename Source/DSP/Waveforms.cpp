﻿/*
  ==============================================================================

    Waveforms.cpp
    Created: 22 Aug 2018 10:13:35pm
	Modified: 11 September 2018
	Author:  MasakiMori, COx2

  ==============================================================================
*/

#include "Waveforms.h"

namespace {
	const float HALF_PI = MathConstants<float>::halfPi;
	const float ONE_PI = MathConstants<float>::pi;
	const float TWO_PI = MathConstants<float>::twoPi;
}

Waveforms::Waveforms()
{
	init();
}

void Waveforms::init()
{
	rand = Random(0);	
	noizeReg = 1 << 14;
	noiseVal = 0.0f;
	freqCounter = 0;
}



float Waveforms::sine(float angle)
{
	checkAngleRanage(angle);

	// 角度（ラジアン）に対応する波形のサンプルデータを返す。
    return sinf(angle);
}

float Waveforms::saw(float angle)
{
	checkAngleRanage(angle);

    if (angle <= ONE_PI)
    {
        return (angle / ONE_PI);
    }
    else
    {
        return -2.0f + (angle / ONE_PI);
    }
}

float Waveforms::square(float angle)
{
	checkAngleRanage(angle);

	if (angle > TWO_PI)
	{
		angle = fmodf(angle, TWO_PI);
	}

	if (angle <= ONE_PI)
	{
		return 1.0f;
	}
	else
	{
		return -1.0f;
	}
}

float Waveforms::square25(float angle)
{
	checkAngleRanage(angle);

	if (angle <= HALF_PI)
	{
		return 1.0f;
	}
	else
	{
		return -1.0f;
	}
}

float Waveforms::square125(float angle)
{
	checkAngleRanage(angle);

	if (angle <= HALF_PI / 2)
	{
		return 1.0f;
	}
	else
	{
		return -1.0f;
	}
}

float Waveforms::triangle(float angle)
{
	checkAngleRanage(angle);

    if (angle <= HALF_PI)
    {
        return (angle / HALF_PI);
    }
    else if(angle > HALF_PI && angle <= (ONE_PI + HALF_PI))
    {
        return 2.0f - (2.0f * angle / ONE_PI);
    }
    else
    {
        return -4.0f + (angle / HALF_PI);
    }
}

//NESの長周期ノイズの再現
float Waveforms::longNoise(float angleDelta)
{
	//noiseVal *= 0.99;

	if (++freqCounter > TWO_PI / angleDelta / (2 << 4)) 
	{
		freqCounter = 0;
		int result = (noizeReg ^ (noizeReg >> 1)) & 1;
		noizeReg = noizeReg >> 1;
		noizeReg |= result << 14;
		noiseVal = (noizeReg & 1) * 2.0f - 1.0f;
	}
	return noiseVal;
}

//NESの短周期ノイズの再現
float Waveforms::shortNoise(float angleDelta)
{
	//noiseVal *= 0.99;

	if (++freqCounter > TWO_PI / angleDelta / (2 << 4)) 
	{
		freqCounter = 0;
		int result = (noizeReg ^ (noizeReg >> 6)) & 1;
		noizeReg = noizeReg >> 1;
		noizeReg |= result << 14;
		noiseVal = (noizeReg & 1) * 2.0f - 1.0f;
	}
	return noiseVal;
}

//乱数を時間軸と振幅軸側でクオンタイズしたもの
float Waveforms::lobitNoise(float angleDelta)
{
	if (++freqCounter > TWO_PI / angleDelta / (2 << 4)) 
	{
		freqCounter = 0;
		noiseVal = rand.nextFloat() * 2.0f - 1.0f;
	}
	return quantize(noiseVal);
}

float Waveforms::nesSquare(float angle)
{	
	checkAngleRanage(angle);

	if (angle <= ONE_PI)
	{
		return 1.0f / pow(1.4f, angle);
	}
	else
	{
		return -1.0f / pow(1.4f, angle-ONE_PI);
	}
}

float Waveforms::nesSquare25(float angle)
{
	checkAngleRanage(angle);

	if (angle <= HALF_PI)
	{
		return 1.0f / pow(1.4f, angle);
	}
	else
	{
		return -1.0f / pow(1.4f, angle - HALF_PI);
	}
}

float Waveforms::nesSquare125(float angle)
{
	checkAngleRanage(angle);

	if (angle <= HALF_PI/2)
	{
		return 1.0f / pow(1.4f, angle);
	}
	else
	{
		return -1.0f / pow(1.4f, angle - HALF_PI/2);
	}
}

float Waveforms::nesTriangle(float angle)
{
	checkAngleRanage(angle);

	if (angle < ONE_PI)
	{
		int value = int(angle / ONE_PI * 16) * 2;
		return ( -1.0f + value / 15.0f);
	}
	else
	{
		int value = int((angle-ONE_PI) / ONE_PI * 16) * 2;
		return (1.0f - value / 15.0f);
	}
}

float Waveforms::waveformMemory(float angle, WaveformMemoryParameters* _waveformMemoryParamsPtr)
{
	checkAngleRanage(angle);

	//valの範囲を変換 0~15 -> -1.0~1.0
	int val = _waveformMemoryParamsPtr->WaveSamplesArray[(int)(angle * WAVESAMPLE_LENGTH / TWO_PI)]->get();
	return val / 8.0f - 1.0f;
}

// 4bitクオンタイズ関数 qNum * 2倍の数でクオンタイズする
float Waveforms::quantize(float sample)
{
	const int qNum = 8;
	return round(sample * qNum) / qNum;
}

// 角度（ラジアン）の値が2πを超えている場合は、変数angleの値が0～2πの範囲内に収まるよう剰余を求める。
float Waveforms::checkAngleRanage(float angle)
{
	if (angle > TWO_PI)
	{
		angle = fmodf(angle, TWO_PI);
	}

	return angle;
}