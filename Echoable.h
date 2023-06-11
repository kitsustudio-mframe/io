/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_222C3DA5_0CEC_43AE_8CBE_04BF7A36FE4C
#define MFRAME_222C3DA5_0CEC_43AE_8CBE_04BF7A36FE4C

/* ****************************************************************************************
 * Include
 */

//-----------------------------------------------------------------------------------------
#include "./../io/WriteBuffer.h"
#include "./../lang/Interface.h"

/* ****************************************************************************************
 * Namespace
 */
namespace mframe::io {
  struct Echoable;
}  // namespace mframe::io

/* ****************************************************************************************
 * Class/Interface/Struct/Enum
 */
struct mframe::io::Echoable : public virtual mframe::lang::Interface {
  /* **************************************************************************************
   * Method
   */

  /**
   * @brief 啟用或停用echo模式
   *
   * @param enable
   * @return true 啟用echo
   * @return false 停用echo
   */
  virtual bool echo(bool enable) abstract;
};

/* ****************************************************************************************
 * End of file
 */

#endif /* MFRAME_222C3DA5_0CEC_43AE_8CBE_04BF7A36FE4C */
