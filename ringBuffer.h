#pragma once
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "main.h"

#define BUFF_SIZE   15

#define MY_INT_DEF int;
//--------------------------------------------------------------------------------
typedef struct
{
	uint8_t *p_buffer;
	uint32_t BufferSize;
	uint32_t FreeSpace;
	uint8_t *pWrite;
	uint8_t *pRead;
}buffer_t;
//--------------------------------------------------------------------------------
typedef enum {
	_BUFFER_EMPTY	= -6,
	_BUFFER_NOT_ENOUGH_MEM,
	_BUFFER_OVERFLOW,
	_BUFFER_INVALID_DATA,
	_BUFFER_FAIL,
	_BUFFER_NO_INIT,
	_BUFFER_OK,
	_BUFFER_INIT,
	_BUFFER_STARTED

} enumStatus;
//--------------------------------------------------------------------------------
//Функция записи данных в буффер
int32_t AddData(buffer_t *__restrict buffer, void *__restrict vpRawData, uint32_t Len);
//--------------------------------------------------------------------------------
//Функция чтения данных из буффера
int32_t GetData(buffer_t *__restrict buffer, void *__restrict vpDst, uint32_t Len);
//--------------------------------------------------------------------------------
//функция инициализации буфера
int32_t initBuffer(buffer_t *buffer);
//--------------------------------------------------------------------------------
int32_t fillBuffer (uint8_t *ptrBuff,uint8_t len);
//--------------------------------------------------------------------------------
void printStatus(int32_t status);
//--------------------------------------------------------------------------------

#endif //RING_BUFFER_H

