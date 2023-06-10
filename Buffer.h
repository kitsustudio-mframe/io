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
namespace io {
  struct Buffer;
}

/* ******************************************************************************
 * Class/Interface/Struct/Enum
 */
struct io::Buffer : public io::WriteBuffer, io::ReadBuffer {
  /* ****************************************************************************
   * Method
   */

  /**
   * @brief
   *
   */
  virtual void flush(void) abstract;
};

/* ******************************************************************************
 * End of file
 */

#endif /* MFRAME_574AD0C2_CCFB_47E3_8947_EF72B95F966B */