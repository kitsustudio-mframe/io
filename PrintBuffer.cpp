/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ******************************************************************************
 * Include
 */
#include "./PrintBuffer.h"

//-------------------------------------------------------------------------------
#include "mframe_io.h"
#include "mframe_lang.h"

/* ******************************************************************************
 * Macro
 */

/* ******************************************************************************
 * Using
 */
using io::PrintBuffer;

//-------------------------------------------------------------------------------
using io::RingBuffer;
using lang::Memory;
using lang::StringFormat;
using lang::Strings;

/* ******************************************************************************
 * Variable <Static>
 */

/* ******************************************************************************
 * Construct Method
 */

//-------------------------------------------------------------------------------
PrintBuffer::PrintBuffer(void* buffer, uint32_t bufferSize) : RingBuffer(buffer, bufferSize) {
  return;
}

//-------------------------------------------------------------------------------
PrintBuffer::PrintBuffer(const Memory& memory) : RingBuffer(memory) {
  return;
}

//-------------------------------------------------------------------------------
PrintBuffer::PrintBuffer(uint32_t length) : RingBuffer(length) {
  return;
}

//-------------------------------------------------------------------------------
PrintBuffer::~PrintBuffer(void) {
  return;
}

/* ******************************************************************************
 * Operator Method
 */

/* ******************************************************************************
 * Public Method <Static>
 */

/* ******************************************************************************
 * Public Method
 */

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(bool b, bool newLine) {
  if (b)
    this->put("True", 4);

  else
    this->put("False", 5);

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(char c, bool newLine) {
  this->putByte(c);

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(double d, bool newLine) {
  lang::StringFormat::writeBuffer(*this, "%f", d);

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(float f, bool newLine) {
  lang::StringFormat::writeBuffer(*this, "%f", static_cast<double>(f));

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(int i, bool newLine, bool unsign) {
  if (unsign)
    lang::StringFormat::writeBuffer(*this, "%d", static_cast<unsigned int>(i));

  else
    lang::StringFormat::writeBuffer(*this, "%d", i);

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(const Strings& string, bool newLine) {
  this->put(string, string.size());

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(const char* string, bool newLine) {
  this->put(string, Strings::getLength(string));

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::print(ReadBuffer& readBuffer, bool newLine) {
  this->put(readBuffer);

  if (newLine)
    this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::println(void) {
  this->putByte('\n');

  return *this;
}

//-------------------------------------------------------------------------------
PrintBuffer& PrintBuffer::format(const char* format, ...) {
  va_list args;
  va_start(args, format);
  StringFormat::writeBufferVa(*this, format, args);
  va_end(args);

  return *this;
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
