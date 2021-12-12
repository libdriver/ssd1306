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
 * @date      2021-2-12
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/12  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include <iic.h>

/**
 * @brief      iic bus init
 * @param[in]  *name points to a iic device name buffer
 * @param[out] *fd points to a iic device handle buffer
 * @return     status code
 *             - 0 success
 *             - 1 init failed
 * @note       none
 */
uint8_t iic_init(char *name, int *fd)
{    
    *fd = open (name, O_RDWR);                /* open iic */
    
    if ((*fd) < 0)                            /* check error */
    {
        perror("iic: open failed.\n");        /* open failed */
     
        return 1;                             /* return error */
    }
    else
    {
        return 0;                             /* success return 0 */
    }
}

/**
 * @brief     iic bus deinit
 * @param[in] fd is the iic handle
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 * @note      none
 */
uint8_t iic_deinit(int fd)
{
    if (close(fd) < 0)                         /* close iic */
    {
        perror("iic: close failed.\n");        /* close failed */
     
        return 1;                              /* return error */
    }
    else
    {
        return 0;                              /* success return 0 */
    }
}

/**
 * @brief      iic bus read command
 * @param[in]  fd is the iic handle
 * @param[in]  addr is iic device write address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t iic_read_cmd(int fd, uint8_t addr, uint8_t *buf, uint16_t len)
{
    struct i2c_rdwr_ioctl_data i2c_rdwr_data;
    struct i2c_msg msgs[1];
    
    memset(&i2c_rdwr_data, 0, sizeof(struct i2c_rdwr_ioctl_data));        /* clear ioctl data */
    memset(msgs, 0, sizeof(struct i2c_msg) * 1);                          /* clear msgs data */

    msgs[0].addr = addr >> 1;                                             /* set iic addr */
    msgs[0].flags = I2C_M_RD;                                             /* set read command */
    msgs[0].buf = buf;                                                    /* set read buf */
    msgs[0].len = len;                                                    /* set read length */
    i2c_rdwr_data.msgs = msgs;                                            /* set msgs */
    i2c_rdwr_data.nmsgs = 1;                                              /* set msgs 1 */
    
    if (ioctl(fd, I2C_RDWR, &i2c_rdwr_data) < 0)                          /* read write command */
    {
        perror("iic: read failed.\n");                                    /* read failed */
     
        return 1;                                                         /* return error */
    }
     
    return 0;                                                             /* success return 0 */
}

/**
 * @brief     iic bus write command
 * @param[in] fd is the iic handle
 * @param[in] addr is iic device write address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t iic_write_cmd(int fd, uint8_t addr, uint8_t *buf, uint16_t len)
{
    struct i2c_rdwr_ioctl_data i2c_rdwr_data;
    struct i2c_msg msgs[1];
    
    memset(&i2c_rdwr_data, 0, sizeof(struct i2c_rdwr_ioctl_data));        /* clear ioctl data */
    memset(msgs, 0, sizeof(struct i2c_msg) * 1);                          /* clear msgs data */

    msgs[0].addr = addr >> 1;                                             /* set iic addr */
    msgs[0].flags = 0;                                                    /* set write command */
    msgs[0].buf = buf;                                                    /* set write buf */
    msgs[0].len = len;                                                    /* set write length */
    i2c_rdwr_data.msgs = msgs;                                            /* set msgs */
    i2c_rdwr_data.nmsgs = 1;                                              /* set msgs 1 */
    
    if (ioctl(fd, I2C_RDWR, &i2c_rdwr_data) < 0)                          /* read write command */
    {
        perror("iic: write failed.\n");                                   /* write failed */
     
        return 1;                                                         /* return error */
    }
     
    return 0;                                                             /* success return 0 */
}

/**
 * @brief      iic bus read
 * @param[in]  fd is the iic handle
 * @param[in]  addr is iic device write address
 * @param[in]  reg is iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t iic_read(int fd, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    struct i2c_rdwr_ioctl_data i2c_rdwr_data;
    struct i2c_msg msgs[2];
    
    memset(&i2c_rdwr_data, 0, sizeof(struct i2c_rdwr_ioctl_data));        /* clear ioctl data */
    memset(msgs, 0, sizeof(struct i2c_msg) * 2);                          /* clear msgs data */

    msgs[0].addr = addr >> 1;                                             /* set iic addr */
    msgs[0].flags = 0;                                                    /* set write command */
    msgs[0].buf = &reg;                                                   /* set reg address */
    msgs[0].len = 1;                                                      /* set len 1 */
    msgs[1].addr = addr >> 1;                                             /* set iic addr */
    msgs[1].flags = I2C_M_RD;                                             /* set read command */
    msgs[1].buf = buf;                                                    /* set read buf */
    msgs[1].len = len;                                                    /* set read length */
    i2c_rdwr_data.msgs = msgs;                                            /* set msgs */
    i2c_rdwr_data.nmsgs = 2;                                              /* set msgs 2 */
    
    if (ioctl(fd, I2C_RDWR, &i2c_rdwr_data) < 0)                          /* read write command */
    {
        perror("iic: read failed.\n");                                    /* read failed */
     
        return 1;                                                         /* return error */
    }
     
    return 0;                                                             /* success return 0 */
}

/**
 * @brief      iic bus read with 16 bits register address
 * @param[in]  fd is the iic handle
 * @param[in]  addr is iic device write address
 * @param[in]  reg is iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t iic_read_address16(int fd, uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    struct i2c_rdwr_ioctl_data i2c_rdwr_data;
    struct i2c_msg msgs[2];
    uint8_t addr_buf[2];
    
    memset(&i2c_rdwr_data, 0, sizeof(struct i2c_rdwr_ioctl_data));        /* clear ioctl data */
    memset(msgs, 0, sizeof(struct i2c_msg) * 2);                          /* clear msgs data */

    msgs[0].addr = addr >> 1;                                             /* set iic addr */
    msgs[0].flags = 0;                                                    /* set write command */
    addr_buf[0] = (reg >> 8) & 0xFF;                                      /* set MSB */
    addr_buf[1] = (reg >> 0) & 0xFF;                                      /* set LSB */
    msgs[0].buf = addr_buf;                                               /* set reg address */
    msgs[0].len = 2;                                                      /* set len 2 */
    msgs[1].addr = addr >> 1;                                             /* set iic addr */
    msgs[1].flags = I2C_M_RD;                                             /* set read command */
    msgs[1].buf = buf;                                                    /* set read buf */
    msgs[1].len = len;                                                    /* set read length */
    i2c_rdwr_data.msgs = msgs;                                            /* set msgs */
    i2c_rdwr_data.nmsgs = 2;                                              /* set msgs 2 */
    
    if (ioctl(fd, I2C_RDWR, &i2c_rdwr_data) < 0)                          /* read write command */
    {
        perror("iic: read failed.\n");                                    /* read failed */
     
        return 1;                                                         /* return error */
    }
     
    return 0;                                                             /* success return 0 */
}

/**
 * @brief     iic bus write with 16 bits register address
 * @param[in] fd is the iic handle
 * @param[in] addr is iic device write address
 * @param[in] reg is iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t iic_write_address16(int fd, uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len)
{
    struct i2c_rdwr_ioctl_data i2c_rdwr_data;
    struct i2c_msg msgs[1];
    uint8_t buf_send[len + 2];
    
    memset(&i2c_rdwr_data, 0, sizeof(struct i2c_rdwr_ioctl_data));        /* clear ioctl data */
    memset(msgs, 0, sizeof(struct i2c_msg) * 1);                          /* clear msgs data */
    memset(buf_send, 0, sizeof(uint8_t) * (len + 2));                     /* clear sent buf */

    msgs[0].addr = addr >> 1;                                             /* set device address */
    msgs[0].flags = 0;                                                    /* set write command */
    buf_send[0] = (reg >> 8) & 0xFF;                                      /* set reg MSB */
    buf_send[1] = (reg >> 0) & 0xFF;                                      /* set reg LSB */
    memcpy(&buf_send[2], buf, len);                                       /* copy data */
    msgs[0].buf = buf_send;                                               /* set sent buffer */
    msgs[0].len = len + 2;                                                /* set sent length */
    i2c_rdwr_data.msgs = msgs;                                            /* set msg */
    i2c_rdwr_data.nmsgs = 1;                                              /* set msg number 1 */
    
    if (ioctl(fd, I2C_RDWR, &i2c_rdwr_data) < 0)                          /* read write command */
    {
        perror("iic: write failed.\n");                                   /* write failed */
        
        return 1;                                                         /* return error */
    }
     
    return 0;                                                             /* success return 0 */
}

/**
 * @brief     iic bus write
 * @param[in] fd is the iic handle
 * @param[in] addr is iic device write address
 * @param[in] reg is iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t iic_write(int fd, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    struct i2c_rdwr_ioctl_data i2c_rdwr_data;
    struct i2c_msg msgs[1];
    uint8_t buf_send[len + 1];
    
    memset(&i2c_rdwr_data, 0, sizeof(struct i2c_rdwr_ioctl_data));        /* clear ioctl data */
    memset(msgs, 0, sizeof(struct i2c_msg) * 1);                          /* clear msgs data */
    memset(buf_send, 0, sizeof(uint8_t) * (len + 1));                     /* clear sent buf */

    msgs[0].addr = addr >> 1;                                             /* set device address */
    msgs[0].flags = 0;                                                    /* set write command */
    buf_send[0] = reg;                                                    /* set reg */
    memcpy(&buf_send[1], buf, len);                                       /* copy data */
    msgs[0].buf = buf_send;                                               /* set sent buffer */
    msgs[0].len = len + 1;                                                /* set sent length */
    i2c_rdwr_data.msgs = msgs;                                            /* set msg */
    i2c_rdwr_data.nmsgs = 1;                                              /* set msg number 1 */
    
    if (ioctl(fd, I2C_RDWR, &i2c_rdwr_data) < 0)                          /* read write command */
    {
        perror("iic: write failed.\n");                                   /* write failed */
        
        return 1;                                                         /* return error */
    }
     
    return 0;                                                             /* success return 0 */
}
