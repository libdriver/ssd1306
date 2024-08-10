[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1306

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1306/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SSD1306是一個單晶片CMOS OLED/PLED驅動器，帶有用於有機/聚合物發光的控制器二極體點陣圖形顯示系統。 它由128個段和64個公共區組成。 這個IC是為普通陰極型OLED面板設計。 SSD1306內寘對比度控制、顯示RAM和振盪器，减少了外部組件和功耗。 它有256階亮度控制。 數據/命令通過硬體可選的6800/8000平行介面、I2C介面或串列週邊介面發送。 它適用於許多小型可擕式應用，如手機分屏、MP3播放機、小算盘等。

LibDriver SSD1306是LibDriver推出的SSD1306的全功能驅動，該驅動提供繪製單點，填充塊，圖片顯示等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver SSD1306的源文件。

/interface目錄包含了LibDriver SSD1306與平台無關的IIC、SPI總線模板。

/test目錄包含了LibDriver SSD1306驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver SSD1306編程範例。

/doc目錄包含了LibDriver SSD1306離線文檔。

/datasheet目錄包含了SSD1306數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC、SPI總線模板，完成指定平台的IIC、SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

#### example basic

```C
#include "driver_ssd1306_basic.h"

uint8_t res;

res = ssd1306_basic_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);
if (res != 0)
{
    return 1;
}

...

res = ssd1306_basic_clear();
if (res != 0)
{
    ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
    (void)ssd1306_basic_deinit();

    return 1;
}
res = ssd1306_basic_string(0, 0, "123", 3, 1, SSD1306_FONT_16);
if (res != 0)
{
    ssd1306_interface_debug_print("ssd1306: show string failed.\n");
    (void)ssd1306_basic_deinit();

    return 1;
}

...

res = ssd1306_basic_rect(0, 31, 31, 31, 1);
if (res != 0)
{
    (void)ssd1306_basic_deinit();

    return 1;
}    

...

(void)ssd1306_basic_deinit();

return 0;
```

#### example advance

圖像提取格式如下，每個像素使用1個字節存儲。

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
</div>

```C
#include "driver_ssd1306_advance.h"

uint8_t res;
uint8_t image[8192];

res = ssd1306_advance_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);
if (res != 0)
{
    return 1;
}

...

res = ssd1306_advance_clear();
if (res != 0)
{
    ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
    (void)ssd1306_advance_deinit();

    return 1;
}
res = ssd1306_advance_string(0, 0, "123", 3, 1, SSD1306_FONT_16);
if (res != 0)
{
    ssd1306_interface_debug_print("ssd1306: show string failed.\n");
    (void)ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_write_point(38, 38, 1);
if (res != 0)
{
    (void)ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_rect(0, 31, 31, 31, 1);
if (res != 0)
{
    (void)ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_fade_blinking(SSD1306_FADE_BLINKING_MODE_BLINKING, 0);
if (res != 0)
{
    (void)ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_vertical_left_horizontal_scroll(0, 7, 0, SSD1306_SCROLL_FRAME_2);
if (res != 0)
{
    (void)ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_picture(0, 0, 0, 0, image);
if (res != 0)
{
    (void)ssd1306_advance_deinit();

    return 1;
}

...

(void)ssd1306_advance_deinit();

return 0;
```

### 文檔

在線文檔: [https://www.libdriver.com/docs/ssd1306/index.html](https://www.libdriver.com/docs/ssd1306/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。