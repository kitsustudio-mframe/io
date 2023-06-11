/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MFRAME_F628179A_5A6B_4572_99A4_3338D77AED7B
#define MFRAME_F628179A_5A6B_4572_99A4_3338D77AED7B

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../lang/Interface.h"

/* ******************************************************************************
 * Namespace
 */
namespace mframe::io {
  template <typename V, typename A>
  struct CompletionHandler;
}  // namespace mframe::io

/* ******************************************************************************
 * Class/struct/Struct
 */
template <typename V, typename A>
struct mframe::io::CompletionHandler : public virtual mframe::lang::Interface {
  /* ****************************************************************************
   *  Method
   */

  /**
   * @brief
   *
   * @param result
   * @param attachment
   */
  virtual void completed(V result, A attachment) abstract;

  /**
   * @brief
   *
   * @param exc
   * @param attachment
   */
  virtual void failed(void* exc, A attachment) abstract;
};

/* *******************************************************************************
 *    End of file
 */

#endif /* MFRAME_F628179A_5A6B_4572_99A4_3338D77AED7B */
