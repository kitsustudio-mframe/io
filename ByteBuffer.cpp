/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ******************************************************************************
 * Include
 */
#include "./ByteBuffer.h"

//-------------------------------------------------------------------------------
#include "mframe.h"

/* ******************************************************************************
 * Using
 */

using mframe::io::ByteBuffer;
//-------------------------------------------------------------------------------
using mframe::io::ReadBuffer;
using mframe::io::WriteBuffer;
using mframe::lang::Memory;
using mframe::lang::Strings;

/* ******************************************************************************
 * Construct Method
 */

//-------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(const Memory& memory) : Memory(memory) {
  ByteBuffer::flush();
  return;
}

//-------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(int length) : Memory(length) {
  ByteBuffer::flush();
  return;
}

//-------------------------------------------------------------------------------
ByteBuffer::~ByteBuffer(void) {
  return;
}

/* ******************************************************************************
 * Operator Method
 */

/* ******************************************************************************
 * Public Method <Static>
 */

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::Memory
 */

//-------------------------------------------------------------------------------
int ByteBuffer::indexOf(char ch, int start) const {
  return Pointer::indexOf(ch, start, ByteBuffer::limit());
}

//-------------------------------------------------------------------------------
int ByteBuffer::indexOfData(const void* destination, int destinationLen, int start) const {
  return Pointer::indexOfData(destination, destinationLen, start, ByteBuffer::limit());
}

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::Iterable<char>
 */
//-------------------------------------------------------------------------------
bool ByteBuffer::peekIndex(int index, char& result) {
  if (index >= this->remaining())
    return false;

  result = *this->pointer((this->mPosition + index), Class<char>::cast());

  return true;
}

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::ReadBufferBuffer
 */

//-------------------------------------------------------------------------------
int ByteBuffer::pollByte(char& result, bool peek) {
  if (this->mPosition >= this->mLimit)
    return -1;

  result = *this->pointer(this->mPosition, Class<char>::cast());
  this->position(this->position() + 1);
  return this->remaining();
}

//-------------------------------------------------------------------------------
int ByteBuffer::poll(WriteBuffer& writeBuffer, bool peek) {
  return this->poll(writeBuffer, writeBuffer.remaining(), peek);
}

//-------------------------------------------------------------------------------
int ByteBuffer::poll(WriteBuffer& writeBuffer, int length, bool peek) {
  if (length <= 0)
    return 0;

  int max = this->avariable();
  if (length > max)
    length = max;

  int result = writeBuffer.put(this->pointer(this->mPosition), length);

  if(!peek)
    this->position(this->position() + result);

  return result;
}

//-------------------------------------------------------------------------------
int ByteBuffer::poll(void* buffer, int bufferSize, bool peek) {
  int max = this->avariable();
  int pos = this->position();
  if (bufferSize > max)
    bufferSize = max;

  this->copyTo(buffer, pos, bufferSize);

  if(!peek)
    this->position(pos + bufferSize);

  return bufferSize;
}

//-------------------------------------------------------------------------------
int ByteBuffer::skip(int value) {
  int max = this->avariable();
  if (value > max)
    value = max;

  this->position(this->position() + value);
  return value;
}

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::WriteBuffer
 */

//-------------------------------------------------------------------------------
int ByteBuffer::putByte(const char value) {
  if (this->mPosition >= this->mLimit)
    return -1;

  *static_cast<uint8_t*>(this->pointer(this->mPosition++)) = value;
  return this->remaining();
}

//-------------------------------------------------------------------------------
int ByteBuffer::put(ReadBuffer& readBuffer) {
  return this->put(readBuffer, readBuffer.avariable());
}

//-------------------------------------------------------------------------------
int ByteBuffer::put(ReadBuffer& readBuffer, int length) {
  if (length <= 0)
    return 0;

  int max = this->remaining();
  if (length > max)
    length = max;

  int result = readBuffer.poll(this->pointer(this->mPosition), length, false);
  this->position(this->position() + result);
  return result;
}

//-------------------------------------------------------------------------------
int ByteBuffer::put(const void* buffer, int bufferSize) {
  if (bufferSize <= 0)
    return false;

  int max = this->remaining();

  if (bufferSize > max)
    bufferSize = max;

  this->copy(buffer, 0, this->mPosition, bufferSize);
  this->position(this->position() + bufferSize);

  return bufferSize;
}

/* ******************************************************************************
 * Public Method
 */

//-------------------------------------------------------------------------------
bool ByteBuffer::limit(int newLimit) {
  if (newLimit < 0)
    return false;

  if (newLimit > this->length())
    return false;

  this->mLimit = newLimit;
  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::position(int newPosition) {
  if (newPosition < 0)
    return false;

  if (newPosition > this->limit())
    return false;

  this->mPosition = newPosition;
  return true;
}

//-------------------------------------------------------------------------------
void ByteBuffer::flip(void) {
  this->mLimit = this->mPosition;
  this->mPosition = 0;
  return;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::put(char const* string) {
  return this->put(string, static_cast<int>(Strings::getLength(string)));
}

//-------------------------------------------------------------------------------
bool ByteBuffer::put(const Strings& string) {
  return this->put(string.pointer(), string.size());
}

//-------------------------------------------------------------------------------
int ByteBuffer::putFormat(const char* format, ...) {
  if (this->isReadOnly())
    return 0;

  va_list args;
  va_start(args, format);
  int result =
      StringFormat::pointerVa(this->pointer(this->mPosition),
                              static_cast<size_t>(this->remaining()), format, args);

  va_end(args);

  this->mPosition += result;
  return result;
}

//-------------------------------------------------------------------------------
int ByteBuffer::putFormat(const char* format, va_list args) {
  int result =
      StringFormat::pointerVa(this->pointer(this->mPosition),
                              static_cast<size_t>(this->remaining()), format, args);
  this->mPosition += result;
  return result;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::putShort(short value) {
  if ((this->mPosition + 1) >= this->mLimit)
    return false;

  *static_cast<short*>(this->pointer(this->mPosition)) = value;
  this->mPosition += 2;

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::putShortMsb(short value) {
  if ((this->mPosition + 1) >= this->mLimit)
    return false;

  uint8_t* ptr = static_cast<uint8_t*>(this->pointer());

  ptr[this->mPosition++] = static_cast<uint8_t>(value >> 8);
  ptr[this->mPosition++] = static_cast<uint8_t>(value);

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::putInt(int value) {
  if ((this->mPosition + 3) >= this->mLimit)
    return false;

  *static_cast<int*>(this->pointer(this->mPosition)) = value;
  this->mPosition += 4;

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::putIntMsb(int value) {
  if ((this->mPosition + 3) >= this->mLimit)
    return false;

  uint8_t* ptr = static_cast<uint8_t*>(this->pointer());

  ptr[this->mPosition++] = static_cast<uint8_t>(value >> 24);
  ptr[this->mPosition++] = static_cast<uint8_t>(value >> 16);
  ptr[this->mPosition++] = static_cast<uint8_t>(value >> 8);
  ptr[this->mPosition++] = static_cast<uint8_t>(value);

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::putFloat(const float value) {
  const int* i = reinterpret_cast<const int*>(&value);
  return this->putInt(*i);
}

//-------------------------------------------------------------------------------
bool ByteBuffer::putFloatMsb(const float value) {
  const int* i = reinterpret_cast<const int*>(&value);
  return this->putIntMsb(*i);
}

//-------------------------------------------------------------------------------
bool ByteBuffer::pollShort(short& result) {
  if ((this->mPosition + 1) >= this->mLimit)
    return false;

  result = *static_cast<short*>(this->pointer(this->mPosition));
  this->mPosition += 2;

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::pollShortMsb(short& result) {
  if ((this->mPosition + 1) >= this->mLimit)
    return false;

  uint8_t* ptr = static_cast<uint8_t*>(this->pointer());

  result = 0;
  result |= (static_cast<short>(ptr[this->mPosition++]) << 8);
  result |= (static_cast<short>(ptr[this->mPosition++]));

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::pollInt(int& result) {
  if ((this->mPosition + 3) >= this->mLimit)
    return false;

  result = *static_cast<int*>(this->pointer(this->mPosition));
  this->mPosition += 4;

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::pollIntMsb(int& result) {
  if ((this->mPosition + 3) >= this->mLimit)
    return false;

  uint8_t* ptr = static_cast<uint8_t*>(this->pointer());

  result = 0;
  result |= (static_cast<int>(ptr[this->mPosition++]) << 24);
  result |= (static_cast<int>(ptr[this->mPosition++]) << 16);
  result |= (static_cast<int>(ptr[this->mPosition++]) << 8);
  result |= (static_cast<int>(ptr[this->mPosition++]));

  return true;
}

//-------------------------------------------------------------------------------
bool ByteBuffer::pollFloat(float& result) {
  int* r = reinterpret_cast<int*>(&result);
  return this->pollInt(*r);
}

//-------------------------------------------------------------------------------
bool ByteBuffer::pollFloatMsb(float& result) {
  int* r = reinterpret_cast<int*>(&result);
  return this->pollIntMsb(*r);
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
