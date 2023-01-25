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
 * @file      wire.c
 * @brief     wire source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-11-11
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/11  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "wire.h"
#include <gpiod.h>

/**
 * @brief gpio device name definition
 */
#define GPIO_DEVICE_NAME "/dev/gpiochip0"        /**< gpio device name */

/**
 * @brief gpio device line definition
 */
#define GPIO_DEVICE_LINE 17                      /**< gpio device line */
#define GPIO_DEVICE_CLOCK_LINE 27                /**< gpio device clock line */

/**
 * @brief global var definition
 */
static struct gpiod_chip *gs_chip;               /**< gpio chip handle */
static struct gpiod_line *gs_line;               /**< gpio line handle */
static struct gpiod_chip *gs_clock_chip;         /**< gpio clock chip handle */
static struct gpiod_line *gs_clock_line;         /**< gpio clock line handle */
static volatile uint8_t gs_read_write_flag;      /**< read write flag */

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t wire_init(void)
{
    /* open the gpio group */
    gs_chip = gpiod_chip_open(GPIO_DEVICE_NAME);
    if (gs_chip == NULL)
    {
        perror("gpio: open failed.\n");
        
        return 1;
    }
    
    /* get the gpio line */
    gs_line = gpiod_chip_get_line(gs_chip, GPIO_DEVICE_LINE);
    if (gs_line == NULL) 
    {
        perror("gpio: get line failed.\n");
        gpiod_chip_close(gs_chip);
        
        return 1;
    }
    
    /* set the flag */
    gs_read_write_flag = 2;
    
    /* set high */
    return wire_write(1);
}

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_deinit(void)
{
    /* close the chip */
    gpiod_chip_close(gs_chip);
    
    return 0;
}

/**
 * @brief      wire bus read data
 * @param[out] *value points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t wire_read(uint8_t *value)
{
    int res;
    
    /* check the flag */
    if (gs_read_write_flag != 0)
    {
        /* check requested */
        if (gpiod_line_is_requested(gs_line) != 0) 
        {
            /* release */
            gpiod_line_release(gs_line);
        }
        
        /* set input */
        if (gpiod_line_request_input(gs_line, "gpio_input") != 0) 
        {
            return 1;
        }
        
        /* flag read */
        gs_read_write_flag = 0;
    }
    
    /* read the value */
    res = gpiod_line_get_value(gs_line);
    if (res < 0)
    {
        return 1;
    }
    
    /* set the value */
    *value = (uint8_t)(res);
    
    return 0;
}

/**
 * @brief     wire bus write data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 *             - 1 write failed
 * @note      none
 */
uint8_t wire_write(uint8_t value)
{
    /* check the flag */
    if (gs_read_write_flag != 1)
    {
        /* check requested */
        if (gpiod_line_is_requested(gs_line) != 0) 
        {
            /* release */
            gpiod_line_release(gs_line);
        }
        
        /* set output */
        if (gpiod_line_request_output(gs_line, "gpio_output", GPIOD_LINE_ACTIVE_STATE_HIGH) != 0)
        {
            return 1;
        }
        
        /* flag write */
        gs_read_write_flag = 1;
    }
    
    /* set the value */
    if (gpiod_line_set_value(gs_line, value) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t wire_clock_init(void)
{
    /* open the gpio group */
    gs_clock_chip = gpiod_chip_open(GPIO_DEVICE_NAME);
    if (gs_clock_chip == NULL)
    {
        perror("gpio: open failed.\n");
        
        return 1;
    }
    
    /* get the gpio line */
    gs_clock_line = gpiod_chip_get_line(gs_clock_chip, GPIO_DEVICE_CLOCK_LINE);
    if (gs_clock_line == NULL) 
    {
        perror("gpio: get line failed.\n");
        gpiod_chip_close(gs_clock_chip);

        return 1;
    }
    
    /* set output */
    if (gpiod_line_request_output(gs_clock_line, "gpio_output", GPIOD_LINE_ACTIVE_STATE_HIGH) != 0)
    {
        return 1;
    }
    
    /* set high */
    return wire_clock_write(1);
}

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_clock_deinit(void)
{
    /* close the chip */
    gpiod_chip_close(gs_clock_chip);
    
    return 0;
}

/**
 * @brief     wire bus write data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wire_clock_write(uint8_t value)
{
    /* write the value */
    if (gpiod_line_set_value(gs_clock_line, value) != 0)
    {
        return 1;
    }
    
    return 0;
}
