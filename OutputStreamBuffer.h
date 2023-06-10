/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_F33833E8_A946_4AD2_B467_0E7FD2EE8911
#define MFRAME_F33833E8_A946_4AD2_B467_0E7FD2EE8911

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../io/OutputStream.h"
#include "./../io/ReadBuffer.h"

/* ******************************************************************************
 * Namespace
 */
namespace io {
  class OutputStreamBuffer;
}

/* ******************************************************************************
 * Class/Interface/Struct/Enum
 */

/**
 * @brief 輸出串流緩衝區 <Class>
 *
 */
class io::OutputStreamBuffer : public io::OutputStream,
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
   * @brief Construct a new Output Stream Buffer object
   *
   */
  OutputStreamBuffer(void);

  /**
   * @brief Destroy the Output Stream Buffer object
   *
   */
  virtual ~OutputStreamBuffer(void) override;

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
   * Public Method <Override> - lang::ReadBuffer
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
   * Public Method <Override>
   */

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

#endif /* MFRAME_F33833E8_A946_4AD2_B467_0E7FD2EE8911 */
