### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

GPIO Pin: RESET/CMD_DATA GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./ssd1306_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ssd1306 REQUIRED)
```

### 3. SSD1306

#### 3.1 Command Instruction

1. Show ssd1306 chip and driver information.

   ```shell
   ssd1306 (-i | --information)
   ```

2. Show ssd1306 help.

   ```shell
   ssd1306 (-h | --help)
   ```

3. Show ssd1306 pin connections of the current board.

   ```shell
   ssd1306 (-p | --port)
   ```

4. Run ssd1306 display test. 

   ```shell
   ssd1306 (-t display | --test=display) [--addr=<0 | 1>] [--interface=<iic | spi>]
   ```

5. Run ssd1306 init function.

   ```shell
   ssd1306 (-e basic-init | --example=basic-init) [--addr=<0 | 1>] [--interface=<iic | spi>]
   ```

6. Run ssd1306 deinit function.

   ```shell
   ssd1306 (-e basic-deinit | --example=basic-deinit)
   ```

7. Run ssd1306 show string function, string is the shown string. 

   ```shell
   ssd1306 (-e basic-str | --example=basic-str) [--str=<string>]
   ```

8. Run ssd1306 display on function.

   ```shell
   ssd1306 (-e basic-display-on | --example=basic-display-on)
   ```

9. Run ssd1306 display off function.

   ```shell
   ssd1306 (-e basic-display-off | --example=basic-display-off)
   ```

10. Run ssd1306 clear screen function.

    ```shell
    ssd1306 (-e basic-clear | --example=basic-clear)
    ```

11. Run ssd1306 writepoint function, x0 is the x of the point and y0 is the y of the point.

    ```shell
    ssd1306 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
    ```

12. Run ssd1306 readpoint function, x0 is the x of the point and y0 is the y of the point.

    ```shell
    ssd1306 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0>
    ```

13. Run ssd1306 drawing rectangle function, x1 is the top left x of the rect, y1 is the top left y of the rect, x2 is the bottom right x of the rect and y2 is the bottom right y of the rect.

    ```shell
    ssd1306 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
    ```

14. Run ssd1306 init function. 

    ```shell
    ssd1306 (-e advance-init | --example=advance-init) [--addr=<0 | 1>] [--interface=<iic | spi>]
    ```

15. Run ssd1306 deinit function.

    ```shell
    ssd1306 (-e advance-deinit | --example=advance-deinit)
    ```

16. Run ssd1306 show string function, string is the shown string.

    ```shell
    ssd1306 (-e advance-str | --example=advance-str) [--str=<string>]
    ```

17. Run ssd1306 display on function. 

    ```shell
    ssd1306 (-e advance-display-on | --example=advance-display-on)
    ```

18. Run ssd1306 display off function.

    ```shell
    ssd1306 (-e advance-display-off | --example=advance-display-off)
    ```

19. Run ssd1306 clear screen function. 

    ```shell
    ssd1306 (-e advance-clear | --example=advance-clear)
    ```

20. Run ssd1306 writepoint function, x0 is the x of the point and y0 is the y of the point.

    ```shell
    ssd1306 (-e advance-point | --example=advance-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
    ```

21. Run ssd1306 readpoint function, x0 is the x of the point and y0 is the y of the point.

    ```shell
    ssd1306 (-e advance-point | --example=advance-point) --x0=<x0> --y0=<y0>
    ```

22. Run ssd1306 drawing rectangle function, x1 is the top left x of the rect, y1 is the top left y of the rect, x2 is the bottom right x of the rect and y2 is the bottom right y of the rect.

    ```shell
    ssd1306 (-e advance-rect | --example=advance-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
    ```

23. Run ssd1306 enable zoom function.

    ```shell
    ssd1306 (-e advance-enable-zoom | --example=advance-enable-zoom)
    ```

24. Run ssd1306 disable zoom function.

    ```shell
    ssd1306 (-e advance-disable-zoom | --example=advance-disable-zoom)
    ```

25. Run ssd1306 deactivate scroll function.

    ```shell
    ssd1306 (-e advance-deactivate-scroll | --example=advance-deactivate-scroll)
    ```

26. Run ssd1306 fade blinking function, f means the running frames.  

    ```shell
    ssd1306 (-e advance-fade-blinking | --example=advance-fade-blinking) [--mode=<DISABLE | FADE-OUT | BLINKING>] [--frames=<f>]
    ```

27. Run ssd1306 setting vertical left horizontal scroll function, spage means start page and it can be "0"-"7", epage means end page and it can be "0"-"7", r means display rows and it can be "0" - "63".

    ```shell
    ssd1306 (-e advance-left-scroll | --example=advance-left-scroll) [--start=<spage>] [--stop=<epage>] [--row=<r>] [--frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>]
    ```

28. Run ssd1306 setting vertical right horizontal scroll function, spage means start page and it can be "0"-"7", epage means end page and it can be "0"-"7", r means display rows and it can be "0" - "63".

    ```shell
    ssd1306 (-e advance-right-scroll | --example=advance-right-scroll) [--start=<spage>] [--stop=<epage>] [--row=<r>] [--frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>]
    ```

#### 3.2 How to run

```shell
# open one terminal and run the server
./ssd1306_server 
```
```shell
# open another terminal and sent the command
./ssd1306 xxx xxx xxx ...
```

#### 3.3 Command Example

```shell
./ssd1306 -i

ssd1306: chip is Solomon Systech SSD1306.
ssd1306: manufacturer is Solomon Systech.
ssd1306: interface is IIC SPI.
ssd1306: driver version is 2.0.
ssd1306: min supply voltage is 1.6V.
ssd1306: max supply voltage is 3.3V.
ssd1306: max current is 0.78mA.
ssd1306: max temperature is 85.0C.
ssd1306: min temperature is -40.0C.
```

```shell
./ssd1306 -p

ssd1306: SPI interface SCK connected to GPIO11(BCM).
ssd1306: SPI interface MISO connected to GPIO9(BCM).
ssd1306: SPI interface MOSI connected to GPIO10(BCM).
ssd1306: SPI interface CS connected to GPIO8(BCM).
ssd1306: SPI interface cmd data gpio GPIO connected to GPIO17(BCM).
ssd1306: SPI interface reset GPIO connected to GPIO27(BCM).
ssd1306: IIC interface SCL connected to GPIO3(BCM).
ssd1306: IIC interface SDA connected to GPIO2(BCM).
```

```shell
./ssd1306 -t display --addr=0 --interface=iic

ssd1306: chip is Solomon Systech SSD1306.
ssd1306: manufacturer is Solomon Systech.
ssd1306: interface is IIC SPI.
ssd1306: driver version is 2.0.
ssd1306: min supply voltage is 1.6V.
ssd1306: max supply voltage is 3.3V.
ssd1306: max current is 0.78mA.
ssd1306: max temperature is 85.0C.
ssd1306: min temperature is -40.0C.
ssd1306: start display test.
ssd1306: font 12 test.
ssd1306: font 16 test.
ssd1306: font 24 test.
ssd1306: rectangle test.
ssd1306: rand point test.
ssd1306: picture test.
ssd1306: graphic acceleration test.
ssd1306: right horizontal scroll.
ssd1306: left horizontal scroll.
ssd1306: vertical right horizontal scroll.
ssd1306: vertical left horizontal scroll.
ssd1306: advance graphic test.
ssd1306: zoom in.
ssd1306: fade mode.
ssd1306: finish display test.
```

```shell
./ssd1306 -e basic-str --str=12345abcdEFGH

ssd1306: 12345abcdEFGH.
```

```shell
./ssd1306 -e basic-init --addr=0 --interface=iic

ssd1306: init success.
```

```shell
./ssd1306 -e basic-display-off

ssd1306: display off.
```

```shell
./ssd1306 -e basic-display-on

ssd1306: display on.
```

```shell
./ssd1306 -e basic-clear

ssd1306: clear screen.
```

```shell
./ssd1306 -e basic-deinit

ssd1306: deinit ssd1306.
```

```shell
./ssd1306 -e basic-point --x0=16 --y0=16 --color=1

ssd1306: write point 16 16 1.
```

```shell
./ssd1306 -e basic-point --x0=16 --y0=16

ssd1306: read point 16 16 is 1.
```

```shell
./ssd1306 -e basic-rect --x1=0 --y1=0 --x2=32 --y2=32 --color=1

ssd1306: draw rect 0 0 32 32.
```

```shell
./ssd1306 -e advance-init --addr=0 --interface=iic

ssd1306: init success.
```

```shell
./ssd1306 -e advance-str --str=12345abcdEFGH

ssd1306: 12345abcdEFGH.
```

```shell
./ssd1306 -e advance-display-off

ssd1306: display off.
```

```shell
./ssd1306 -e advance-display-on

ssd1306: display on.
```

```shell
./ssd1306 -e advance-clear

ssd1306: clear screen.
```

```shell
./ssd1306 -e advance-point --x0=16 --y0=16 --color=1

ssd1306: write point 16 16 1.
```

```shell
./ssd1306 -e advance-point --x0=16 --y0=16

ssd1306: read point 16 16 is 1.
```

```shell
./ssd1306 -e advance-rect --x1=0 --y1=0 --x2=32 --y2=32 --color=1

ssd1306: draw rect 0 0 32 32.
```

```shell
./ssd1306 -e advance-deinit

ssd1306: deinit ssd1306.
```

```shell
./ssd1306 -e advance-enable-zoom

ssd1306: enable zoom in.
```

```shell
./ssd1306 -e advance-disable-zoom

ssd1306: disable zoom in.
```

```shell
./ssd1306 -e advance-fade-blinking --mode=BLINKING --frames=0

ssd1306: set fade blinking blinking mode with 0 frames.
```

```shell
./ssd1306 -e advance-deactivate-scroll

ssd1306: deactivate scroll.
```

```shell
./ssd1306 -e advance-left-scroll --start=0 --stop=7 --row=0 --frame=FRAME_2

ssd1306: vertical left horizontal scroll start stop rows frames 0 7 0.
```

```shell
./ssd1306 -e advance-right-scroll --start=0 --stop=7 --row=0 --frame=FRAME_2

ssd1306: vertical right horizontal scroll start stop rows frames 0 7 0.
```

```shell
./ssd1306 -h

Usage:
  ssd1306 (-i | --information)
  ssd1306 (-h | --help)
  ssd1306 (-p | --port)
  ssd1306 (-t display | --test=display) [--addr=<0 | 1>] [--interface=<iic | spi>]
  ssd1306 (-e basic-init | --example=basic-init) [--addr=<0 | 1>] [--interface=<iic | spi>]
  ssd1306 (-e basic-deinit | --example=basic-deinit)
  ssd1306 (-e basic-str | --example=basic-str) [--str=<string>]
  ssd1306 (-e basic-display-on | --example=basic-display-on)
  ssd1306 (-e basic-display-off | --example=basic-display-off)
  ssd1306 (-e basic-clear | --example=basic-clear)
  ssd1306 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
  ssd1306 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
  ssd1306 (-e advance-init | --example=advance-init) [--addr=<0 | 1>] [--interface=<iic | spi>]
  ssd1306 (-e advance-deinit | --example=advance-deinit)
  ssd1306 (-e advance-str | --example=advance-str) [--str=<string>]
  ssd1306 (-e advance-display-on | --example=advance-display-on)
  ssd1306 (-e advance-display-off | --example=advance-display-off)
  ssd1306 (-e advance-clear | --example=advance-clear)
  ssd1306 (-e advance-point | --example=advance-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]
  ssd1306 (-e advance-rect | --example=advance-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]
  ssd1306 (-e advance-enable-zoom | --example=advance-enable-zoom)
  ssd1306 (-e advance-disable-zoom | --example=advance-disable-zoom)
  ssd1306 (-e advance-deactivate-scroll | --example=advance-deactivate-scroll)
  ssd1306 (-e advance-fade-blinking | --example=advance-fade-blinking) [--mode=<DISABLE | FADE-OUT | BLINKING>]
          [--frames=<f>]
  ssd1306 (-e advance-left-scroll | --example=advance-left-scroll) [--start=<spage>] [--stop=<epage>] [--row=<r>]
          [--frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>]
  ssd1306 (-e advance-right-scroll | --example=advance-right-scroll) [--start=<spage>] [--stop=<epage>] [--row=<r>]
          [--frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>]

Options:
      --addr=<0 | 1>      Set the iic addr pin.([default: 0])
      --color=<0 | 1>     Set the chip color.([default: 1])
  -e <basic-init | basic-deinit | basic-str | basic-display-on | basic-display-off | basic-clear 
     | basic-point | basic-rect>, --example=<advance-init | advance-deinit | advance-str | advance-display-on
     | advance-display-off | advance-clear | advance-point | advance-rect | advance-enable-zoom | advance-disable-zoom
     | advance-fade-blinking | advance-left-scroll | advance-right-scroll | advance-deactivate-scroll>
                          Run the driver example.
      --frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>
                          Set the scrolling frame.([default: FRAME_2])
      --frames=<f>        Se the fade-blinking frames.([default: 0])
  -h, --help              Show the help.
  -i, --information       Show the chip information.
      --interface=<iic | spi>
                          Set the chip interface.([default: iic])
      --mode=<DISABLE | FADE-OUT | BLINKING>
                          Set the fade-blinking mode.([default: DISABLE])
  -p, --port              Display the pin connections of the current board.
      --row=<r>           Set the scrolling row.([default: 0])
      --start=<spage>     Set the scrolling start page.([default: 0])
      --stop=<epage>      Set the scrolling stop page.([default: 7])
      --str=<string>      Set the display string.([default: libdriver])
  -t <display>, --test=<display>
                          Run the driver test.
      --x0=<x0>           Set the x0 and it is the x of the point.
      --x1=<x1>           Set the x1 and it is the top left x of the rect.
      --x2=<x2>           Set the x2 and it is the bottom right x of the rect.
      --y0=<y0>           Set the y0 and it is the y of the point.
      --y1=<y1>           Set the y1 and it is the top left y of the rect.
      --y2=<y2>           Set the y2 and it is the bottom right y of the rect.
```

