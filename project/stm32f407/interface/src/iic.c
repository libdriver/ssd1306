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
 * @file      iic.c
 * @brief     iic source file
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

#include "iic.h"
#include "delay.h"

/**
 * @brief bit operate definition
 */
#define BITBAND(addr, bitnum)    ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2)) 
#define MEM_ADDR(addr)           *((uint32_t *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

/**
 * @brief iic gpio operate definition
 */
#define GPIOB_ODR_Addr    (GPIOB_BASE + 0x14)
#define GPIOB_IDR_Addr    (GPIOB_BASE + 0x10)
#define PBout(n)          BIT_ADDR(GPIOB_ODR_Addr, n)
#define PBin(n)           BIT_ADDR(GPIOB_IDR_Addr, n)
#define SDA_IN()          {GPIOB->MODER &= ~(3 << (9 * 2)); GPIOB->MODER |= 0 << 9 * 2;}
#define SDA_OUT()         {GPIOB->MODER &= ~(3 << (9 * 2)); GPIOB->MODER |= 1 << 9 * 2;}
#define IIC_SCL           PBout(8)
#define IIC_SDA           PBout(9)
#define READ_SDA          PBin(9)

/**
 * @brief  iic bus init
 * @return status code
 *         - 0 success
 * @note   SCL is PB8 and SDA is PB9
 */
uint8_t iic_init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    /* enable iic gpio clock */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    /* iic gpio init */
    GPIO_Initure.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;   
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    
    /* set sda high */
    IIC_SDA = 1;
    
    /* set scl high */
    IIC_SCL = 1;
    
    return 0;
}

/**
 * @brief  iic bus deinit
 * @return status code
 *         - 0 success
 * @note   none
 */
uint8_t iic_deinit(void)
{
    /* iic gpio deinit */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);
    
    return 0;
}

/**
 * @brief iic bus send start
 * @note  none
 */
static void a_iic_start(void)
{
    SDA_OUT();
    IIC_SDA = 1;
    IIC_SCL = 1;
    delay_us(4);
    IIC_SDA = 0;
    delay_us(4);
    IIC_SCL = 0;
}

/**
 * @brief iic bus send stop
 * @note  none
 */
static void a_iic_stop(void)
{
    SDA_OUT();
    IIC_SCL = 0;
    IIC_SDA = 0;
    delay_us(4);
    IIC_SCL = 1;
    delay_us(4);
    IIC_SDA = 1;
    delay_us(4);
}

/**
 * @brief  iic wait ack
 * @return status code
 *         - 0 get ack
 *         - 1 no ack
 * @note   none
 */
static uint8_t a_iic_wait_ack(void)
{
    uint16_t uc_err_time = 0;
    
    SDA_IN();
    IIC_SDA = 1; 
    delay_us(1);
    IIC_SCL = 1; 
    delay_us(1);
    while (READ_SDA != 0)
    {
        uc_err_time++;
        if (uc_err_time > 250)
        {
            a_iic_stop();
            
            return 1;
        }
    }
    IIC_SCL = 0;
    
    return 0;
}

/**
 * @brief iic bus send ack
 * @note  none
 */
static void a_iic_ack(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 0;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(2);
    IIC_SCL = 0;
}

/**
 * @brief iic bus send nack
 * @note  none
 */
static void a_iic_nack(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 1;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(2);
    IIC_SCL = 0; 
}

/**
 * @brief     iic send one byte
 * @param[in] txd is the sent byte
 * @note      none
 */
static void a_iic_send_byte(uint8_t txd)
{
    uint8_t t;
    
    SDA_OUT();
    IIC_SCL = 0;
    for (t = 0; t < 8; t++)
    {
        IIC_SDA = (txd & 0x80) >> 7;
        txd <<= 1;
        delay_us(2);
        IIC_SCL = 1;
        delay_us(2);
        IIC_SCL = 0;
        delay_us(2);
    }
}

/**
 * @brief     iic read one byte
 * @param[in] ack is the sent ack
 * @return    read byte
 * @note      none
 */
static uint8_t a_iic_read_byte(uint8_t ack)
{
    uint8_t i;
    uint8_t receive = 0;
    
    SDA_IN();
    for (i = 0; i < 8; i++)
    {
        IIC_SCL = 0;
        delay_us(2);
        IIC_SCL = 1;
        receive <<= 1;
        if (READ_SDA != 0)
        {
            receive++;
        }
        delay_us(1);
    }
    if (ack != 0)
    {
        a_iic_ack();
    }
    else
    {
        a_iic_nack();
    }
    
    return receive;
}

/**
 * @brief     iic bus write command
 * @param[in] addr is the iic device write address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      addr = device_address_7bits << 1
 */
uint8_t iic_write_cmd(uint8_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i; 
    
    /* send a start */
    a_iic_start();
    
    /* send the write addr */
    a_iic_send_byte(addr);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* write the data */
    for (i = 0; i < len; i++)
    {
        /* send one byte */
        a_iic_send_byte(buf[i]);
        if (a_iic_wait_ack() != 0)
        {
            a_iic_stop();
            
            return 1;
        }
    }
    
    /* send a stop */
    a_iic_stop();
    
    return 0;
} 

/**
 * @brief     iic bus write
 * @param[in] addr is the iic device write address
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      addr = device_address_7bits << 1
 */
uint8_t iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t i; 
    
    /* send a start */
    a_iic_start();
    
    /* send the write addr */
    a_iic_send_byte(addr);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send the reg */
    a_iic_send_byte(reg);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* write the data */
    for (i = 0; i < len; i++)
    {
        /* send one byte */
        a_iic_send_byte(buf[i]);
        if (a_iic_wait_ack() != 0)
        {
            a_iic_stop(); 
            
            return 1;
        }
    }
    
    /* send a stop */
    a_iic_stop();
    
    return 0;
} 

/**
 * @brief     iic bus write with 16 bits register address 
 * @param[in] addr is the iic device write address
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      addr = device_address_7bits << 1
 */
uint8_t iic_write_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t i; 
    
    /* send a start */
    a_iic_start();
    
    /* send the write addr */
    a_iic_send_byte(addr);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send the reg high part */
    a_iic_send_byte((reg >> 8) & 0xFF);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send the reg low part */
    a_iic_send_byte(reg & 0xFF);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* write the data */
    for (i = 0; i < len; i++)
    {
        /* send one byte */
        a_iic_send_byte(buf[i]);
        if (a_iic_wait_ack() != 0)
        {
            a_iic_stop();
            
            return 1;
        }
    }
    
    /* send a stop */
    a_iic_stop();
    
    return 0;
} 

/**
 * @brief      iic bus read command
 * @param[in]  addr is the iic device write address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       addr = device_address_7bits << 1
 */
uint8_t iic_read_cmd(uint8_t addr, uint8_t *buf, uint16_t len)
{
    /* send a start */
    a_iic_start();
    
    /* send the read addr */
    a_iic_send_byte(addr + 1);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* read the data */
    while (len != 0)
    {
        /* if the last */
        if (len == 1)
        {
            /* send nack */
            *buf = a_iic_read_byte(0);
        }
        else
        {
            /* send ack */
            *buf = a_iic_read_byte(1); 
        }
        len--;
        buf++;
    }
    
    /* send a stop */
    a_iic_stop(); 
    
    return 0;
}

/**
 * @brief      iic bus read
 * @param[in]  addr is the iic device write address
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       addr = device_address_7bits << 1
 */
uint8_t iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    /* send a start */
    a_iic_start();
    
    /* send the write addr */
    a_iic_send_byte(addr);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send the reg */
    a_iic_send_byte(reg);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send a start */
    a_iic_start();
    
    /* send the read addr */
    a_iic_send_byte(addr + 1);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* read the data */
    while (len != 0)
    {
        /* if the last */
        if (len == 1)
        {
            /* send nack */
            *buf = a_iic_read_byte(0);
        }
        else
        {
            /* send ack */
            *buf = a_iic_read_byte(1);
        }
        len--;
        buf++;
    }
    
    /* send a stop */
    a_iic_stop();
    
    return 0;
}

/**
 * @brief      iic bus read with 16 bits register address 
 * @param[in]  addr is the iic device write address
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       addr = device_address_7bits << 1
 */
uint8_t iic_read_address16(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    /* send a start */
    a_iic_start();
    
    /* send the write addr */
    a_iic_send_byte(addr);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send the reg high part */
    a_iic_send_byte((reg >> 8) & 0xFF);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send the reg low part */
    a_iic_send_byte(reg & 0xFF);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* send a start */
    a_iic_start();
    
    /* send the read addr */
    a_iic_send_byte(addr + 1);
    if (a_iic_wait_ack() != 0)
    {
        a_iic_stop();
        
        return 1;
    }
    
    /* read the data */
    while (len != 0)
    {
        /* if the last */
        if (len == 1)
        {
            /* send nack */
            *buf = a_iic_read_byte(0);
        }
        else
        {
            /* send ack */
            *buf = a_iic_read_byte(1);
        }
        len--;
        buf++;
    }
    
    /* send a stop */
    a_iic_stop();
    
    return 0;
}
