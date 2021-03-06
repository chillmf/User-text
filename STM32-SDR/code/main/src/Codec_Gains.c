/*
 * Codec_Gains.c
 *
 *  Created on: Mar 28, 2013
 *      Author: CharleyK
 */
#include 	"Init_Codec.h"
#include 	"Init_I2C.h"
#include	"Codec_Gains.h"

void Set_HP_Gain(int HP_gain)
{

	// Check for error writing.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x10, HP_gain);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x11, HP_gain);
	Delay(Codec_Pause);
}   // End of Set_HP_Gain

/*==========================================================================*/

void Set_LO_Gain(int LO_gain)
{
	// Check for error writing.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x12, LO_gain);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x13, LO_gain);
	Delay(Codec_Pause);
}   // End of Set_LO_Gain

/*==========================================================================*/

void Set_PGA_Gain(int PGA_gain)
{

	if (PGA_gain < PGA_GAIN_MIN)
		PGA_gain = PGA_GAIN_MIN;
	if (PGA_gain > PGA_GAIN_MAX)
		PGA_gain = PGA_GAIN_MAX;

	// Check for failure accessing I2C.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x3B, PGA_gain);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x3C, PGA_gain);
	Delay(Codec_Pause);
}   // End of Set_PGA_gain

/*==========================================================================*/

void Set_DAC_DVC(int DAC_gain)
{

	if (DAC_gain > DAC_GAIN_MAX)
		DAC_gain = DAC_GAIN_MAX;
	if (DAC_gain < DAC_GAIN_MIN)
		DAC_gain = DAC_GAIN_MIN;
	if (DAC_gain < 0)
		DAC_gain += 256;

	// Check for error writing.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x00) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x41, DAC_gain);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x42, DAC_gain);
	Delay(Codec_Pause);
}   // End of Set_Dig_DVC

/*============================================================================*/

void Set_ADC_DVC(int ADC_gain)
{

	if (ADC_gain > ADC_GAIN_MAX)
		ADC_gain = ADC_GAIN_MAX;
	if (ADC_gain < ADC_GAIN_MIN)
		ADC_gain = ADC_GAIN_MIN;
	if (ADC_gain < 0)
		ADC_gain += 127;

	// Check for error writing.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x00) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x53, ADC_gain);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x54, ADC_gain);
	Delay(Codec_Pause);
}   // End of Set_ADC_DVC
/*============================================================================*/

//Microphone Power Handling
void Turn_On_Bias(void)
{
	// Check for error writing.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x33, 0x40);
	Delay(Codec_Pause);
}

void Turn_Off_Bias(void)
{

	// Check for error writing.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x33, 0x00);
	Delay(Codec_Pause);
}

/*============================================================================*/

//Disconnect Everything from PGA input
void Disconnect_PGA(void)
{
	// Check for error writing.
	if (I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01) != 0) {
		return;
	}
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x34, 0x00);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x37, 0x00);
	Delay(Codec_Pause);

}

/*============================================================================*/
//Mute HP Outputs
void Mute_HP(void)
{
	Set_HP_Gain(0x40);			//Mute HPL & HPR
}
/*============================================================================*/
//Mute Line Outputs
void Mute_LO(void)
{
	Set_LO_Gain(0x40);						//Mute LOL & LOR
}
/*============================================================================*/
//Connect IQ Inputs to PGA
void Connect_IQ_Inputs(void)
{
	I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x34, 0x30);  //IN2L routed to Left MICPGA
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x37, 0x30);  //IN2R routed to Right MICPGA
	Delay(Codec_Pause);
}

/*============================================================================*/
//Connect Microphone to PGA
void Connect_Microphone_Input(void)
{
	I2C_WriteRegister(CODEC_ADDRESS, 0x00, 0x01);
	Delay(Codec_Pause);

	I2C_WriteRegister(CODEC_ADDRESS, 0x34, 0x0C);  //IN3L routed to Left MICPGA
	Delay(Codec_Pause);
}

