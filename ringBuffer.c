#include "ringBuffer.h"

//--------------------------------------------------------------------------------
//Функция записи данных в буффер
int32_t AddData(buffer_t *__restrict buffer, void *__restrict vpRawData, uint32_t Len)
{
  int32_t ret_code     = _BUFFER_FAIL;
  uint8_t *pDst         = buffer->pWrite, *pSrc = (uint8_t*)(vpRawData);
  uint32_t data_len    = Len;
  uint8_t *buffer_start = buffer->p_buffer;

  do
  {
    if(data_len > buffer->FreeSpace)
    { ret_code = _BUFFER_NOT_ENOUGH_MEM; break; }

    if(NULL == vpRawData)
    { ret_code = _BUFFER_INVALID_DATA; break; }

    if(buffer->pWrite >= buffer->pRead)
    {
      const uint32_t bytes_to_end = (buffer_start + buffer->BufferSize) - buffer->pWrite;

      if(bytes_to_end <= data_len)
      {
        memcpy(pDst, pSrc, bytes_to_end);
        buffer->pWrite     = buffer->p_buffer;
        pDst               = buffer->pWrite;
        pSrc              += bytes_to_end;
        data_len          -= bytes_to_end;
      }
    }
    if(data_len)
    {
      memcpy(pDst, pSrc, data_len);
      buffer->pWrite    += data_len;
    }
    buffer->FreeSpace -= Len;

    ret_code = _BUFFER_OK;
  } while(0);

  return ret_code;
}
//--------------------------------------------------------------------------------
//Функция чтения данных из буффера
int32_t GetData(buffer_t *__restrict buffer, void *__restrict vpDst, uint32_t Len)
{
  int32_t ret_code          = _BUFFER_FAIL;
  const uint32_t busy_space = buffer->BufferSize - buffer->FreeSpace;
  uint8_t *pSrc              = buffer->pRead, *pDst = (uint8_t*)vpDst;
  uint32_t data_len         = 0;

  do
  {
    if(buffer->FreeSpace == buffer->BufferSize)
    { ret_code = _BUFFER_EMPTY; break; }

    if(NULL == vpDst)
    { ret_code = _BUFFER_INVALID_DATA; break; }

    if(busy_space < Len)  //Если байт в буфере меньше, чем просят...
    {
      data_len = ret_code = busy_space; //Отдадим сколько есть
    }
    else //Иначе байт в буфере больше, чем просят
    {
      data_len = ret_code = Len;  //В этом случае и отдадим сколько просят
    }

    if(buffer->pRead > buffer->pWrite)
    {
      uint8_t *buffer_start = buffer->p_buffer;
      const uint32_t bytes_to_end = (buffer_start + buffer->BufferSize) - buffer->pRead;

      if(bytes_to_end < Len)
      {
        memcpy(pDst, pSrc, bytes_to_end);
        buffer->pRead = buffer_start;
        pDst         += bytes_to_end;
        pSrc          = buffer->pRead;
        data_len     -= bytes_to_end;
      }
    }

    memcpy( pDst, pSrc, data_len );
    buffer->pRead     += data_len;
    buffer->FreeSpace += Len;
  } while(0);

  return ret_code;
}
//--------------------------------------------------------------------------------
//функция инициализации буфера
int32_t initBuffer(buffer_t *buffer)
{
  int32_t status = _BUFFER_FAIL;

  do
  {

    if(buffer == NULL)
      break;
    buffer->p_buffer = (uint8_t*)malloc(BUFF_SIZE);
    buffer->BufferSize = BUFF_SIZE;
    buffer->FreeSpace = BUFF_SIZE;
    buffer->pWrite = buffer->p_buffer;
    buffer->pRead = buffer->p_buffer;

    memset(buffer->p_buffer,0,buffer->BufferSize);

    status = _BUFFER_OK;

  }while(0);

  return status;

}

int32_t fillBuffer (uint8_t *ptrBuff,uint8_t len)
{
  int32_t status = _BUFFER_FAIL;

  do
  {

    if((ptrBuff == NULL) || (len == 0))
       break;

    uint8_t i = 0;
    while((i++) < len)
    {
      *(ptrBuff + i) = i;
    }

    printf("массив со следующими значениями:\n {");
    for(i=0;i<SIZE_ARRAY;i++)
    {
      printf("%d, ",ptrBuff[i]);
    }
    printf("}\n");

    status = _BUFFER_OK;

  }while(0);

  return status;

}
//--------------------------------------------------------------------------------
void printStatus(int32_t status)
{
  printf("текущее состояние буффера: ");

  switch(status)
  {
    case _BUFFER_EMPTY:
      printf("_BUFFER_EMPTY\n");
    break;

    case _BUFFER_NOT_ENOUGH_MEM:
      printf("_BUFFER_NOT_ENOUGH_MEM\n");
    break;

    case _BUFFER_OVERFLOW:
      printf("_BUFFER_OVERFLOW\n");
    break;

    case _BUFFER_INVALID_DATA:
      printf("_BUFFER_INVALID_DATA\n");
    break;

    case _BUFFER_FAIL:
      printf("_BUFFER_FAIL\n");
    break;

    case _BUFFER_NO_INIT:
      printf("_BUFFER_NO_INIT\n");
    break;

    case _BUFFER_OK:
      printf("_BUFFER_OK\n");
    break;

    case _BUFFER_INIT:
      printf("_BUFFER_INIT\n");
    break;

    case _BUFFER_STARTED:
      printf("_BUFFER_STARTED\n");
    break;

    default:
    break;
  }

}
//--------------------------------------------------------------------------------

