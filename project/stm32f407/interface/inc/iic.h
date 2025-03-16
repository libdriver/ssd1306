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
 * @file      iic.h
 * @brief     iic header file
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

#ifndef IIC_H
#define IIC_H

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @defgroup iic iic function
 * @brief    iic function modules
 * @{
 */

/**
 * @brief  iic bus init
 * @return status code
 *         - 0 success
 * @note   SCL is PB8 and SDA is PB9
 */
uint8_t iic_init(void);

/**
 * @brief  iic bus deinit
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t iic_deinit(void);

/**
 * @brief     iic bus write command
 * @param[in] addr iic device write address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      addr = device_address_7bits << 1
 */
uint8_t iic_write_cmd(uint8_t addr, uint8_t *buf, uint16_t len);

/**
 * @brief     iic bus write
 * @param[in] addr iic device write address
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      addr = device_address_7bits << 1
 */
uint8_t iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief     iic bus write with 16 bits register address 
 * @param[in] addr iic device write address
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      addr = device_address_7bits << 1
 */
uint8_t iic_write_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      iic bus read command
 * @param[in]  addr iic device write address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       addr = device_address_7bits << 1
 */
uint8_t iic_read_cmd(uint8_t addr, uint8_t *buf, uint16_t len);

/**
 * @brief      iic bus read
 * @param[in]  addr iic device write address
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       addr = device_address_7bits << 1
 */
uint8_t iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      iic bus read with 16 bits register address 
 * @param[in]  addr iic device write address
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       addr = device_address_7bits << 1
 */
uint8_t iic_read_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
