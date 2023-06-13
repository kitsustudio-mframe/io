/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ******************************************************************************
 * Include
 */
#include "./OutputStreamBuffer.h"

//-------------------------------------------------------------------------------
#include "mframe.h"

/* ******************************************************************************
 * Macro
 */

/* ******************************************************************************
 * Using
 */
using mframe::io::OutputStreamBuffer;

//-------------------------------------------------------------------------------
using mframe::io::WriteBuffer;

/* ******************************************************************************
 * Variable <Static>
 */

/* ******************************************************************************
 * Construct Method
 */

//-------------------------------------------------------------------------------
OutputStreamBuffer::OutputStreamBuffer(void) {
  this->mResult = 0;
  this->mHandling = false;
  return;
}

//-------------------------------------------------------------------------------
OutputStreamBuffer::~OutputStreamBuffer(void) {
  return;
}

/* ******************************************************************************
 * Operator Method
 */

/* ******************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************
 *  Public Method <Override> - mframe::lang::Iterable<char>
 */

//-------------------------------------------------------------------------------
bool OutputStreamBuffer::peekIndex(int index, char& result) {
  if (this->mReadBuffer == nullptr)
    return true;

  return this->mReadBuffer->peekIndex(index, result);
}

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::ReadBuffer
 */

//-------------------------------------------------------------------------------
bool OutputStreamBuffer::isEmpty(void) const {
  if (this->mReadBuffer == nullptr)
    return true;

  return this->mReadBuffer->isEmpty();
}

//-------------------------------------------------------------------------------
int OutputStreamBuffer::avariable(void) const {
  if (this->mReadBuffer == nullptr)
    return 0;

  return this->mReadBuffer->avariable();
}

//-------------------------------------------------------------------------------
int OutputStreamBuffer::pollByte(char& result, bool peek) {
  if (this->mReadBuffer == nullptr)
    return 0;

  int status = this->mReadBuffer->pollByte(result, peek);

  if (status >= 0)
    ++this->mResult;

  if (status <= 0)
    this->execute();

  return status;
}

//-------------------------------------------------------------------------------
int OutputStreamBuffer::poll(WriteBuffer& writeBuffer, bool peek) {
  return this->poll(writeBuffer, writeBuffer.remaining(), peek);
}

//-------------------------------------------------------------------------------
int OutputStreamBuffer::poll(WriteBuffer& writeBuffer, int length, bool peek) {
  if (this->mReadBuffer == nullptr)
    return 0;

  int result = this->mReadBuffer->poll(writeBuffer, length, peek);

  if (this->mReadBuffer->isEmpty())
    this->execute();

  return result;
}

//-------------------------------------------------------------------------------
int OutputStreamBuffer::poll(void* buffer, int bufferSize, bool peek) {
  if (this->mReadBuffer == nullptr)
    return 0;

  int result = this->mReadBuffer->poll(buffer, bufferSize, peek);

  if (this->mReadBuffer->isEmpty())
    this->execute();

  return result;
}

//-------------------------------------------------------------------------------
int OutputStreamBuffer::skip(int value) {
  if (this->mReadBuffer == nullptr)
    return 0;

  int result = this->mReadBuffer->skip(value);

  if (this->mReadBuffer->isEmpty())
    this->execute();

  return result;
}

/* ******************************************************************************
 * Public Method <Override>
 */

/* ******************************************************************************
 * Public Method
 */

/* ******************************************************************************
 * Protected Method <Static>
 */

/* ******************************************************************************
 * Protected Method <Override>
 */

/* ******************************************************************************
 * Protected Method
 */

/* ******************************************************************************
 * Private Method
 */

/* ******************************************************************************
 * End of file
 */
