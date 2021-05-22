<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver SSD1306

[English](/README.md) | [ 简体中文](/README_CH.md)

SSD1306是一个单芯片CMOS OLED/PLED驱动器，带有用于有机/聚合物发光的控制器二极管点阵图形显示系统。它由128个段和64个公共区组成。这个IC是为普通阴极型OLED面板设计。SSD1306内置对比度控制、显示RAM和振荡器，减少了外部组件和功耗。它有256阶亮度控制。数据/命令通过硬件可选的6800/8000系列兼容并行接口从通用MCU发送，I2C接口或串行外围接口。它适用于许多小型便携式应用，如手机分屏、MP3播放器、计算器等。

LibDriver SSD1306是LibDriver推出的SSD1306的全功能驱动，该驱动提供绘制单点，填充块，图片显示等功能。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver SSD1306的源文件。

/interface目录包含了LibDriver SSD1306与平台无关的IIC、SPI总线模板。

/test目录包含了LibDriver SSD1306驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver SSD1306编程范例。

/doc目录包含了LibDriver SSD1306离线文档。

/datasheet目录包含了SSD1306数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

### 安装

参考/interface目录下与平台无关的IIC、SPI总线模板，完成指定平台的IIC、SPI总线驱动。

将/src目录，/interface目录和/example目录加入工程。

### 使用

#### example basic

```C
uint8_t res;

res = ssd1306_basic_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);
if (res)
{
    ssd1306_basic_deinit();

    return 1;
}

...

res = ssd1306_basic_clear();
if (res)
{
    ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
    ssd1306_basic_deinit();

    return 1;
}
res = ssd1306_basic_string(0, 0, "123", 3, 1, SSD1306_FONT_16);
if (res)
{
    ssd1306_interface_debug_print("ssd1306: show string failed.\n");
    ssd1306_basic_deinit();

    return 1;
}

...

res = ssd1306_basic_rect(0, 31, 31, 31, 1);
if (res)
{
    ssd1306_basic_deinit();

    return 1;
}    

...

ssd1306_basic_deinit();

return 0;
```

#### example advance

```C
uint8_t res;

res = ssd1306_advance_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);
if (res)
{
    ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_clear();
if (res)
{
    ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
    ssd1306_advance_deinit();

    return 1;
}
res = ssd1306_advance_string(0, 0, "123", 3, 1, SSD1306_FONT_16);
if (res)
{
    ssd1306_interface_debug_print("ssd1306: show string failed.\n");
    ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_write_point(38, 38, 1);
if (res)
{
    ssd1306_basic_deinit();

    return 1;
}

...

res = ssd1306_advance_rect(0, 31, 31, 31, 1);
if (res)
{
    ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_fade_blinking(SSD1306_FADE_BLINKING_MODE_BLINKING, 0);
if (res)
{
    ssd1306_advance_deinit();

    return 1;
}

...

res = ssd1306_advance_vertical_left_horizontal_scroll(0, 7, 0, SSD1306_SCROLL_FRAME_2);
if (res)
{
    ssd1306_basic_deinit();

    return 1;
}

...

ssd1306_advance_deinit();

return 0;
```

### 文档

在线文档: https://www.libdriver.com/docs/ssd1306/index.html

离线文档: /doc/html/index.html

### 贡献

请联系lishifenging@outlook.com

### 版权

版权(C) LibDriver 2015-2021 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com