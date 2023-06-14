/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "./ReadBufferMonitor.h"

//-----------------------------------------------------------------------------------------

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */
using mframe::io::ReadBufferMonitor;

//-----------------------------------------------------------------------------------------
using mframe::io::ReadBuffer;
using mframe::io::WriteBuffer;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

//-----------------------------------------------------------------------------------------
ReadBufferMonitor::ReadBufferMonitor(ReadBuffer& readBuffer) : mReadBuffer(readBuffer) {
  this->mMonitor = nullptr;
  return;
}

//-----------------------------------------------------------------------------------------
ReadBufferMonitor::~ReadBufferMonitor(void) {
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 *  Public Method <Override> - mframe::lang::Iterable<char>
 */
//-----------------------------------------------------------------------------------------
bool ReadBufferMonitor::peekIndex(int index, char& result) {
  return this->mReadBuffer.peekIndex(index, result);
}

/* ****************************************************************************************
 * Public Method <Override> - mframe::io::ReadBuffer
 */

//-----------------------------------------------------------------------------------------
bool ReadBufferMonitor::isEmpty(void) const {
  return this->mReadBuffer.isEmpty();
}

//-----------------------------------------------------------------------------------------
int ReadBufferMonitor::avariable(void) const {
  return this->mReadBuffer.avariable();
}

//-----------------------------------------------------------------------------------------
int ReadBufferMonitor::pollByte(char& result, bool peek) {
  if ((this->mMonitor == nullptr) || peek)
    return this->mReadBuffer.pollByte(result, peek);

  int status = this->pollByte(result, true);
  if (status >= 0)
    this->mMonitor->putByte(result);

  return status;
}

//-----------------------------------------------------------------------------------------
int ReadBufferMonitor::poll(WriteBuffer& writeBuffer, bool peek) {
  return this->poll(writeBuffer, writeBuffer.remaining(), peek);
}

//-----------------------------------------------------------------------------------------
int ReadBufferMonitor::poll(WriteBuffer& writeBuffer, int length, bool peek) {
  if ((this->mMonitor == nullptr) || peek)
    return this->poll(writeBuffer, length, true);

  int result = this->poll(writeBuffer, length, true);
  int skip = result - this->poll(this->mMonitor, length, false);

  if (skip)
    this->mReadBuffer.skip(skip);

  return result;
}

//-----------------------------------------------------------------------------------------
int ReadBufferMonitor::poll(void* buffer, int bufferSize, bool peek) {
  int result = this->mReadBuffer.poll(buffer, bufferSize, peek);
  this->mMonitor->put(buffer, result);
  return result;
}

//-----------------------------------------------------------------------------------------
int ReadBufferMonitor::skip(int value) {
  int result;
  int max = this->mReadBuffer.avariable();
  if (value > max)
    value = max;

  result = this->mMonitor->put(this->mReadBuffer, value);
  if (result < max)
    result += this->mReadBuffer.skip(max - result);

  return result;
}

/* ****************************************************************************************
 * Public Method
 */

//-----------------------------------------------------------------------------------------
void ReadBufferMonitor::setMonitor(WriteBuffer* monitor) {
  this->mMonitor = monitor;
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
