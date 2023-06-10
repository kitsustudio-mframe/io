/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_9211D576_B0C2_4C52_93CE_C47BB00192E1
#define MFRAME_9211D576_B0C2_4C52_93CE_C47BB00192E1

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../io/ReadBuffer.h"
#include "./../lang/Object.h"

/* ******************************************************************************
 * Namespace
 */
namespace io {
  class EmptyReadBuffer;
}

/* ******************************************************************************
 * Class/Interface/Struct/Enum
 */
class io::EmptyReadBuffer : public lang::Object,
                            public io::ReadBuffer {
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
   * @brief Construct a new Empty Read Buffer object
   *
   */
  EmptyReadBuffer(void);

  /**
   * @brief Destroy the Empty Read Buffer object
   *
   */
  virtual ~EmptyReadBuffer(void) override;

  /* ****************************************************************************
   * Operator Method
   */

  /* ****************************************************************************
   * Public Method <Static>
   */

  /* ****************************************************************************
   *  Public Method <Override> - lang::Iterable<char>
   */
 public:
  virtual bool peekIndex(int index, char& result) override;

  /* ****************************************************************************
   * Public Method <Override> - io::ReadBuffer
   */
 public:
  virtual bool isEmpty(void) const override;

  virtual int avariable(void) const override;

  virtual int pollByte(char& result) override;

  virtual int poll(io::WriteBuffer& writeBuffer) override;

  virtual int poll(io::WriteBuffer& writeBuffer, int length) override;

  virtual int poll(void* buffer, int bufferSize) override;

  virtual int skip(int value) override;
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

#endif /* MFRAME_9211D576_B0C2_4C52_93CE_C47BB00192E1 */
