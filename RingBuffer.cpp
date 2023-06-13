/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ******************************************************************************
 * Include
 */
#include "./RingBuffer.h"

//-------------------------------------------------------------------------------
#include "mframe.h"

/* ******************************************************************************
 * Macro
 */
#define INDH() (static_cast<int>(RingBuffer::mHead & (RingBuffer::mCount - 1)))
#define INDT() (static_cast<int>(RingBuffer::mTail & (RingBuffer::mCount - 1)))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* ******************************************************************************
 * Using
 */
using mframe::io::RingBuffer;

//-------------------------------------------------------------------------------
using mframe::io::ReadBuffer;
using mframe::io::WriteBuffer;
using mframe::lang::Memory;

/* ******************************************************************************
 * Variable <Static>
 */

/* ******************************************************************************
 * Construct Method
 */

//-------------------------------------------------------------------------------
RingBuffer::RingBuffer(const Memory& memory) : Memory(memory) {
  RingBuffer::init();
  return;
}

//-------------------------------------------------------------------------------
RingBuffer::RingBuffer(int length) : Memory(length) {
  RingBuffer::init();
  return;
}

//-------------------------------------------------------------------------------
RingBuffer::~RingBuffer(void) {
  return;
}

/* ******************************************************************************
 * Operator Method
 */

/* ******************************************************************************
 * Public Method <Static>
 */

/* ******************************************************************************
 *  Public Method <Override> - mframe::lang::Iterable<char>
 */
bool RingBuffer::peekIndex(int index, char& result) {
  if (index >= this->avariable())
    return false;

  int ptrIndex = static_cast<int>((this->mTail + Integers::castUnsigned(index)) & (this->mCount - 1));
  result = *this->pointer(ptrIndex, Class<char>::cast());

  return true;
}

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::ReadBuffer
 */

//-------------------------------------------------------------------------------
int RingBuffer::putByte(const char result) {
  uint8_t* ptr = static_cast<uint8_t*>(RingBuffer::pointer());

  /* We cannot insert when queue is full */
  if (RingBuffer::isFull())
    return -1;

  ptr += INDH();
  *(static_cast<uint8_t*>(ptr)) = (static_cast<const uint8_t>(result));
  RingBuffer::mHead++;

  return this->remaining();
}

//-------------------------------------------------------------------------------
int RingBuffer::put(ReadBuffer& outputBuffer) {
  return RingBuffer::put(outputBuffer, outputBuffer.avariable());
}

//-------------------------------------------------------------------------------
int RingBuffer::put(ReadBuffer& outputBuffer, int length) {
  return this->putMult(&outputBuffer, nullptr, length);
}

//-------------------------------------------------------------------------------
int RingBuffer::put(const void* data, int num) {
  return this->putMult(nullptr, data, num);
}

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::WriteBuffer
 */

//-------------------------------------------------------------------------------
int RingBuffer::pollByte(char& data, bool peek) {
  uint8_t* ptr = static_cast<uint8_t*>(RingBuffer::pointer());

  /* We cannot pop when queue is empty */
  if (this->isEmpty())
    return -1;

  ptr += INDT();
  data = static_cast<char>(*ptr);
  if(!peek)
    ++this->mTail;

  return this->avariable();
}

//-------------------------------------------------------------------------------
int RingBuffer::poll(WriteBuffer& writeBuffer, bool peek) {
  return RingBuffer::poll(writeBuffer, writeBuffer.remaining(), peek);
}

//-------------------------------------------------------------------------------
int RingBuffer::poll(WriteBuffer& writeBuffer, int length, bool peek) {
  return this->pollMult(&writeBuffer, nullptr, length, peek);
}

//-------------------------------------------------------------------------------
int RingBuffer::poll(void* data, int num, bool peek) {
  return this->pollMult(nullptr, data, num, peek);
}

//-------------------------------------------------------------------------------
int RingBuffer::skip(int value) {
  int max = RingBuffer::avariable();

  if (value > max)
    value = max;

  RingBuffer::mTail += static_cast<uint32_t>(value);
  return value;
}

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
//-------------------------------------------------------------------------------
void RingBuffer::init(void) {
  uint32_t bufferSize = static_cast<uint32_t>(this->length());
  this->mHead = 0;
  this->mTail = 0;

  for (int i = 0; i < 32; i++) {
    bufferSize &= ~(1 << i);
    if (!bufferSize) {
      bufferSize = (1 << i);
      break;
    }
  }

  this->mCount = bufferSize;
}

//-------------------------------------------------------------------------------
int RingBuffer::pollMult(mframe::io::WriteBuffer* writeBuffer, void* buffer, int length, bool isPeek) {
  if ((writeBuffer == nullptr) && (buffer == nullptr))
    return 0;

  if (length <= 0)
    return 0;

  int num = length;

  if (writeBuffer){
    num = writeBuffer->remaining();
    if (num > length)
      num = length;
  }

  uint8_t* ptr = static_cast<uint8_t*>(this->pointer());
  int cnt1, cnt2;

  /* We cannot insert when queue is full */
  if (this->isEmpty())
    return 0;

  /* Calculate the segment lengths */
  cnt1 = cnt2 = this->avariable();
  if (INDT() + cnt1 >= static_cast<int>(this->mCount))
    cnt1 = static_cast<int>(this->mCount) - INDT();

  cnt2 -= cnt1;

  cnt1 = MIN(cnt1, num);
  num -= cnt1;

  cnt2 = MIN(cnt2, num);
  num -= cnt2;

  /* Write segment 1 */
  ptr += INDT();

  if (writeBuffer)
    writeBuffer->put(ptr, cnt1);

  else
    Pointers::copy(buffer, ptr, cnt1);

  if (cnt2) {
    ptr = static_cast<uint8_t*>(this->pointer());
    if (writeBuffer)
      writeBuffer->put(ptr, cnt2);

    else
      Pointers::copy(buffer, ptr, cnt2);
  }

  if (!isPeek)
    this->mTail += static_cast<uint32_t>(cnt1 + cnt2);

  return cnt1 + cnt2;
}

//-------------------------------------------------------------------------------
int RingBuffer::putMult(mframe::io::ReadBuffer* readBuffer, const void* buffer, int length) {
  if ((readBuffer == nullptr) && (buffer == nullptr))
    return 0;

  if (length <= 0)
    return 0;

  int num = length;
  if (readBuffer){
    num = readBuffer->avariable();
    if (num > length)
      num = length;
  }


  uint8_t* ptr = this->pointer(Class<uint8_t>::cast());
  int cnt1, cnt2;

  /* We cannot insert when queue is full */
  if (this->isFull())
    return 0;

  /* Calculate the segment lengths */
  cnt1 = cnt2 = this->remaining();
  if (INDH() + cnt1 >= static_cast<int>(this->mCount))
    cnt1 = static_cast<int>(this->mCount) - INDH();

  cnt2 -= cnt1;

  cnt1 = MIN(cnt1, num);
  num -= cnt1;

  cnt2 = MIN(cnt2, num);
  num -= cnt2;

  /* Write segment 1 */
  ptr += INDH();
  if (readBuffer)
    readBuffer->poll(ptr, cnt1, false);
  else
    Pointers::copy(ptr, buffer, cnt1);

  /* Write segment 2 */
  if (cnt2) {
    ptr = this->pointer(Class<uint8_t>::cast());
    if (readBuffer)
      readBuffer->poll(ptr, cnt2, false);

    else
      Pointers::copy(ptr, buffer, cnt2);
  }

  this->mHead += static_cast<uint32_t>(cnt1 + cnt2);
  return (cnt1 + cnt2);
}
/* ******************************************************************************
 * End of file
 */
