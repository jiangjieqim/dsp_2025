#ifndef _I2C_H_
#define _I2C_H_
#include "utils.h"

/**错误码位*/
/**
*@breaf	 I2C开始函数
*@param	无
*@retval	无
*/
void I2C_Start();
/**
   *@breaf I2C停止函数
   *@param无
   *@retval无
*/	
void I2C_Stop();
/**
*@breaf  I2C发送字节函数
*@param Byte要发送的字节内容
*@retval 无
*/
void I2C_SendByte(u8 Byte);
/**
*@breaf  I2C接收字节函数
*@param 无
*@retval Byte接收来自外设的数据
*/
u8 I2C_ReceiveByte();
/**
*@breaf I2C发送应答
*@param AckBit 应答位，0为应答，1为非应答
*@retval 无
*/
// void I2C_SendAck(unsigned char AckBit);
/**
*@breaf I2C接收应答
*@param无
*@retval AckBit  应答位，0为应答，1为非应答
*/
u8 I2C_ReceiveAck();
#endif