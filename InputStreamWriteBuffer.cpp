/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ******************************************************************************
 * Include
 */
#include "./InputStreamWriteBuffer.h"

//-------------------------------------------------------------------------------
#include "mframe.h"

/* ******************************************************************************
 * Macro
 */

/* ******************************************************************************
 * Using
 */
using mframe::io::InputStreamWriteBuffer;

//-------------------------------------------------------------------------------
using mframe::io::ReadBuffer;

/* ******************************************************************************
 * Variable <Static>
 */

/* ******************************************************************************
 * Construct Method
 */

//-------------------------------------------------------------------------------
InputStreamWriteBuffer::InputStreamWriteBuffer(void) {
  return;
}

//-------------------------------------------------------------------------------
InputStreamWriteBuffer::~InputStreamWriteBuffer(void) {
  return;
}

/* ******************************************************************************
 * Operator Method
 */

/* ******************************************************************************
 * Public Method <Static>
 */

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::WriteBuffer
 */

//-------------------------------------------------------------------------------
bool InputStreamWriteBuffer::isFull(void) const {
  if (this->mWriteBuffer == nullptr)
    return true;

  return this->mWriteBuffer->isFull();
}

//-------------------------------------------------------------------------------
int InputStreamWriteBuffer::remaining(void) const {
  if (this->mWriteBuffer == nullptr)
    return 0;

  return this->mWriteBuffer->remaining();
}

//-------------------------------------------------------------------------------
int InputStreamWriteBuffer::putByte(const char data) {
  if (this->mWriteBuffer == nullptr)
    return -1;

  int status = this->mWriteBuffer->putByte(data);

  if (status >= 0)
    ++this->mResult;

  if (status <= 0)
    this->execute();

  return status;
}

//-------------------------------------------------------------------------------
int InputStreamWriteBuffer::put(ReadBuffer& readBuffer) {
  return this->put(readBuffer, readBuffer.avariable());
}

//-------------------------------------------------------------------------------
int InputStreamWriteBuffer::put(ReadBuffer& readBuffer, int length) {
  if (this->mWriteBuffer == nullptr)
    return 0;

  int result = this->mWriteBuffer->put(readBuffer, length);
  this->mResult += result;

  if (this->mWriteBuffer->isFull())
    this->execute();

  return result;
}

//-------------------------------------------------------------------------------
int InputStreamWriteBuffer::put(const void* buffer, int length) {
  if (this->mWriteBuffer == nullptr)
    return 0;

  int result = this->mWriteBuffer->put(buffer, length);
  this->mResult += result;

  if (this->mWriteBuffer->isFull())
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
