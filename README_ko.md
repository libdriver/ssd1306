[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1306

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1306/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SSD1306은 유기/폴리머 발광 다이오드 도트 매트릭스 그래픽 디스플레이 시스템용 컨트롤러가 있는 단일 칩 CMOS OLED/PLED 드라이버입니다. 128개의 세그먼트와 64개의 커먼으로 구성됩니다. 이 IC는 Common Cathode 유형 OLED 패널용으로 설계되었습니다. SSD1306에는 대비 제어, 디스플레이 RAM 및 발진기가 내장되어 있어 외부 부품 수와 전력 소비를 줄입니다. 256단계 밝기 조절이 가능합니다. 데이터/명령은 하드웨어 선택 가능한 6800/8000 시리즈 호환 병렬 인터페이스, I2C 인터페이스 또는 직렬 주변 장치 인터페이스를 통해 일반 MCU에서 전송됩니다. 휴대 전화 서브 디스플레이, MP3 플레이어 및 계산기 등과 같은 많은 소형 휴대용 응용 프로그램에 적합합니다.

LibDriver SSD1306은 LibDriver에서 출시한 SSD1306의 전체 기능 드라이버입니다. 단일 포인트 그리기, 블록 채우기, 이미지 표시 등의 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver SSD1306의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver SSD1306용 플랫폼 독립적인 IIC,SPI버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver SSD1306드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver SSD1306프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver SSD1306오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 SSD1306데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC,SPI버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC,SPI버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

이미지 추출 형식은 다음과 같으며 모든 픽셀은 1바이트에 저장됩니다.

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
</div>

```c
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

### 문서

온라인 문서: [https://www.libdriver.com/docs/ssd1306/index.html](https://www.libdriver.com/docs/ssd1306/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.