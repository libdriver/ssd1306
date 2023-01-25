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

/**
 * @brief bit operate definition
 */
#define BITBAND(addr, bitnum)    ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2)) 
#define MEM_ADDR(addr)           *((uint32_t *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

/**
 * @brief wire gpio operate definition
 */
#define GPIOA_ODR_Addr        (GPIOA_BASE + 0x14)
#define GPIOA_IDR_Addr        (GPIOA_BASE + 0x10)
#define PAout(n)               BIT_ADDR(GPIOA_ODR_Addr, n)
#define PAin(n)                BIT_ADDR(GPIOA_IDR_Addr, n)
#define IO_IN()               {GPIOA->MODER &= ~(3 << (8 * 2)); GPIOA->MODER |= 0 << (8 * 2);}
#define IO_OUT()              {GPIOA->MODER &= ~(3 << (8 * 2)); GPIOA->MODER |= 1 << (8 * 2);} 
#define DQ_OUT                 PAout(8)
#define DQ_IN                  PAin(8)

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 * @note   IO is PA8
 */
uint8_t wire_init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    /* enable gpio clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    /* gpio init */
    GPIO_Initure.Pin = GPIO_PIN_8;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
    
    /* output mode */
    IO_OUT();
    
    /* set high */
    DQ_OUT = 1;
    
    /* input mode */
    IO_IN();
 
    return 0;
}

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_deinit(void)
{
    /* gpio deinit */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);
    
    return 0; 
}

/**
 * @brief      wire bus read data
 * @param[out] *value points to a read data buffer
 * @return     status code
 *             - 0 success
 * @note       none
 */
uint8_t wire_read(uint8_t *value)
{
    /* input mode */
    IO_IN();
    
    /* read the data */
    *value = DQ_IN;
    
    return 0;
}

/**
 * @brief     wire bus write data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t wire_write(uint8_t value)
{
    /* output mode */
    IO_OUT();
    
    /* set the data */
    DQ_OUT = value;
  
    return 0;
}

/**
 * @brief  wire bus init
 * @return status code
 *         - 0 success
 * @note   IO is PA0
 */
uint8_t wire_clock_init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    /* enable gpio clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    /* gpio init */
    GPIO_Initure.Pin = GPIO_PIN_0;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure); 
    
    return 0;
}

/**
 * @brief  wire bus deint
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t wire_clock_deinit(void)
{
    /* gpio deinit */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
    
    return 0;
}

/**
 * @brief     wire bus write the data
 * @param[in] value is the write data
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t wire_clock_write(uint8_t value)
{
    if (value != 0)
    {
        /* set high */
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    }
    else
    {
        /* set low */
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    }
    
    return 0;
}
