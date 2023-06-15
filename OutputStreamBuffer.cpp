/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "./OutputStreamBuffer.h"

//-----------------------------------------------------------------------------------------
#include "mframe.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */
using mframe::io::OutputStreamBuffer;

//-----------------------------------------------------------------------------------------
using mframe::io::Buffer;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

//-----------------------------------------------------------------------------------------
OutputStreamBuffer::OutputStreamBuffer(void) {
  this->mBuffer = nullptr;
  return;
}

//-----------------------------------------------------------------------------------------
OutputStreamBuffer::~OutputStreamBuffer(void) {
  this->mBuffer = nullptr;
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 *  Public Method <Override> - mframe::io::Buffer
 */

//-----------------------------------------------------------------------------------------
void OutputStreamBuffer::flush(void) {
  if (this->mBuffer)
    this->mBuffer->flush();

  return;
}

/* ****************************************************************************************
 * Public Method <Override> - mframe::lang::WriteBuffer
 */

//-----------------------------------------------------------------------------------------
bool OutputStreamBuffer::isFull(void) const {
  if (this->mBuffer)
    return this->mBuffer->isFull();

  return false;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::remaining(void) const {
  if (this->mBuffer)
    return this->mBuffer->remaining();

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::putByte(const char data) {
  if (this->mBuffer) {
    int result = this->mBuffer->putByte(data);
    this->onBufferPutEvent();
    return result;
  }

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(mframe::io::ReadBuffer& readBuffer) {
  if (this->mBuffer) {
    int result = this->mBuffer->put(readBuffer);
    this->onBufferPutEvent();
    return result;
  }

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(mframe::io::ReadBuffer& readBuffer, int length) {
  if (this->mBuffer) {
    int result = this->mBuffer->put(readBuffer, length);
    this->onBufferPutEvent();
    return result;
  }

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(const void* buffer, int length) {
  if (this->mBuffer) {
    int result = this->mBuffer->put(buffer, length);
    this->onBufferPutEvent();
    return result;
  }

  return 0;
}

/* ****************************************************************************************
 *  Public Method <Override> - mframe::lang::Iterable<char>
 */

//-----------------------------------------------------------------------------------------
bool OutputStreamBuffer::peekIndex(int index, char& result) {
  if (this->mReadBuffer)
    return this->mReadBuffer->peekIndex(index, result);

  if (this->mBuffer)
    return this->mBuffer->peekIndex(index, result);

  return false;
}

/* ****************************************************************************************
 * Public Method <Override> - mframe::lang::ReadBuffer
 */

//-----------------------------------------------------------------------------------------
bool OutputStreamBuffer::isEmpty(void) const {
  if (this->mReadBuffer)
    return this->mReadBuffer->isEmpty();

  if (this->mBuffer)
    return this->mBuffer->isEmpty();

  return false;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::avariable(void) const {
  if (this->mReadBuffer)
    return this->mReadBuffer->avariable();

  if (this->mBuffer)
    return this->mBuffer->avariable();

  return false;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::pollByte(char& result, bool peek) {
  if (this->mReadBuffer) {
    int status = this->mReadBuffer->pollByte(result, peek);
    if (status <= 0) {
      this->execute();
      status = this->mBuffer->avariable();
    }
    
    return status;
  }

  if (this->mBuffer)
    return this->mBuffer->pollByte(result, peek);

  return -1;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::poll(mframe::io::WriteBuffer& writeBuffer, bool peek) {
  return this->poll(writeBuffer, writeBuffer.remaining(), peek);
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::poll(mframe::io::WriteBuffer& writeBuffer, int length, bool peek) {
  int result = 0;
  if (this->mReadBuffer) {
    result = this->mReadBuffer->poll(writeBuffer, length, peek);
    if (!peek)
      this->mResult += result;

    if (this->mReadBuffer->isEmpty())
      this->execute();
  }

  if (this->mBuffer) {
    if (length > result)
      result += this->mBuffer->poll(writeBuffer, length - result, peek);
  }

  return result;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::poll(void* buffer, int bufferSize, bool peek) {
  int result = 0;
  if (this->mReadBuffer) {
    result = this->mReadBuffer->poll(buffer, bufferSize, peek);

    if (!peek)
      this->mResult += result;

    if (this->mReadBuffer->isEmpty())
      this->execute();
  }

  if (this->mBuffer) {
    if (bufferSize > result)
      result += this->mBuffer->poll(buffer, bufferSize - result, peek);
  }

  return result;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::skip(int value) {
  int result = 0;

  if (this->mReadBuffer) {
    result = this->mReadBuffer->skip(value);
    this->mResult += result;
    if (this->mReadBuffer->isEmpty())
      this->execute();
  }

  if (this->mBuffer) {
    if (value > result)
      result += this->mBuffer->skip(value - result);
  }

  return result;
}

/* ****************************************************************************************
 * Public Method
 */

//-----------------------------------------------------------------------------------------
void OutputStreamBuffer::setDefaultBuffer(Buffer* buffer) {
  this->mBuffer = buffer;
  return;
}

/* ****************************************************************************************
 * Protected Method <Static>
 */

/* ****************************************************************************************
 * Protected Method <Override>
 */

/* ****************************************************************************************
 * Protected Method
 */

//-----------------------------------------------------------------------------------------
void OutputStreamBuffer::onBufferPutEvent(void) {
  return;
}
/* ****************************************************************************************
 * Private Method
 */

/* ****************************************************************************************
 * End of file
 */
