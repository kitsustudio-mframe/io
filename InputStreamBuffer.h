/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_24732F21_BBC1_4AB0_8238_ACE2005FF0DF
#define MFRAME_24732F21_BBC1_4AB0_8238_ACE2005FF0DF

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../io/InputStream.h"
#include "./../lang/Runnable.h"

/* ******************************************************************************
 * Namespace
 */
namespace mframe::io {
  class InputStreamBuffer;
}  // namespace mframe::io

/* ******************************************************************************
 * Class/Interface/Struct/Enum
 */
class mframe::io::InputStreamBuffer : public mframe::io::InputStream,
                                      public mframe::io::WriteBuffer {
  /* ****************************************************************************
   * Variable <Public>
   */

  /* ****************************************************************************
   * Variable <Protected>
   */

  /* ****************************************************************************
   * Variable <Private>
   */

  /* ****************************************************************************
   * Abstract method <Public>
   */

  /* ****************************************************************************
   * Abstract method <Protected>
   */

  /* ****************************************************************************
   * Construct Method
   */
 public:
  /**
   * @brief Construct a new Input Stream Buffer object
   *
   */
  InputStreamBuffer(void);

  /**
   * @brief Destroy the Input Stream Buffer object
   *
   */
  virtual ~InputStreamBuffer(void) override;

  /* ****************************************************************************
   * Operator Method
   */

  /* ****************************************************************************
   * Public Method <Static>
   */

  /* ****************************************************************************
   * Public Method <Override> - mframe::lang::WriteBuffer
   */
 public:
  virtual bool isFull(void) const override;

  virtual int remaining(void) const override;

  virtual int putByte(const char data) override;

  virtual int put(mframe::io::ReadBuffer& readBuffer) override;

  virtual int put(mframe::io::ReadBuffer& readBuffer, int length) override;

  virtual int put(const void* buffer, int length) override;

  /* ****************************************************************************
   * Public Method
   */

  /* ****************************************************************************
   * Protected Method <Static>
   */

  /* ****************************************************************************
   * Protected Method <Override>
   */

  /* ****************************************************************************
   * Protected Method
   */

  /* ****************************************************************************
   * Private Method <Static>
   */

  /* ****************************************************************************
   * Private Method <Override>
   */

  /* ****************************************************************************
   * Private Method
   */
};

/* ******************************************************************************
 * End of file
 */

#endif /* MFRAME_24732F21_BBC1_4AB0_8238_ACE2005FF0DF */
