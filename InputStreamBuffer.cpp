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
InputStreamBuffer::InputStreamBuffer(void) {
  this->mBuffer = nullptr;
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
 *  Public Method <Override> - mframe::io::Buffer
 */

//-----------------------------------------------------------------------------------------
void InputStreamBuffer::flush(void) {
  if (this->mBuffer)
    this->mBuffer->flush();

  return;
}

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
  this->mResult = 0;
  if (this->mBuffer)
    this->mResult = writeBuffer.put(*this->mBuffer);

  if (writeBuffer.isFull())
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

  if (this->mBuffer)
    return this->mBuffer->isFull();

  return true;
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::remaining(void) const {
  if (this->mWriteBuffer)
    return this->mWriteBuffer->remaining();

  if (this->mBuffer)
    return this->mBuffer->remaining();

  return 0;
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

  if (this->mBuffer)
    return this->mBuffer->putByte(data);

  return 0;
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

    if (this->mBuffer)
      result += this->mBuffer->put(readBuffer, (length - result));
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
    if (this->mBuffer)
      result += this->mBuffer->put(buffer, length);
  }

  return result;
}

/* ****************************************************************************************
 *  Public Method <Override> - mframe::lang::Iterable<char>
 */

//-----------------------------------------------------------------------------------------
bool InputStreamBuffer::peekIndex(int index, char& result) {
  if (this->mBuffer)
    return this->mBuffer->peekIndex(index, result);

  return false;
}

/* ****************************************************************************************
 * Public Method <Override> - mframe::lang::ReadBuffer
 */

//-----------------------------------------------------------------------------------------
bool InputStreamBuffer::isEmpty(void) const {
  if (this->mBuffer)
    return this->mBuffer->isEmpty();

  return false;
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::avariable(void) const {
  if (this->mBuffer)
    return this->mBuffer->avariable();

  return false;
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::pollByte(char& result, bool peek) {
  int status = -1;
  if (this->mBuffer) {
    status = this->mBuffer->pollByte(result, peek);
    if (!peek)
      this->onBufferPollEvent();
  }

  return status;
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::poll(WriteBuffer& writeBuffer, bool peek) {
  return this->poll(writeBuffer, writeBuffer.remaining(), peek);
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::poll(WriteBuffer& writeBuffer, int length, bool peek) {
  int result = 0;
  if (this->mBuffer) {
    result = this->mBuffer->poll(writeBuffer, length, peek);
    if (!peek)
      this->onBufferPollEvent();
  }

  return result;
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::poll(void* buffer, int bufferSize, bool peek) {
  int result = 0;
  if (this->mBuffer) {
    result = this->mBuffer->poll(buffer, bufferSize, peek);
    if (!peek)
      this->onBufferPollEvent();
  }

  return result;
}

//-----------------------------------------------------------------------------------------
int InputStreamBuffer::skip(int value) {
  int result = 0;
  if (this->mBuffer) {
    result = this->mBuffer->skip(value);
    if (result)
      this->onBufferPollEvent();
  }

  return 0;
}

/* ****************************************************************************************
 * Public Method
 */

//-----------------------------------------------------------------------------------------
void InputStreamBuffer::setDefaultBuffer(Buffer* buffer) {
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
void InputStreamBuffer::onBufferPollEvent(void) {
  return;
}
/* ****************************************************************************************
 * Private Method
 */

/* ****************************************************************************************
 * End of file
 */
