[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1306

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1306/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

SSD1306 ist ein Single-Chip-CMOS-OLED/PLED-Treiber mit Controller für organische/polymere Leuchtdioden-Punktmatrix-Grafikanzeigesysteme. Es besteht aus 128 Segmenten und 64 Commons. Dieser IC ist für OLED-Panels vom Typ Common Cathode ausgelegt. Der SSD1306 enthält Kontraststeuerung, Anzeige-RAM und Oszillator, wodurch die Anzahl externer Komponenten und der Stromverbrauch reduziert werden. Es verfügt über eine 256-stufige Helligkeitsregelung. Daten/Befehle werden von der allgemeinen MCU über die Hardware-wählbare, mit der 6800/8000-Serie kompatible parallele Schnittstelle, I2C-Schnittstelle oder serielle Peripherieschnittstelle gesendet. Es eignet sich für viele kompakte tragbare Anwendungen, wie z. B. Handy-Sub-Display, MP3-Player und Taschenrechner usw.

LibDriver SSD1306 ist der voll funktionsfähige Treiber von SSD1306, der von LibDriver gestartet wurde. Er bietet die Funktionen zum Zeichnen von Einzelpunkten, Füllen von Blöcken, Bildanzeige usw. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example advance](#example-advance)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver SSD1306-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver SSD1306 IIC,SPI.

/test enthält den Testcode des LibDriver SSD1306-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver SSD1306-Beispielcode.

/doc enthält das LibDriver SSD1306-Offlinedokument.

/Datenblatt enthält SSD1306-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC,SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC,SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

Das Bildextraktionsformat ist wie folgt und jedes Pixel wird in einem Byte gespeichert

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ssd1306/index.html](https://www.libdriver.com/docs/ssd1306/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.