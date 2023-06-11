/**
 * Copyright (c) 2020 ZxyKira
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef MFRAME_70D3F441_6A18_4924_BBD9_227663933296
#define MFRAME_70D3F441_6A18_4924_BBD9_227663933296

/* ******************************************************************************
 * Include
 */

//-------------------------------------------------------------------------------
#include "./../io/CompletionHandler.h"
#include "./../io/ReadBuffer.h"
#include "./../lang/Runnable.h"
#include "./../util/Future.h"

/* ******************************************************************************
 * Namespace
 */
namespace mframe::io {
  class OutputStream;
}  // namespace mframe::io

/* ******************************************************************************
 * Class/Interface/Struct/Enum
 */

/**
 * @brief 輸出串流 <Protected Class>
 *
 * 此類別無法被直接建構，須被繼承後並實現字節從緩衝區輸出至裝置。
 *
 */
class mframe::io::OutputStream : public mframe::lang::Object,
                                 public mframe::lang::Runnable {
  /* ****************************************************************************
   * Variable <Public>
   */

  /* ****************************************************************************
   * Variable <Protected>
   */
 protected:
  mframe::io::ReadBuffer* mReadBuffer;
  mframe::io::CompletionHandler<int, void*>* mCompletionHandler;
  void* mAttachment;
  int mResult;
  bool mHandling;

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
 protected:
  /**
   * @brief Construct a new Output Stream object
   *
   */
  OutputStream(void);

 public:
  /**
   * @brief Destroy the Output Stream object
   *
   */
  virtual ~OutputStream(void) override;

  /* ****************************************************************************
   * Operator Method
   */

  /* ****************************************************************************
   * Public Method <Static>
   */

  /* ****************************************************************************
   * Public Method <Override> - mframe::lang::Runnable
   */
 public:
  virtual void run(void) override;

  /* ****************************************************************************
   * Public Method
   */
 public:
  /**
   * @brief 取消當前的輸出串流寫入
   *
   * @return
   *  - true : 為成功終止當前的輸出至OutputStream
   *  - false : 終止失敗，有可能當前輸出串流並未忙碌
   */
  bool abortWrite(void);

  /**
   * @brief 取得輸出串流是否為寫入忙碌
   *
   * @return
   *  - true: 輸出串流忙碌中，無法接受新的寫入
   *  - false: 輸出串流閒置中
   */
  bool writeBusy(void);

  /**
   * @brief IO 寫入模式
   *
   * @param readBuffer
   * @param timeout
   * @return
   *  - true: 建立寫入成功
   *  - false: 建立寫入失敗，串流可能正在忙碌中
   */
  bool write(mframe::io::ReadBuffer& readBuffer, int timeout);

  /**
   * @brief NIO 寫入模式
   *
   * 從給定的緩衝區向該通道寫入一個字節序列。
   * 該方法啟動異步寫入操作，以從給定的緩衝區向該通道寫入字節序列。
   *
   * 該方法的行為方式與 write(ReadBuffer,void*,CompletionHandler)方法完全相同，不同的是，
   * 該方法不是指定完成處理程序，
   * 而是返回一個Future待處理結果的Future。Future的get方法返回寫入的字節數。
   *
   *
   * @param readBuffer - 要檢索字節的緩衝區
   * @param future - 代表操作結果的未來
   *
   * @return
   *  - true : 建立寫入成功
   *  - false : 建立寫入失敗，串流可能正在忙碌中
   */
  bool write(mframe::io::ReadBuffer& readBuffer, mframe::util::Future& future);

  /* ****************************************************************************
   * Public Method <Virtual>
   */
 public:
  /**
   * @brief AIO 寫入模式
   *
   * @param readBuffer
   * @param attachment
   * @param handler
   * @return
   *  - true : 建立寫入成功
   *  - false : 建立寫入失敗，串流可能正在忙碌中
   */
  virtual bool write(mframe::io::ReadBuffer& readBuffer,
                     void* attachment,
                     mframe::io::CompletionHandler<int, void*>* handler);

  /* ****************************************************************************
   * Protected Method <Static>
   */

  /* ****************************************************************************
   * Protected Method <Override>
   */

  /* ****************************************************************************
   * Protected Method
   */
 protected:
  /**
   * @brief
   *
   */
  virtual void execute(void);

  /**
   * @brief
   *
   */
  virtual void onWriteEvent(void);
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

#endif /* MFRAME_70D3F441_6A18_4924_BBD9_227663933296 */
