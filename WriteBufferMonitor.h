/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_F581AE1C_B9B4_4A3A_9E1E_6349940CFBD0
#define MFRAME_F581AE1C_B9B4_4A3A_9E1E_6349940CFBD0

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------
#include "./../io/WriteBuffer.h"
#include "./../lang/Object.h"

/* ****************************************************************************************
 * Namespace
 */
namespace mframe::io {
  class WriteBufferMonitor;
}  // namespace mframe::io

/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
class mframe::io::WriteBufferMonitor : public mframe::lang::Object,
                                       public mframe::io::WriteBuffer {
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
  mframe::io::WriteBuffer& mWriteBuffer;
  mframe::io::WriteBuffer* mMonitor;

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
  /**
   * @brief Construct a new Write Buffer Monitor object
   *
   * @param writeBuffer
   */
  WriteBufferMonitor(mframe::io::WriteBuffer& writeBuffer);

  /**
   * @brief Destroy the Write Buffer Monitor object
   *
   */
  virtual ~WriteBufferMonitor(void) override;

  /* **************************************************************************************
   * Operator Method
   */

  /* **************************************************************************************
   * Public Method <Static>
   */

  /* **************************************************************************************
   * Public Method <Override> - mframe::io::WriteBuffer
   */
 public:
  virtual bool isFull(void) const override;

  virtual int remaining(void) const override;

  virtual int putByte(const char data) override;

  virtual int put(mframe::io::ReadBuffer& readBuffer) override;

  virtual int put(mframe::io::ReadBuffer& readBuffer, int length) override;

  virtual int put(const void* buffer, int length) override;

  /* **************************************************************************************
   * Public Method
   */
 public:
  /**
   * @brief 設定監視器
   *
   * @param monitor
   * - null 取消監聽
   * - other 建立監聽事件
   */
  virtual void setMonitor(mframe::io::WriteBuffer* monitor);

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

#endif /* MFRAME_F581AE1C_B9B4_4A3A_9E1E_6349940CFBD0 */
