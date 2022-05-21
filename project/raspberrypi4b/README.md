### 1. chip

#### 1.1 chip info

chip name : Raspberry Pi 4B

iic pin: SCL/SDA GPIO3/GPIO2

spi pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8

gpio pin: RESET/CMD_DATA GPIO27/GPIO17

### 2. install

#### 2.1 install info

```shell
sudo apt-get install libgpiod-dev

make
```

#### 2.2 run server

```shell
./ssd1306_server 
```

### 3. ssd1306

#### 3.1 command Instruction

​          ssd1306 is a basic command which can test all ssd1306 driver function:

​           -i        show ssd1306 chip and driver information.

​           -h       show ssd1306 help.

​           -p       show ssd1306 pin connections of the current board.

​           -t display (-spi | -iic  -a (0 | 1))

​           -t display -spi        run ssd1306 display test by spi interface. 

​           -t display -iic -a (0 | 1)        run ssd1306 display test by iic interface. 0 or 1 means the iic address pin level.

​           -c (basic (-spi -init | -iic -a (0 | 1) | -deinit | -str <string> | -displayon | -displayoff | -clear | -writepoint <x> <y> <data> | -readpoint <x> <y> | -rect <x1> <y1> <x2> <y2>) | advance (-spi -init | -iic -a (0 | 1) | -deinit | -str <string> | -displayon | -displayoff | -clear | -writepoint <x> <y> <data> | -readpoint <x> <y> | -rect <x1> <y1> <x2> <y2> | -enable_zoom | -disable_zoom |  -deactivate_scroll | advance -fade_blinking (disable | fade_out | blinking) <frame> | -vertical_left_horizontal_scroll  <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 
 FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256) |  -vertical_right_horizontal_scroll <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 |  FRAME_4 | FRAME_5 | FRAME_25 |FRAME_64 | FRAME_128 | FRAME_256) )

​            -c basic -spi -init        run ssd1306 init by spi interface. 

​            -c basic -iic -a (0 | 1)        run ssd1306 init by iic interface. 0 or 1 means the iic address pin level.

​            -c basic -deinit        run ssd1306 deinit function. 

​            -c basic -str <string>        run ssd1306 show string function. string is the shown string. 

​            -c basic -displayon        run ssd1306 display on function. 

​            -c basic -displayoff        run ssd1306 display off function. 

​            -c basic -clear        run ssd1306 clear screen function. 

​            -c basic -writepoint <x> <y> <data>        run ssd1306 writepoint function. 

​            -c basic -readpoint <x> <y>        run ssd1306 readpoint function.

​            -c basic -rect <x1> <y1> <x2> <y2>        run ssd1306 drawing rectangle function. x1 means x start. y1 means y start. x2 means x end. y2 means y end.

​            -c advance -spi -init        run ssd1306 init by spi interface. 

​            -c advance -iic -a (0 | 1)        run ssd1306 init by iic interface. 0 or 1 means the iic address pin level.

​            -c advance -deinit        run ssd1306 deinit function. 

​            -c advance  -str <string>        run ssd1306 show string function. string is the shown string. 

​            -c advance -displayon        run ssd1306 display on function. 

​            -c advance  -displayoff        run ssd1306 display off function. 

​            -c advance  -clear        run ssd1306 clear screen function. 

​            -c advance -writepoint <x> <y> <data>        run ssd1306 writepoint function. 

​            -c advance -readpoint <x> <y>        run ssd1306 readpoint function.

​            -c advance -rect <x1> <y1> <x2> <y2>        run ssd1306 drawing rectangle function. x1 means x start. y1 means y start. x2 means x end. y2 means y end.

​            -c advance -enable_zoom        run ssd1306 enable zoom function. 

​            -c advance -disable_zoom        run ssd1306 disable zoom function. 

​            -c advance -deactivate_scroll        run ssd1306 deactivate scroll function. 

​            -c advance -fade_blinking (disable | fade_out | blinking) <frame>        run ssd1306 fade blinking function. frames means the running frames.  

​            -c advance -vertical_left_horizontal_scroll  <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256)        run ssd1306 setting vertical left horizontal scroll function. startpage means start page and it can be "0"-"7". endpage means end page and it can be "0"-"7". rows means display rows and it can be "0" - "63".

​            -c -advance -vertical_right_horizontal_scroll  <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256)        run ssd1306 setting vertical right horizontal scroll function. startpage means start page and it can be "0"-"7". endpage means end page and it can be "0"-"7". rows means display rows and it can be "0" - "63".

#### 3.2 command example

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
./ssd1306 -t display -iic -a 0

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
ssd1306: set vertical left horizontal scroll.
ssd1306: advance graphic test.
ssd1306: zoom in.
ssd1306: fade mode.
ssd1306: finish display test.
```

```shell
./ssd1306 -c basic -str 12345abcdEFGH

ssd1306: 12345abcdEFGH
```

```shell
./ssd1306 -c basic -iic -a 0 -init

ssd1306: init success.
```

```shell
./ssd1306 -c basic -displayoff

ssd1306: display off.
```

```shell
./ssd1306 -c basic -displayon

ssd1306: display on.
```

```shell
./ssd1306 -c basic -clear

ssd1306: clear screen.
```

```shell
./ssd1306 -c basic -deinit

ssd1306: deinit ssd1306.
```

```shell
./ssd1306 -c basic -writepoint 16 16 1

ssd1306: write point 16 16 1.
```

```shell
./ssd1306 -c basic -readpoint 16 16

ssd1306: read point 16 16 is 1.
```

```shell
./ssd1306 -c basic -rect 0 0 32 32

ssd1306: draw rect 0 0 32 32.
```

```shell
./ssd1306 -c advance -iic -a 0 -init

ssd1306: init success.
```

```shell
./ssd1306 -c advance -str 12345abcdEFGH

ssd1306: 12345abcdEFGH
```

```shell
./ssd1306 -c advance -displayoff

ssd1306: display off.
```

```shell
./ssd1306 -c advance -displayon

ssd1306: display on.
```

```shell
./ssd1306 -c advance -clear

ssd1306: clear screen.
```

```shell
./ssd1306 -c advance -writepoint 16 16 1

ssd1306: write point 16 16 1.
```

```shell
./ssd1306 -c advance -readpoint 16 16

ssd1306: read point 16 16 is 1.
```

```shell
./ssd1306 -c advance -rect 0 0 32 32

ssd1306: draw rect 0 0 32 32.
```

```shell
./ssd1306 -c advance -deinit

ssd1306: deinit ssd1306.
```

```shell
./ssd1306 -c advance -enable_zoom

ssd1306: enable zoom in.
```

```shell
./ssd1306 -c advance -disable_zoom

ssd1306: disable zoom in.
```

```shell
./ssd1306 -c advance -fade_blinking blinking 0

ssd1306: set fade blinking blinking mode with 0 frames.
```

```shell
./ssd1306 -c advance -deactivate_scroll

ssd1306: deactivate scroll.
```

```shell
./ssd1306 -c advance -vertical_left_horizontal_scroll 0 7 0 FRAME_2

ssd1306: vertical left horizontal scroll start stop rows frames 0 7 0.
```

```shell
./ssd1306 -c advance -vertical_right_horizontal_scroll 0 7 0 FRAME_2

ssd1306: vertical right horizontal scroll start stop rows frames 0 7 0.
```

```shell
./ssd1306 -h

ssd1306 -i
	show ssd1306 chip and driver information.
ssd1306 -h
	show ssd1306 help.
ssd1306 -p
	show ssd1306 pin connections of the current board.
ssd1306 -t display -spi
	run ssd1306 display test by spi interface.
ssd1306 -t display -iic -a (0 | 1)
	run ssd1306 display test by iic interface.0 or 1 means the iic address pin level.
ssd1306 -c basic -spi -init
	run ssd1306 init by spi interface.
ssd1306 -c basic -iic -a (0 | 1)
	run ssd1306 init by iic interface.0 or 1 means the iic address pin level.
ssd1306 -c basic -deinit
	run ssd1306 deinit function.
ssd1306 -c basic -str <string>
	run ssd1306 show string function.string is the shown string.
ssd1306 -c basic -displayon
	run ssd1306 display on function.
ssd1306 -c basic -displayoff
	run ssd1306 display off function.
ssd1306 -c basic -clear
	run ssd1306 clear screen function.
ssd1306 -c basic -writepoint <x> <y> <data>
	run ssd1306 writepoint function.
ssd1306 -c basic -readpoint <x> <y>
	run ssd1306 readpoint function.
ssd1306 -c basic -rect <x1> <y1> <x2> <y2>
	run ssd1306 drawing rectangle function.x1 means x start.y1 means y start.x2 means x end.y2 means y end.
ssd1306 -c advance -spi -init
	run ssd1306 init by spi interface.
ssd1306 -c advance -iic -a (0 | 1)
	run ssd1306 init by iic interface.0 or 1 means the iic address pin level.
ssd1306 -c advance -deinit
	run ssd1306 deinit function.
ssd1306 -c advance -str <string>
	run ssd1306 show string function.string is the shown string.
ssd1306 -c advance -displayon
	run ssd1306 display on function.
ssd1306 -c advance -displayoff
	run ssd1306 display off function.
ssd1306 -c advance -clear
	run ssd1306 clear screen function.
ssd1306 -c advance -writepoint <x> <y> <data>
	run ssd1306 writepoint function.
ssd1306 -c advance -readpoint <x> <y>
	run ssd1306 readpoint function.
ssd1306 -c advance -rect <x1> <y1> <x2> <y2>
	run ssd1306 drawing rectangle function.x1 means x start.y1 means y start.x2 means x end.y2 means y end.
ssd1306 -c advance -enable_zoom
	run ssd1306 enable zoom function.
ssd1306 -c advance -disable_zoom
	run ssd1306 disable zoom function.
ssd1306 -c advance -deactivate_scroll
	run ssd1306 deactivate scroll function.
ssd1306 -c advance -fade_blinking (disable | fade_out | blinking) <frame>
	run ssd1306 fade blinking function.frames means the running frames.
ssd1306 -c advance -vertical_left_horizontal_scroll <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256)
	run ssd1306 setting vertical left horizontal scroll function.startpage means start page andit can be "0"-"7".endpage means end page and it can be "0"-"7".rows means display rowsand it can be "0" - "63".
ssd1306 -c advance -vertical_right_horizontal_scroll <startpage> <endpage> <rows> (FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256)
	run ssd1306 setting vertical right horizontal scroll function.startpage means start page andit can be "0"-"7".endpage means end page and it can be "0"-"7".rows means display rowsand it can be "0" - "63".
```

