/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name : [RZ/A2M] 2D barcode Sample Project
* File Name   : readme-j.txt
*******************************************************************************/
/*******************************************************************************
*
* History     : Jun. 30,2020 Rev.1.00.00    新規作成
*             : Sep. 30,2020 Rev.1.01.00    e2 studio 2020-07用に更新
*             : Apr. 20,2021 Rev.1.02.00    e2 studio 2021-04用に更新
*******************************************************************************/

1. はじめに

  本サンプルコードは、RZ/A2Mグループ R7S921053VCBGを搭載した
  RZ/A2M CPUボード(RTK7921053C00000BE)およびSUBボード(RTK79210XXB00000BE)を
  使用して動作確認しています。
  お客様のソフトウエア開発時に技術参考資料としてご利用ください。

  ****************************** ご 注 意 ******************************
   本サンプルコードはすべて参考資料であり、その動作を保証するもの
   ではありません。実際のシステムに組み込む場合はシステム全体で
   十分に評価し、お客様の責任において適用可否を判断してください。
  ****************************** ご 注 意 ******************************


2. 動作確認環境

  サンプルコードは以下の環境で動作を確認しています。

    CPU          : RZ/A2M
    ボード       : RZ/A2M CPUボード(RTK7921053C00000BE)
                   RZ/A2M SUBボード(RTK79210XXB00000BE)
                   Display Output Board (RTK79210XXB00010BE)
    コンパイラ   : GNU Arm Embedded Toolchain 6-2017-q2-update
    統合開発環境 : e2 studio 2021-04
    エミュレータ : SEGGER社J-Link Base
                   (RZ/A2Mに対応したJ-Link製品を準備してください。)
    カメラ       : Raspberry Pi Camera V2
    モニタ       : Full-WXGA(1366*768)を表示可能なモニタ


3. サンプルコードの内容

    このサンプルプログラムは動的再構成可能プロセッサ（DRP）を使用して2Dバーコードをデコードします。
    オープンソースのプロジェクトZXingは、2Dバーコードをデコードするためのアルゴリズムとしてこのプログラムで使用されます。

    アプリケーションプログラムは、ローダプログラムによりSPIマルチI/Oバスコントローラ(SPIBSC)と
    シリアルフラッシュメモリのレジスタ設定処理をを行った後に、ローダプログラムから実行されます。
    ローダプログラムは、以下のフォルダに格納しています。
      [プロジェクト名\bootloader\rza2_qspi_flash_ddr_bootloader.elf]

    このローダプログラムは、Macronix社のMX25L51245Gの仕様に合わせています。他のシリアルフラッシュメモリを
    使用する場合は、フラッシュメモリの仕様に合わせて「RZ/A2Mグループ シリアルフラッシュメモリからのブート例」
    アプリケーションノートに付属のローダプログラムのプロジェクト[rza2m_sflash_boot_loader_gcc]のソースコードを変更し、
    ロードモジュールを生成してください。生成されたロードモジュールのファイル名を"rza2_qspi_flash_ddr_bootloader.elf"に
    変更してご使用ください。

  サンプルコードの詳細内容については、アプリケーションノートを参照してください。


4. サンプルコードの動作確認条件

  (1) ブートモード
    - ブートモード3
      (シリアルフラッシュメモリ3.3Vからブート)
      ※上記以外のブートモードを設定した場合、プログラムは動作しません。

  (2) 動作周波数
    RZ/A2M CPUボード上のRZ/A2Mの各クロックが以下の周波数となるように、
    RZ/A2Mのクロックパルス発振器を設定しています。
    (RZ/A2Mのクロックモード1で、EXTAL端子に24MHzのクロックが
    入力されている状態での周波数です。)
      - CPUクロック(Iφ)     : 528MHz
      - 画像処理(Gφ)        : 264MHz
      - 内部バスクロック(Bφ): 132MHz
      - 周辺クロック1(P1φ)  :  66MHz
      - 周辺クロック0(P0φ)  :  33MHz
      - QSPI0_SPCLK          :  66MHz
      - CKIO                 : 132MHz

  (3) 使用するシリアルフラッシュメモリ
    - メーカ  : Macronix社
    - 型名    : MX25L51245G

  (4) キャッシュの設定
    L1およびL2キャッシュの初期設定をMMUを設定することにより行っています。
    L1キャッシュおよびL2キャッシュの有効または無効の領域については、
    RZ/A2M初期設定例のアプリケーションノートの「MMUの設定」を参照してください。


5. サンプルコードの動作手順

  本サンプルコードを動作させる場合は、以下の手順に従ってください。

  (1) ディップスイッチおよびジャンパの設定
     CPUボードのディップスイッチおよびジャンパを以下のとおりに設定します。

     <<CPUボードの設定>>
      - SW1-1  : ON  (SSCG動作 OFF)
        SW1-2  : OFF (クロックモード1(EXTAL入力の入力周波数を20～24MHzに設定))
        SW1-3  : ON  (MD_BOOT2 = L)
        SW1-4  : OFF (MD_BOOT1 = H)
        SW1-5  : OFF (MD_BOOT0 = H)
        SW1-6  : ON  (BSCANP 通常動作(CoreSightデバッグモード))
        SW1-7  : ON  (CLKTEST OFF)
        SW1-8  : ON  (TESTMD OFF)
      - JP3 :   Open (USB ch0をファンクションモードで使用する(VBUS0電源を供給しない))

     SUBボードのディップスイッチおよびジャンパを以下のとおりに設定します。

     <<SUBボードの設定>>
      - SW6-1  : OFF (P9_[7:0]、P8_[7:1]、P2_2、P2_0、P1_3、P1_[1:0]、P0_[6:0]、P6_7、P6_5、P7_[1:0]、P7[5:3]を
                       DRP、オーディオ、UART、CANおよびUSBインタフェース端子として使用)
        SW6-2  : OFF (P8_4、P8_[7:6]、P6_4、P9_[6:3]をオーディオインタフェース端子として使用)
        SW6-3  : OFF (P9_[1:0]、P1_0、P7_5をUARTおよびUSBインタフェース端子として使用)
        SW6-4  : OFF (P6_[3:1]、PE_[6:0]をCEU端子として使用)
        SW6-5  : OFF (P3_[5:1]、PH_5、PK_[4:0]をFLCTL端子として使用)
        SW6-6  : ON  (PJ_[7:6]をVDC6端子として使用)
        SW6-7  : ON  (PA_[7:4]をVDC6端子として使用)
        SW6-8  : OFF (NC)
        SW6-9  : OFF (汎用入力ポートP5_3 = "H")
        SW6-10 : OFF (汎用入力ポートPC_2 = "H")

      - JP1 : 2-JP2  (PJ_1をIRQ0スイッチ(SW3)の割り込み端子として使用)

      ディップスイッチおよびジャンパ設定の詳細は、CPUボードおよび
      SUBボードのユーザーズマニュアルを参照してください。

  サンプルコードのビルド、ダウンロード、実行はQuick Start Guide(R01QS0027)を参照ください。


以上

