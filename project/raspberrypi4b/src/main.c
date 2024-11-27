/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ssd1306_basic.h"
#include "driver_ssd1306_advance.h"
#include "driver_ssd1306_display_test.h"
#include "shell.h"
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                              /**< uart buffer */
volatile uint16_t g_len;                         /**< uart buffer length */
static int gs_listen_fd;                         /**< network handle */
static int gs_conn_fd;                           /**< network handle */
static struct sockaddr_in gs_server_addr;        /**< server address */

/**
 * @brief     ssd1306 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ssd1306(uint8_t argc, char** argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"color", required_argument, NULL, 2},
        {"frame", required_argument, NULL, 3},
        {"frames", required_argument, NULL, 4},
        {"interface", required_argument, NULL, 5},
        {"mode", required_argument, NULL, 6},
        {"row", required_argument, NULL, 7},
        {"start", required_argument, NULL, 8},
        {"stop", required_argument, NULL, 9},
        {"str", required_argument, NULL, 10},
        {"x0", required_argument, NULL, 11},
        {"x1", required_argument, NULL, 12},
        {"x2", required_argument, NULL, 13},
        {"y0", required_argument, NULL, 14},
        {"y1", required_argument, NULL, 15},
        {"y2", required_argument, NULL, 16},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    ssd1306_address_t addr = SSD1306_ADDR_SA0_0;
    ssd1306_scroll_frame_t frame = SSD1306_SCROLL_FRAME_2;
    ssd1306_interface_t interface = SSD1306_INTERFACE_IIC;
    ssd1306_fade_blinking_mode_t mode = SSD1306_FADE_BLINKING_MODE_DISABLE;
    uint8_t color = 1;
    uint8_t frames = 0;
    uint8_t row = 0;
    uint8_t start = 0;
    uint8_t stop = 7;
    uint8_t x0 = 0;
    uint8_t x1 = 0;
    uint8_t x2 = 0;
    uint8_t y0 = 0;
    uint8_t y1 = 0;
    uint8_t y2 = 0;
    uint8_t x0_flag = 0;
    uint8_t x1_flag = 0;
    uint8_t x2_flag = 0;
    uint8_t y0_flag = 0;
    uint8_t y1_flag = 0;
    uint8_t y2_flag = 0;
    uint8_t color_flag = 0;
    char str[49] = "libdriver";
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = SSD1306_ADDR_SA0_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = SSD1306_ADDR_SA0_1;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* color */
            case 2 :
            {
                /* set the color */
                if (strcmp("0", optarg) == 0)
                {
                    color = 0;
                    color_flag = 1;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    color = 1;
                    color_flag = 1;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* frame */
            case 3 :
            {
                /* set the frame */
                if (strcmp("FRAME_2", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_2;
                }
                else if (strcmp("FRAME_3", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_3;
                }
                else if (strcmp("FRAME_4", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_4;
                }
                else if (strcmp("FRAME_5", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_5;
                }
                else if (strcmp("FRAME_25", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_25;
                }
                else if (strcmp("FRAME_64", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_64;
                }
                else if (strcmp("FRAME_128", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_128;
                }
                else if (strcmp("FRAME_256", optarg) == 0)
                {
                    frame = SSD1306_SCROLL_FRAME_256;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
             
            /* frames */
            case 4 :
            {
                /* set the frames */
                frames = atol(optarg);
                
                break;
            }
            
            /* interface */
            case 5 :
            {
                /* set the interface */
                if (strcmp("iic", optarg) == 0)
                {
                    interface = SSD1306_INTERFACE_IIC;
                }
                else if (strcmp("spi", optarg) == 0)
                {
                    interface = SSD1306_INTERFACE_SPI;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* mode */
            case 6 :
            {
                /* set the mode */
                if (strcmp("DISABLE", optarg) == 0)
                {
                    mode = SSD1306_FADE_BLINKING_MODE_DISABLE;
                }
                else if (strcmp("FADE-OUT", optarg) == 0)
                {
                    mode = SSD1306_FADE_BLINKING_MODE_FADE_OUT;
                }
                else if (strcmp("BLINKING", optarg) == 0)
                {
                    mode = SSD1306_FADE_BLINKING_MODE_BLINKING;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* row */
            case 7 :
            {
                /* set the row */
                row = atol(optarg);
                
                break;
            }
            
            /* start */
            case 8 :
            {
                /* set the start */
                start = atol(optarg);
                
                break;
            }
            
            /* stop */
            case 9 :
            {
                /* set the stop */
                stop = atol(optarg);
                
                break;
            }
            
            /* str */
            case 10 :
            {
                /* set the str */
                memset(str, 0, sizeof(char) * 49);
                strncpy(str, optarg, 48);
                
                break;
            }
            
            /* x0 */
            case 11 :
            {
                /* convert */
                x0 = atol(optarg);
                x0_flag = 1;
                
                break;
            }
            
            /* x1 */
            case 12 :
            {
                /* convert */
                x1 = atol(optarg);
                x1_flag = 1;
                
                break;
            }
            
            /* x2 */
            case 13 :
            {
                /* convert */
                x2 = atol(optarg);
                x2_flag = 1;
                
                break;
            }
            /* y0 */
            case 14 :
            {
                /* convert */
                y0 = atol(optarg);
                y0_flag = 1;
                
                break;
            }
            
            /* y1 */
            case 15 :
            {
                /* convert */
                y1 = atol(optarg);
                y1_flag = 1;
                
                break;
            }
            
            /* y2 */
            case 16 :
            {
                /* convert */
                y2 = atol(optarg);
                y2_flag = 1;
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);
    
    /* run the function */
    if (strcmp("t_display", type) == 0)
    {
        /* run display test */
        if (ssd1306_display_test(interface, addr) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_basic-str", type) == 0)
    {
        uint8_t res;
        
        /* clear */
        res = ssd1306_basic_clear();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
            (void)ssd1306_basic_deinit();
            
            return 1;
        }
        
        /* set the string */
        res = ssd1306_basic_string(0, 0, str, (uint16_t)strlen(str), color, SSD1306_FONT_16);
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: show string failed.\n");
            (void)ssd1306_basic_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: %s.\n", str);
        
        return 0;
    }
    else if (strcmp("e_basic-init", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = ssd1306_basic_init(interface, addr);
        if (res != 0)
        {
            (void)ssd1306_basic_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: init success.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-display-off", type) == 0)
    {
        uint8_t res;
        
        /* display off */
        res = ssd1306_basic_display_off();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: display off failed.\n");
            (void)ssd1306_basic_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: display off.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-display-on", type) == 0)
    {
        uint8_t res;
        
        /* display on */
        res = ssd1306_basic_display_on();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: display on failed.\n");
            (void)ssd1306_basic_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: display on.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-clear", type) == 0)
    {
        uint8_t res;
        
        /* clear */
        res = ssd1306_basic_clear();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
            (void)ssd1306_basic_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: clear screen.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-deinit", type) == 0)
    {
        uint8_t res;
        
        /* deinit */
        res = ssd1306_basic_deinit();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: deinit failed.\n");
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: deinit ssd1306.\n");
        
        return 0;
    }
    else if (strcmp("e_basic-point", type) == 0)
    {
        if ((x0_flag == 1) && (y0_flag == 1) && (color_flag == 0))
        {
            uint8_t res;
            uint8_t data;
            
            /* read point */
            res = ssd1306_basic_read_point(x0, y0, (uint8_t*)&data);
            if (res != 0)
            {
                (void)ssd1306_basic_deinit();
                
                return 1;
            }
            
            /* output */
            ssd1306_interface_debug_print("ssd1306: read point %d %d is %d.\n", x0, y0, data);
            
            return 0;
        }
        else if ((x0_flag == 1) && (y0_flag == 1) && (color_flag == 1))
        {
            uint8_t res;
            
            /* write point */
            res = ssd1306_basic_write_point(x0, y0, color);
            if (res != 0)
            {
                (void)ssd1306_basic_deinit();
                
                return 1;
            }
            
            /* output */
            ssd1306_interface_debug_print("ssd1306: write point %d %d %d.\n", x0, y0, color);
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (strcmp("e_basic-rect", type) == 0)
    {
        uint8_t res;
        
        /* check the flag */
        if ((x1_flag != 1) || (y1_flag != 1) || (x2_flag != 1) || (y2_flag != 1))
        {
             return 5;
        }
        
        /* rect */
        res = ssd1306_basic_rect(x1, y1, x2, y2, color);
        if (res != 0)
        {
            (void)ssd1306_basic_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: draw rect %d %d %d %d.\n", x1, y1, x2, y2);
        
        return 0;
    }
    else if (strcmp("e_advance-init", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = ssd1306_advance_init(interface, addr);
        if (res != 0)
        {
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: init success.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-str", type) == 0)
    {
        uint8_t res;
        
        /* clear */
        res = ssd1306_advance_clear();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* set the string */
        res = ssd1306_advance_string(0, 0, str, (uint16_t)strlen(str), color, SSD1306_FONT_16);
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: show string failed.\n");
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: %s.\n", str);
        
        return 0;
    }
    else if (strcmp("e_advance-display-off", type) == 0)
    {
        uint8_t res;

        /* display off */
        res = ssd1306_advance_display_off();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: display off failed.\n");
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: display off.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-display-on", type) == 0)
    {
        uint8_t res;
        
        /* display on */
        res = ssd1306_advance_display_on();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: display on failed.\n");
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: display on.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-clear", type) == 0)
    {
        uint8_t res;
        
        /* clear */
        res = ssd1306_advance_clear();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: clear screen failed.\n");
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: clear screen.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-point", type) == 0)
    {
        if ((x0_flag == 1) && (y0_flag == 1) && (color_flag == 0))
        {
            uint8_t res;
            uint8_t data;
            
            /* read point */
            res = ssd1306_advance_read_point(x0, y0, (uint8_t*)&data);
            if (res != 0)
            {
                (void)ssd1306_advance_deinit();
                
                return 1;
            }
            
            /* output */
            ssd1306_interface_debug_print("ssd1306: read point %d %d is %d.\n", x0, y0, data);
            
            return 0;
        }
        else if ((x0_flag == 1) && (y0_flag == 1) && (color_flag == 1))
        {
            uint8_t res;
            
            /* write point */
            res = ssd1306_advance_write_point(x0, y0, color);
            if (res != 0)
            {
                (void)ssd1306_advance_deinit();
                
                return 1;
            }
            
            /* output */
            ssd1306_interface_debug_print("ssd1306: write point %d %d %d.\n", x0, y0, color);
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (strcmp("e_advance-rect", type) == 0)
    {
        uint8_t res;

        /* check the flag */
        if ((x1_flag != 1) || (y1_flag != 1) || (x2_flag != 1) || (y2_flag != 1))
        {
             return 5;
        }
         
        /* rect */
        res = ssd1306_advance_rect(x1, y1, x2, y2, color);
        if (res != 0)
        {
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: draw rect %d %d %d %d.\n", x1, y1, x2, y2);
        
        return 0;
    }
    else if (strcmp("e_advance-deinit", type) == 0)
    {
        uint8_t res;
        
        /* deinit */
        res = ssd1306_advance_deinit();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: deinit failed.\n");
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: deinit ssd1306.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-enable-zoom", type) == 0)
    {
        uint8_t res;
        
        /* enable */
        res = ssd1306_advance_enable_zoom_in();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: enable zoom in failed.\n");
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: enable zoom in.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-disable-zoom", type) == 0)
    {
        uint8_t res;
        
        /* disable */
        res = ssd1306_advance_disable_zoom_in();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: disable zoom in failed.\n");
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: disable zoom in.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-fade-blinking", type) == 0)
    {
        uint8_t res;
        char str_s[4][16] = { "disable", "", "fade out", "blinking" };
        
        /* fade blinking */
        res = ssd1306_advance_fade_blinking(mode, frames);
        if (res != 0)
        {
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: set fade blinking %s mode with %d frames.\n", str_s[(uint8_t)mode], frames);
        
        return 0;
    }
    else if (strcmp("e_advance-deactivate-scroll", type) == 0)
    {
        uint8_t res;
        
        /* deactivate */
        res = ssd1306_advance_deactivate_scroll();
        if (res != 0)
        {
            ssd1306_interface_debug_print("ssd1306: deactivate scroll failed.\n");
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: deactivate scroll.\n");
        
        return 0;
    }
    else if (strcmp("e_advance-left-scroll", type) == 0)
    {
        uint8_t res;
        
        /* left scroll */
        res = ssd1306_advance_vertical_left_horizontal_scroll(start, stop, row, frame);
        if (res != 0)
        {
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: vertical left horizontal scroll start stop rows frames %d %d %d.\n", start, stop, row);
        
        return 0;
    }
    else if (strcmp("e_advance-right-scroll", type) == 0)
    {
        uint8_t res;
        
        /* right scroll */
        res = ssd1306_advance_vertical_right_horizontal_scroll(start, stop, row, frame);
        if (res != 0)
        {
            (void)ssd1306_advance_deinit();
            
            return 1;
        }
        
        /* output */
        ssd1306_interface_debug_print("ssd1306: vertical right horizontal scroll start stop rows frames %d %d %d.\n", start, stop, row);
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ssd1306_interface_debug_print("Usage:\n");
        ssd1306_interface_debug_print("  ssd1306 (-i | --information)\n");
        ssd1306_interface_debug_print("  ssd1306 (-h | --help)\n");
        ssd1306_interface_debug_print("  ssd1306 (-p | --port)\n");
        ssd1306_interface_debug_print("  ssd1306 (-t display | --test=display) [--addr=<0 | 1>] [--interface=<iic | spi>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-init | --example=basic-init) [--addr=<0 | 1>] [--interface=<iic | spi>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-deinit | --example=basic-deinit)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-str | --example=basic-str) [--str=<string>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-display-on | --example=basic-display-on)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-display-off | --example=basic-display-off)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-clear | --example=basic-clear)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-point | --example=basic-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e basic-rect | --example=basic-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-init | --example=advance-init) [--addr=<0 | 1>] [--interface=<iic | spi>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-deinit | --example=advance-deinit)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-str | --example=advance-str) [--str=<string>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-display-on | --example=advance-display-on)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-display-off | --example=advance-display-off)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-clear | --example=advance-clear)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-point | --example=advance-point) --x0=<x0> --y0=<y0> [--color=<0 | 1>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-rect | --example=advance-rect) --x1=<x1> --y1=<y1> --x2=<x2> --y2=<y2> [--color=<0 | 1>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-enable-zoom | --example=advance-enable-zoom)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-disable-zoom | --example=advance-disable-zoom)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-deactivate-scroll | --example=advance-deactivate-scroll)\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-fade-blinking | --example=advance-fade-blinking) [--mode=<DISABLE | FADE-OUT | BLINKING>]\n");
        ssd1306_interface_debug_print("          [--frames=<f>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-left-scroll | --example=advance-left-scroll) [--start=<spage>] [--stop=<epage>] [--row=<r>]\n");
        ssd1306_interface_debug_print("          [--frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>]\n");
        ssd1306_interface_debug_print("  ssd1306 (-e advance-right-scroll | --example=advance-right-scroll) [--start=<spage>] [--stop=<epage>] [--row=<r>]\n");
        ssd1306_interface_debug_print("          [--frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>]\n");
        ssd1306_interface_debug_print("\n");
        ssd1306_interface_debug_print("Options:\n");
        ssd1306_interface_debug_print("      --addr=<0 | 1>      Set the iic addr pin.([default: 0])\n");
        ssd1306_interface_debug_print("      --color=<0 | 1>     Set the chip color.([default: 1])\n");
        ssd1306_interface_debug_print("  -e <basic-init | basic-deinit | basic-str | basic-display-on | basic-display-off | basic-clear \n");
        ssd1306_interface_debug_print("     | basic-point | basic-rect>, --example=<advance-init | advance-deinit | advance-str | advance-display-on\n");
        ssd1306_interface_debug_print("     | advance-display-off | advance-clear | advance-point | advance-rect | advance-enable-zoom | advance-disable-zoom\n");
        ssd1306_interface_debug_print("     | advance-fade-blinking | advance-left-scroll | advance-right-scroll | advance-deactivate-scroll>\n");
        ssd1306_interface_debug_print("                          Run the driver example.\n");
        ssd1306_interface_debug_print("      --frame=<FRAME_2 | FRAME_3 | FRAME_4 | FRAME_5 | FRAME_25 | FRAME_64 | FRAME_128 | FRAME_256>\n");
        ssd1306_interface_debug_print("                          Set the scrolling frame.([default: FRAME_2])\n");
        ssd1306_interface_debug_print("      --frames=<f>        Se the fade-blinking frames.([default: 0])\n");
        ssd1306_interface_debug_print("  -h, --help              Show the help.\n");
        ssd1306_interface_debug_print("  -i, --information       Show the chip information.\n");
        ssd1306_interface_debug_print("      --interface=<iic | spi>\n");
        ssd1306_interface_debug_print("                          Set the chip interface.([default: iic])\n");
        ssd1306_interface_debug_print("      --mode=<DISABLE | FADE-OUT | BLINKING>\n");
        ssd1306_interface_debug_print("                          Set the fade-blinking mode.([default: DISABLE])\n");
        ssd1306_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        ssd1306_interface_debug_print("      --row=<r>           Set the scrolling row.([default: 0])\n");
        ssd1306_interface_debug_print("      --start=<spage>     Set the scrolling start page.([default: 0])\n");
        ssd1306_interface_debug_print("      --stop=<epage>      Set the scrolling stop page.([default: 7])\n");
        ssd1306_interface_debug_print("      --str=<string>      Set the display string.([default: libdriver])\n");
        ssd1306_interface_debug_print("  -t <display>, --test=<display>\n");
        ssd1306_interface_debug_print("                          Run the driver test.\n");
        ssd1306_interface_debug_print("      --x0=<x0>           Set the x0 and it is the x of the point.\n");
        ssd1306_interface_debug_print("      --x1=<x1>           Set the x1 and it is the top left x of the rect.\n");
        ssd1306_interface_debug_print("      --x2=<x2>           Set the x2 and it is the bottom right x of the rect.\n");
        ssd1306_interface_debug_print("      --y0=<y0>           Set the y0 and it is the y of the point.\n");
        ssd1306_interface_debug_print("      --y1=<y1>           Set the y1 and it is the top left y of the rect.\n");
        ssd1306_interface_debug_print("      --y2=<y2>           Set the y2 and it is the bottom right y of the rect.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ssd1306_info_t info;
        
        /* print ssd1306 info */
        ssd1306_info(&info);
        ssd1306_interface_debug_print("ssd1306: chip is %s.\n", info.chip_name);
        ssd1306_interface_debug_print("ssd1306: manufacturer is %s.\n", info.manufacturer_name);
        ssd1306_interface_debug_print("ssd1306: interface is %s.\n", info.interface);
        ssd1306_interface_debug_print("ssd1306: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ssd1306_interface_debug_print("ssd1306: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ssd1306_interface_debug_print("ssd1306: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ssd1306_interface_debug_print("ssd1306: max current is %0.2fmA.\n", info.max_current_ma);
        ssd1306_interface_debug_print("ssd1306: max temperature is %0.1fC.\n", info.temperature_max);
        ssd1306_interface_debug_print("ssd1306: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ssd1306_interface_debug_print("ssd1306: SPI interface SCK connected to GPIO11(BCM).\n");
        ssd1306_interface_debug_print("ssd1306: SPI interface MISO connected to GPIO9(BCM).\n");
        ssd1306_interface_debug_print("ssd1306: SPI interface MOSI connected to GPIO10(BCM).\n");
        ssd1306_interface_debug_print("ssd1306: SPI interface CS connected to GPIO8(BCM).\n");
        ssd1306_interface_debug_print("ssd1306: SPI interface cmd data gpio GPIO connected to GPIO17(BCM).\n");
        ssd1306_interface_debug_print("ssd1306: SPI interface reset GPIO connected to GPIO27(BCM).\n");
        ssd1306_interface_debug_print("ssd1306: IIC interface SCL connected to GPIO3(BCM).\n");
        ssd1306_interface_debug_print("ssd1306: IIC interface SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief  socket init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
static uint8_t a_socket_init(void)
{
    int optval;
    
    /* creat a socket */
    gs_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (gs_listen_fd < 0) 
    {
        ssd1306_interface_debug_print("ssd1306: create socket failed.\n");
        
        return 1;
    }
    
    /* set the server port */
    memset(&gs_server_addr, 0, sizeof(gs_server_addr));
    gs_server_addr.sin_family = AF_INET;
    gs_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    gs_server_addr.sin_port = htons(6666);
    
    /* enable same port binding */
    optval = 1;
    if (setsockopt(gs_listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) < 0)
    {
        ssd1306_interface_debug_print("ssd1306: create socket failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* bind the port */
    if (bind(gs_listen_fd, (struct sockaddr*)&gs_server_addr, sizeof(gs_server_addr)) < 0) 
    {
        ssd1306_interface_debug_print("ssd1306: bind failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* listen the port */
    if (listen(gs_listen_fd, 10) < 0) 
    {
        ssd1306_interface_debug_print("ssd1306: listen failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    } 
    
    return 0;
}

/**
 * @brief     socket read
 * @param[in] *buf points to a buffer address
 * @param[in] len is the buffer length
 * @return    status code
 *             - 0 success
 *             - 1 read failed
 * @note      none
 */
static uint16_t a_socket_read(uint8_t *buf, uint16_t len)
{
    int n;
    
    /* wait data */
    gs_conn_fd = accept(gs_listen_fd, (struct sockaddr *)NULL, NULL);
    if (gs_conn_fd < 0) 
    {
        ssd1306_interface_debug_print("ssd1306: accept failed.\n");
        (void)close(gs_conn_fd);

        return 1;
    }
    
    /* read data */
    n = recv(gs_conn_fd, buf, len, 0);
    
    /* close the socket */
    (void)close(gs_conn_fd);
    
    return n;
}

/**
 * @brief     signal handler
 * @param[in] signum is the signal number
 * @note      none
 */
static void a_sig_handler(int signum)
{
    if (SIGINT == signum)
    {
        ssd1306_interface_debug_print("ssd1306: close the server.\n");
        (void)close(gs_listen_fd);
        exit(0);
    }
    
    return;
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* socket init*/
    res = a_socket_init();
    if (res != 0)
    {
        ssd1306_interface_debug_print("ssd1306: socket init failed.\n");
        
        return 1;
    }
    
    /* shell init && register ssd1306 function */
    shell_init();
    shell_register("ssd1306", ssd1306);
    ssd1306_interface_debug_print("ssd1306: welcome to libdriver ssd1306.\n");
    
    /* set the signal */
    signal(SIGINT, a_sig_handler);
    
    while (1)
    {
        /* read uart */
        g_len = a_socket_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                ssd1306_interface_debug_print("ssd1306: run failed.\n");
            }
            else if (res == 2)
            {
                ssd1306_interface_debug_print("ssd1306: unknown command.\n");
            }
            else if (res == 3)
            {
                ssd1306_interface_debug_print("ssd1306: length is too long.\n");
            }
            else if (res == 4)
            {
                ssd1306_interface_debug_print("ssd1306: pretreat failed.\n");
            }
            else if (res == 5)
            {
                ssd1306_interface_debug_print("ssd1306: param is invalid.\n");
            }
            else
            {
                ssd1306_interface_debug_print("ssd1306: unknown status code.\n");
            }
        }
    }
}
