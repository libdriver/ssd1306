[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1306

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1306/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SSD1306 is a single-chip CMOS OLED/PLED driver with controller for organic / polymer light emitting diode dot-matrix graphic display system. It consists of 128 segments and 64 commons. This IC is designed for Common Cathode type OLED panel.The SSD1306 embeds with contrast control, display RAM and oscillator, which reduces the number of external components and power consumption. It has 256-step brightness control. Data/Commands are sent from general MCU through the hardware selectable 6800/8000 series compatible Parallel Interface, I2C interface or Serial Peripheral Interface. It is suitable for many compact portable applications, such as mobile phone sub-display, MP3 player and calculator, etc.

LibDriver SSD1306 is the full function driver of SSD1306 launched by LibDriver.It provides the functions of drawing single point, filling block, image display, etc. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver SSD1306 source files.

/interface includes LibDriver SSD1306 IIC, SPI platform independent template.

/test includes LibDriver SSD1306 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver SSD1306 sample code.

/doc includes LibDriver SSD1306 offline document.

/datasheet includes SSD1306 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC, SPI platform independent template and finish your platform IIC, SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

The image extraction format is as follows and every pixel stored in one byte.

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

### Document

Online documents: [https://www.libdriver.com/docs/ssd1306/index.html](https://www.libdriver.com/docs/ssd1306/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.