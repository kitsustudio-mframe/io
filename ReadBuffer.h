/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_739FA0D6_740F_4CA0_975C_FD713D983D41
#define MFRAME_739FA0D6_740F_4CA0_975C_FD713D983D41

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../lang/Iterable.h"

/* ******************************************************************************
 * Namespace
 */
namespace mframe::io {
  struct ReadBuffer;
  struct WriteBuffer;
}  // namespace mframe::io

/* ******************************************************************************
 * Class/struct/Struct/Enum
 */
struct mframe::io::ReadBuffer : public mframe::lang::Iterable<char> {
  /* ****************************************************************************
   * Method
   */

  /**
   * @brief 輸出緩存是否為空?
   *
   * @return true 輸出緩存為空
   * @return false 輸出緩存不為空
   */
  virtual bool isEmpty(void) const abstract;

  /**
   * @brief 取得輸出緩存內剩餘多少位元組
   *
   * @return int 緩存內有效位元組數量
   */
  virtual int avariable(void) const abstract;

  /**
   * @brief 檢索一個字節，並由此緩衝區刪除
   *
   * @param result
   * @param peek true 啟用窺視，僅讀取不刪除
   * @return int 緩衝區剩餘可讀取數量
   */
  virtual int pollByte(char& result, bool peek) abstract;

  /**
   * @brief 檢索至writeBuffer，並由此緩衝區刪除
   *
   * @param writeBuffer 輸出緩衝區
   * @param peek true 啟用窺視，僅讀取不刪除
   * @return int 檢索的位元組數量
   */
  virtual int poll(mframe::io::WriteBuffer& writeBuffer, bool peek) abstract;

  /**
   * @brief 檢索至writeBuffer指定數量字節，並由此緩衝區刪除
   *
   * @param writeBuffer 輸出緩衝區
   * @param length 指定最大輸出字節數量
   * @param peek true 啟用窺視，僅讀取不刪除
   * @return int 檢索的位元組數量
   */
  virtual int poll(mframe::io::WriteBuffer& writeBuffer, int length, bool peek) abstract;

  /**
   * @brief 檢索至buffer指定數量字節，並由此緩衝區刪除
   *
   * @param buffer 輸出緩衝區
   * @param bufferSize 緩衝區大小
   * @param peek true 啟用窺視，僅讀取不刪除
   * @return int 檢索的位元組數量
   */
  virtual int poll(void* buffer, int bufferSize, bool peek) abstract;

  /**
   * @brief 跳躍數個緩衝區內位元組
   *
   * @param value 期望跳躍數量
   * @return int 實際跳躍數量
   */
  virtual int skip(int value) abstract;
};

/* ******************************************************************************
 * End of file
 */

#endif /* MFRAME_739FA0D6_740F_4CA0_975C_FD713D983D41 */
