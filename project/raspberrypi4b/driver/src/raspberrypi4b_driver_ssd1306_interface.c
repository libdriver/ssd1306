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
 * SOFTWARE.i 
 *
 * @file      raspberrypi4b_driver_ssd1306_interface.c
 * @brief     raspberrypi4b driver ssd1306 interface source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/30  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/10  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ssd1306_interface.h"
#include "iic.h"
#include "spi.h"
#include "wire.h"
#include <stdarg.h>

/**
 * @brief iic device name definition
 */
#define IIC_DEVICE_NAME "/dev/i2c-1"        /**< iic device name */

/**
 * @brief spi device name definition
 */
#define SPI_DEVICE_NAME "/dev/spidev0.0"    /**< spi device name */

/**
 * @brief iic device handle definition
 */
static int gs_iic_fd;                       /**< iic handle */

/**
 * @brief spi device handle definition
 */
static int gs_spi_fd;                       /**< spi handle */

/**
 * @brief  interface iic bus init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   none
 */
uint8_t ssd1306_interface_iic_init(void)
{
    return iic_init(IIC_DEVICE_NAME, &gs_iic_fd);
}

/**
 * @brief  interface iic bus deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t ssd1306_interface_iic_deinit(void)
{
    return iic_deinit(gs_iic_fd);
}

/**
 * @brief     interface iic bus write
 * @param[in] addr iic device write address
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ssd1306_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return iic_write(gs_iic_fd, addr, reg, buf, len);
}

/**
 * @brief  interface spi bus init
 * @return status code
 *         - 0 success
 *         - 1 spi init failed
 * @note   none
 */
uint8_t ssd1306_interface_spi_init(void)
{
    return spi_init(SPI_DEVICE_NAME, &gs_spi_fd, SPI_MODE_TYPE_3, 1000 * 1000);
}

/**
 * @brief  interface spi bus deinit
 * @return status code
 *         - 0 success
 *         - 1 spi deinit failed
 * @note   none
 */
uint8_t ssd1306_interface_spi_deinit(void)
{
    return spi_deinit(gs_spi_fd);
}

/**
 * @brief     interface spi bus write
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ssd1306_interface_spi_write_cmd(uint8_t *buf, uint16_t len)
{
    return spi_write_cmd(gs_spi_fd, buf, len);
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void ssd1306_interface_delay_ms(uint32_t ms)
{
    usleep(1000 * ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void ssd1306_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    (void)printf((uint8_t *)str);
}

/**
 * @brief  interface command && data gpio init
 * @return status code
 *         - 0 success
 *         - 1 gpio init failed
 * @note   none
 */
uint8_t ssd1306_interface_spi_cmd_data_gpio_init(void)
{
    return wire_init();
}

/**
 * @brief  interface command && data gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 gpio deinit failed
 * @note   none
 */
uint8_t ssd1306_interface_spi_cmd_data_gpio_deinit(void)
{
    return wire_deinit();
}

/**
 * @brief     interface command && data gpio write
 * @param[in] value written value
 * @return    status code
 *            - 0 success
 *            - 1 gpio write failed
 * @note      none
 */
uint8_t ssd1306_interface_spi_cmd_data_gpio_write(uint8_t value)
{
    return wire_write(value);
}

/**
 * @brief  interface reset gpio init
 * @return status code
 *         - 0 success
 *         - 1 gpio init failed
 * @note   none
 */
uint8_t ssd1306_interface_reset_gpio_init(void)
{
    return wire_clock_init();
}

/**
 * @brief  interface reset gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 gpio deinit failed
 * @note   none
 */
uint8_t ssd1306_interface_reset_gpio_deinit(void)
{
    return wire_clock_deinit();
}

/**
 * @brief     interface reset gpio write
 * @param[in] value written value
 * @return    status code
 *            - 0 success
 *            - 1 gpio write failed
 * @note      none
 */
uint8_t ssd1306_interface_reset_gpio_write(uint8_t value)
{
    return wire_clock_write(value);
}
