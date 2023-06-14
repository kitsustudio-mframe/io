/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "./WriteBufferMonitor.h"

//-----------------------------------------------------------------------------------------
#include "mframe.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */
using mframe::WriteBufferMonitor;

//-----------------------------------------------------------------------------------------
using mframe::io::WriteBuffer;
using mframe::io::ReadBuffer;

/* ****************************************************************************************
 * Variable <Static>
 */

/* ****************************************************************************************
 * Construct Method
 */

//-----------------------------------------------------------------------------------------
WriteBufferMonitor::WriteBufferMonitor(WriteBuffer& writeBuffer) : mWriteBuffer(writeBuffer){
  this->mMonitor = nullptr;
  return;
}

//-----------------------------------------------------------------------------------------
WriteBufferMonitor::~WriteBufferMonitor(void){
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 * Public Method <Override> - mframe::io::WriteBuffer
 */

//-----------------------------------------------------------------------------------------
bool WriteBufferMonitor::isFull(void) const {
  return this->mWriteBuffer.isFull();
}

//-----------------------------------------------------------------------------------------
int WriteBufferMonitor::remaining(void) const {
  return this->mWriteBuffer.remaining();
}

//-----------------------------------------------------------------------------------------
int WriteBufferMonitor::putByte(const char data) {
  int result = this->mWriteBuffer.putByte(data);
  if((result >= 0) && this->mMonitor)
    this->mMonitor->putByte(data);

  return result;
}

//-----------------------------------------------------------------------------------------
int WriteBufferMonitor::put(ReadBuffer& readBuffer) {
  return this->put(readBuffer, readBuffer.avariable());
}

//-----------------------------------------------------------------------------------------
int WriteBufferMonitor::put(ReadBuffer& readBuffer, int length) {
  bool peek = (this->mMonitor != nullptr);
  int result = readBuffer.poll(this->mWriteBuffer, length, peek);
  
  if(peek){
    int skip = result - readBuffer.poll(*this->mMonitor, result, false);
    if(skip)
      readBuffer.skip(skip);
  }

  return result;
}

//-----------------------------------------------------------------------------------------
int WriteBufferMonitor::put(const void* buffer, int length) {
  int result = this->mWriteBuffer.put(buffer, length);
  if(this->mMonitor)
    this->mMonitor->put(buffer, result);

  return result;
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
