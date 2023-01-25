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
 * @file      wire.h
 * @brief     wire header file
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

#ifndef WIRE_H
#define WIRE_H

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @defgroup wire wire function
 * @brief    wire function modules
 * @{
 */

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t wire_init(void);

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_deinit(void);

/**
 * @brief      wire bus read data
 * @param[out] *value points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t wire_read(uint8_t *value);

/**
 * @brief     wire bus write data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 *             - 1 write failed
 * @note      none
 */
uint8_t wire_write(uint8_t value);

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t wire_clock_init(void);

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_clock_deinit(void);

/**
 * @brief     wire bus write data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wire_clock_write(uint8_t value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
