/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* ******************************************************************************
 * Include
 */
#include "./InputStream.h"

//-------------------------------------------------------------------------------

#include "mframe.h"

/* ******************************************************************************
 * Macro
 */

/* ******************************************************************************
 * Using
 */
using mframe::io::InputStream;

//-------------------------------------------------------------------------------
using mframe::io::CompletionHandler;
using mframe::io::WriteBuffer;
using mframe::util::Future;

/* ******************************************************************************
 * Variable <Static>
 */

/* ******************************************************************************
 * Construct Method
 */

//-------------------------------------------------------------------------------
InputStream::InputStream(void) {
  this->mAttachment = nullptr;
  this->mCompletionHandler = nullptr;
  this->mWriteBuffer = nullptr;
  this->mResult = 0;
  this->mHandling = false;
  return;
}

//-------------------------------------------------------------------------------
InputStream::~InputStream(void) {
  this->abortRead();
  return;
}

/* ******************************************************************************
 * Operator Method
 */

/* ******************************************************************************
 * Public Method <Static>
 */

/* ******************************************************************************
 * Public Method <Override> - mframe::lang::Runnable
 */

//-------------------------------------------------------------------------------
void InputStream::run(void) {
  CompletionHandler<int, void*>* handler = this->mCompletionHandler;
  void* attachment = this->mAttachment;
  int result = this->mResult;

  this->mResult = 0;
  this->mWriteBuffer = nullptr;
  this->mHandling = false;

  if (handler)
    handler->completed(result, attachment);

  return;
}

/* ******************************************************************************
 * Public Method
 */

//-------------------------------------------------------------------------------
bool InputStream::abortRead(void) {
  if (!this->readBusy())
    return false;

  this->execute();
  return true;
}

//-------------------------------------------------------------------------------
bool InputStream::readBusy(void) {
  return ((this->mWriteBuffer != nullptr) || this->mHandling);
}

//-------------------------------------------------------------------------------
bool InputStream::read(WriteBuffer& writeBuffer, int timeout) {
  Future future = Future();
  if (this->read(writeBuffer, future) == false)
    return false;

  future.waitDone(timeout);
  if (future.isBusy())
    this->abortRead();

  future.waitDone();
  return true;
}

//-------------------------------------------------------------------------------
bool InputStream::read(WriteBuffer& writeBuffer,
                       void* attachment,
                       CompletionHandler<int, void*>* handler) {
  if (this->readBusy())
    return false;

  this->mAttachment = attachment;
  this->mCompletionHandler = handler;
  this->mResult = 0;

  if (writeBuffer.isFull())
    this->execute();

  else
    this->mWriteBuffer = &writeBuffer;

  this->onReadEvent();
  return true;
}

//-------------------------------------------------------------------------------
bool InputStream::read(WriteBuffer& writeBuffer, Future& future) {
  if (!future.isIdle())
    return false;

  future.setWait();
  bool result = this->read(writeBuffer, nullptr, &future);
  if (result == false)
    future.clear();

  return result;
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

//-------------------------------------------------------------------------------
void InputStream::execute(void) {
  if (this->mHandling)
    return;

  this->mHandling = true;
  this->mWriteBuffer = nullptr;
  System::execute(*this);
  return;
}

//-------------------------------------------------------------------------------
void InputStream::onReadEvent(void) {
  return;
}
/* ******************************************************************************
 * End of file
 */
