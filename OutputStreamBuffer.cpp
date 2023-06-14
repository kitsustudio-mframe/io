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

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */
using mframe::io::OutputStreamBuffer;

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

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
  return this->mBuffer.isFull();
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::remaining(void) const {
  return this->mBuffer.remaining();
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::putByte(const char data) {
  return this->mBuffer.putByte(data);
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(mframe::io::ReadBuffer& readBuffer) {
  return this->mBuffer.put(readBuffer);
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(mframe::io::ReadBuffer& readBuffer, int length) {
  return this->mBuffer.put(readBuffer, length);
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::put(const void* buffer, int length) {
  return this->mBuffer.put(buffer, length);
}

/* ****************************************************************************************
 *  Public Method <Override> - mframe::lang::Iterable<char>
 */

//-----------------------------------------------------------------------------------------
bool OutputStreamBuffer::peekIndex(int index, char& result) {
  if (this->mReadBuffer)
    return this->mReadBuffer->peekIndex(index, result);
  return this->mBuffer.peekIndex(index, result);
}

/* ****************************************************************************************
 * Public Method <Override> - mframe::lang::ReadBuffer
 */

//-----------------------------------------------------------------------------------------
bool OutputStreamBuffer::isEmpty(void) const {
  if (this->mReadBuffer)
    return this->mReadBuffer->isEmpty();

  return this->mBuffer.isEmpty();
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::avariable(void) const {
  if (this->mReadBuffer)
    return this->mReadBuffer->avariable();

  return this->mBuffer.avariable();
}

//-----------------------------------------------------------------------------------------
int OutputStreamBuffer::pollByte(char& result, bool peek) {
  if (this->mReadBuffer) {
    int status = this->mReadBuffer->pollByte(result, peek);
    if (status <= 0)
      this->execute();

    return result;
  }

  return this->mBuffer.pollByte(result, peek);
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

  return this->mBuffer.poll(writeBuffer, length, peek);
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

  return this->mBuffer.poll(buffer, bufferSize, peek);
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

  return this->mBuffer.skip(value);
}

/* ****************************************************************************************
 * Public Method
 */

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
