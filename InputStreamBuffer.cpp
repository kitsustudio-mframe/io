/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ****************************************************************************************
 * Include
 */
#include "./InputStreamBuffer.h"

//-----------------------------------------------------------------------------------------
#include "mframe.h"

/* ****************************************************************************************
 * Macro
 */

/* ****************************************************************************************
 * Using
 */
using mframe::io::InputStreamBuffer;

//-----------------------------------------------------------------------------------------
using mframe::io::Buffer;
using mframe::io::CompletionHandler;
using mframe::io::ReadBuffer;
using mframe::io::WriteBuffer;

/* ****************************************************************************************
 * Variable <Static>
 */

//-----------------------------------------------------------------------------------------
InputStreamBuffer::InputStreamBuffer(Buffer& buffer) : mBuffer(buffer) {
  return;
}

//-----------------------------------------------------------------------------------------
InputStreamBuffer::~InputStreamBuffer(void) {
  return;
}

/* ****************************************************************************************
 * Operator Method
 */

/* ****************************************************************************************
 * Public Method <Static>
 */

/* ****************************************************************************************
 *  Public Method <Override> - mframe::io::InputStream
 */
//-----------------------------------------------------------------------------------------
bool InputStreamBuffer::read(WriteBuffer& writeBuffer, void* attachment,
                             CompletionHandler<int, void*>* handler) {
  if (this->readBusy())
    return false;

  this->mAttachment = attachment;
  this->mCompletionHandler = handler;
  this->mResult = writeBuffer.put(this->mBuffer);

  if (this->mWriteBuffer->isFull())
    this->execute();

  else
    this->mWriteBuffer = &writeBuffer;

  this->onReadEvent();
  return true;
}

/* ****************************************************************************************
 * Public Method <Override> - mframe::lang::WriteBuffer
 */

//-----------------------------------------------------------------------------------------
bool InputStreamBuffer::isFull(void) const {
  if (this->mWriteBuffer)
    return this->mWriteBuffer->isFull();

  return this->mBuffer.isFull();
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::remaining(void) const {
  if (this->mWriteBuffer)
    return this->mWriteBuffer->remaining();

  return this->mBuffer.remaining();
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::putByte(const char data) {
  if (this->mWriteBuffer) {
    int result = this->mWriteBuffer->putByte(data);
    if (result <= 0)
      this->execute();

    else
      ++this->mResult;

    return result;
  }

  return this->mBuffer.putByte(data);
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::put(ReadBuffer& readBuffer) {
  return this->put(readBuffer, readBuffer.avariable());
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::put(ReadBuffer& readBuffer, int length) {
  int result = 0;

  if (this->mWriteBuffer) {
    result = this->mWriteBuffer->put(readBuffer, length);
    this->mResult += result;
  }

  if (length > result) {
    this->execute();
    result += this->mBuffer.put(readBuffer, (length - result));
  }

  return result;
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::put(const void* buffer, int length) {
  int result = 0;

  if (this->mWriteBuffer) {
    result = this->mWriteBuffer->put(buffer, length);
    this->mResult += result;
  }

  if (length > result) {
    this->execute();
    result += this->mBuffer.put(buffer, length);
  }

  return result;
}

/* ****************************************************************************************
 *  Public Method <Override> - mframe::lang::Iterable<char>
 */

//-----------------------------------------------------------------------------------------
bool InputStreamBuffer::peekIndex(int index, char& result) {
  return this->mBuffer.peekIndex(index, result);
}

/* ****************************************************************************************
 * Public Method <Override> - mframe::lang::ReadBuffer
 */

//-----------------------------------------------------------------------------------------
bool InputStreamBuffer::isEmpty(void) const {
  return this->mBuffer.isEmpty();
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::avariable(void) const {
  return this->mBuffer.avariable();
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::pollByte(char& result, bool peek) {
  return this->mBuffer.pollByte(result, peek);
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::poll(WriteBuffer& writeBuffer, bool peek) {
  return this->mBuffer.poll(writeBuffer, peek);
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::poll(WriteBuffer& writeBuffer, int length, bool peek) {
  return this->mBuffer.poll(writeBuffer, length, peek);
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::poll(void* buffer, int bufferSize, bool peek) {
  return this->mBuffer.poll(buffer, bufferSize, peek);
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::skip(int value) {
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
