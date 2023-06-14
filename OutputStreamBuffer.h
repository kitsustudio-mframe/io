/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_F49C4A53_E633_4A18_B37A_23E496773E8D
#define MFRAME_F49C4A53_E633_4A18_B37A_23E496773E8D

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------
#include "./../io/Buffer.h"
#include "./../io/OutputStream.h"

/* ****************************************************************************************
 * Namespace
 */
namespace mframe::io {
  class OutputStreamBuffer;
}  // namespace mframe::io

/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
class mframe::io::OutputStreamBuffer : public mframe::io::OutputStream,
                                       public mframe::io::Buffer {
  /* **************************************************************************************
   * Variable <Public>
   */

  /* **************************************************************************************
   * Variable <Protected>
   */

  /* **************************************************************************************
   * Variable <Private>
   */
 private:
  mframe::io::Buffer& mBuffer;

  /* **************************************************************************************
   * Abstract method <Public>
   */

  /* **************************************************************************************
   * Abstract method <Protected>
   */

  /* **************************************************************************************
   * Construct Method
   */
 public:
  OutputStreamBuffer(mframe::io::Buffer& buffer);

  virtual ~OutputStreamBuffer(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mframe::lang::WriteBuffer
   */
 public:
  virtual bool isFull(void) const override;

  virtual int remaining(void) const override;

  virtual int putByte(const char data) override;

  virtual int put(mframe::io::ReadBuffer& readBuffer) override;

  virtual int put(mframe::io::ReadBuffer& readBuffer, int length) override;

  virtual int put(const void* buffer, int length) override;

  /* **************************************************************************************
   *  Public Method <Override> - mframe::lang::Iterable<char>
   */
 public:
  virtual bool peekIndex(int index, char& result) override;

  /* **************************************************************************************
   * Public Method <Override> - mframe::lang::ReadBuffer
   */
 public:
  virtual bool isEmpty(void) const override;

  virtual int avariable(void) const override;

  virtual int pollByte(char& result, bool peek) override;

  virtual int poll(mframe::io::WriteBuffer& writeBuffer, bool peek) override;

  virtual int poll(mframe::io::WriteBuffer& writeBuffer, int length, bool peek) override;

  virtual int poll(void* buffer, int bufferSize, bool peek) override;

  virtual int skip(int value) override;

  /* **************************************************************************************
   * Public Method
   */

  /* **************************************************************************************
   * Protected Method <Static>
   */

  /* **************************************************************************************
   * Protected Method <Override>
   */

  /* **************************************************************************************
   * Protected Method
   */

  /* **************************************************************************************
   * Private Method <Static>
   */

  /* **************************************************************************************
   * Private Method <Override>
   */

  /* **************************************************************************************
   * Private Method
   */
};

/* ****************************************************************************************
 * End of file
 */

#endif /* MFRAME_F49C4A53_E633_4A18_B37A_23E496773E8D */
