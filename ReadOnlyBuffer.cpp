/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ******************************************************************************
 * Include
 */
#include "./ReadOnlyBuffer.h"

//-------------------------------------------------------------------------------
#include "mframe_io.h"
#include "mframe_lang.h"

/* ******************************************************************************
 * Macro
 */

/* ******************************************************************************
 * Using
 */
using io::ReadOnlyBuffer;

//-------------------------------------------------------------------------------
using io::WriteBuffer;

/* ******************************************************************************
 * Variable <Static>
 */

/* ******************************************************************************
 * Construct Method
 */

//-------------------------------------------------------------------------------
ReadOnlyBuffer::ReadOnlyBuffer(const char* str) : Data(str, static_cast<unsigned int>(Character::length(str))) {
  this->mPosition = 0;
  return;
}

//-------------------------------------------------------------------------------
ReadOnlyBuffer::ReadOnlyBuffer(const void* pointer, size_t length) : Data(pointer, length) {
  this->mPosition = 0;
  return;
}

//-------------------------------------------------------------------------------
ReadOnlyBuffer::~ReadOnlyBuffer(void) {
  this->mPosition = 0;
  return;
}

/* ******************************************************************************
 * Operator Method
 */

/* ******************************************************************************
 * Public Method <Static>
 */

/* ******************************************************************************
 *  Public Method <Override> - lang::Iterable<char>
 */

//-------------------------------------------------------------------------------
bool ReadOnlyBuffer::peekIndex(int index, char& result) {
  if (index >= this->avariable())
    return false;

  result = *(this->pointer((this->mPosition + index), Class<char>::cast()));
  return true;
}

/* ******************************************************************************
 * Public Method <Override> - lang::ReadBuffer
 */

//-------------------------------------------------------------------------------
int ReadOnlyBuffer::pollByte(char& result) {
  if (this->isEmpty())
    return -1;

  result = *this->pointer(this->mPosition, Class<char>::cast());
  ++this->mPosition;

  return this->avariable();
}

//-------------------------------------------------------------------------------
int ReadOnlyBuffer::poll(WriteBuffer& writeBuffer) {
  return ReadOnlyBuffer::poll(writeBuffer, this->avariable());
}

//-------------------------------------------------------------------------------
int ReadOnlyBuffer::poll(WriteBuffer& writeBuffer, int length) {
  if (length <= 0)
    return 0;

  if (this->isEmpty())
    return 0;

  int max = this->avariable();
  if (length > max)
    length = max;

  int result = writeBuffer.put(this->pointer(mPosition), this->avariable());
  this->mPosition += result;
  return result;
}

//-------------------------------------------------------------------------------
int ReadOnlyBuffer::poll(void* buffer, int bufferSize) {
  if (this->isEmpty())
    return 0;

  int result = this->length();
  if (result >= bufferSize)
    bufferSize = result;

  if (buffer != nullptr)
    this->copyTo(buffer, 0, this->mPosition, bufferSize);

  this->mPosition += result;
  return result;
}

//-------------------------------------------------------------------------------
int ReadOnlyBuffer::skip(int value) {
  return this->poll(nullptr, value);
}

/* ******************************************************************************
 * Public Method
 */

//-------------------------------------------------------------------------------
bool ReadOnlyBuffer::position(int newPosition) {
  if (newPosition < 0)
    return false;

  if (newPosition > this->capacity())
    return false;

  this->mPosition = newPosition;
  return true;
}

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