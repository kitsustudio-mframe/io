/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_53B50485_918E_4B71_A576_99D31C076375
#define MFRAME_53B50485_918E_4B71_A576_99D31C076375

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../io/WriteBuffer.h"
#include "./../lang/Object.h"

/* ******************************************************************************
 * Namespace
 */
namespace io {
  class EmptyWriteBuffer;
}

/* ******************************************************************************
 * Class/Interface/Struct/Enum
 */
class io::EmptyWriteBuffer : public lang::Object,
                             public io::WriteBuffer {
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
   * @brief Construct a new Empty Write Buffer object
   *
   */
  EmptyWriteBuffer(void);

  /**
   * @brief Destroy the Empty Write Buffer object
   *
   */
  virtual ~EmptyWriteBuffer(void) override;

  /* ****************************************************************************
   * Operator Method
   */

  /* ****************************************************************************
   * Public Method <Static>
   */

  /* ****************************************************************************
   * Public Method <Override> - lang::WriteBuffer
   */
 public:
  virtual bool isFull(void) const override;

  virtual int remaining(void) const override;

  virtual int putByte(const char data) override;

  virtual int put(io::ReadBuffer& readBuffer) override;

  virtual int put(io::ReadBuffer& readBuffer, int length) override;

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

#endif /* MFRAME_53B50485_918E_4B71_A576_99D31C076375 */
