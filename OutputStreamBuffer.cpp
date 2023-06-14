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

OutputStreamBuffer::OutputStreamBuffer(void) {
  this->mBuffer = nullptr;
  return;
}

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
  if (this->mBuffer)
    return this->mBuffer->putByte(data);

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(mframe::io::ReadBuffer& readBuffer) {
  if (this->mBuffer)
    return this->mBuffer->put(readBuffer);

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(mframe::io::ReadBuffer& readBuffer, int length) {
  if (this->mBuffer)
    return this->mBuffer->put(readBuffer, length);

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(const void* buffer, int length) {
  if (this->mBuffer)
    return this->mBuffer->put(buffer, length);

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
    if (status <= 0)
      this->execute();

    return result;
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
  if (this->mReadBuffer) {
    int result = this->mReadBuffer->poll(writeBuffer, length, peek);
    if (!peek)
      this->mResult += result;

    if (this->mReadBuffer->isEmpty())
      this->execute();

    return result;
  }

  if (this->mBuffer)
    return this->mBuffer->poll(writeBuffer, length, peek);

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::poll(void* buffer, int bufferSize, bool peek) {
  if (this->mReadBuffer) {
    int result = this->mReadBuffer->poll(buffer, bufferSize, peek);

    if (!peek)
      this->mResult += result;

    if (this->mReadBuffer->isEmpty())
      this->execute();
    return result;
  }
  if (this->mBuffer)
    return this->mBuffer->poll(buffer, bufferSize, peek);

  return 0;
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::skip(int value) {
  if (this->mReadBuffer) {
    int result = this->mReadBuffer->skip(value);
    this->mResult += result;
    if (this->mReadBuffer->isEmpty())
      this->execute();

    return result;
  }
  if (this->mBuffer)
    return this->mBuffer->skip(value);

  return 0;
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

/* ****************************************************************************************
 * Private Method
 */

/* ****************************************************************************************
 * End of file
 */
