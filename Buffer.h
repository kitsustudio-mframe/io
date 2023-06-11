/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_574AD0C2_CCFB_47E3_8947_EF72B95F966B
#define MFRAME_574AD0C2_CCFB_47E3_8947_EF72B95F966B

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../io/ReadBuffer.h"
#include "./../io/WriteBuffer.h"

/* ******************************************************************************
 * Namespace
 */
namespace mframe::io {
  struct Buffer;
}  // namespace mframe::io

/* ******************************************************************************
 * Class/Interface/Struct/Enum
 */
struct mframe::io::Buffer : public mframe::io::WriteBuffer,
                            public mframe::io::ReadBuffer {
  /* ****************************************************************************
   * Method
   */

  /**
   * @brief 沖洗緩衝區。
   *
   */
  virtual void flush(void) abstract;
};

/* ******************************************************************************
 * End of file
 */

#endif /* MFRAME_574AD0C2_CCFB_47E3_8947_EF72B95F966B */
