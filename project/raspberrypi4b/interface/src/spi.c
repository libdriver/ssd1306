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
 * @file      spi.c
 * @brief     spi source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-02-12
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/12  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "spi.h"

/**
 * @brief      spi bus init
 * @param[in]  *name points to a spi device name buffer
 * @param[out] *fd points to a spi device handle buffer
 * @param[in]  mode is the spi mode.
 * @param[in]  freq is the spi running frequence
 * @return     status code
 *             - 0 success
 *             - 1 init failed
 * @note       none
 */
uint8_t spi_init(char *name, int *fd, spi_mode_type_t mode, uint32_t freq)
{
    int i;

    *fd = open (name, O_RDWR);                                       /* open spi device */
    if ((*fd) < 0)                                                   /* check result */
    {
        perror("spi: open failed.\n");                               /* open failed */
     
        return 1;                                                    /* return error */
    }
    else
    {
        i = mode;                                                    /* set mode */
        if (ioctl(*fd, SPI_IOC_WR_MODE, &i) < 0)                     /* config write mode */
        {
            perror("spi: write mode set failed.\n");                 /* write mode set failed */
     
            return 1;                                                /* return error */
        }
        if (ioctl(*fd, SPI_IOC_RD_MODE, &i) < 0)                     /* config read mode */
        {
            perror("spi: read mode set failed.\n");                  /* read mode set failed */
     
            return 1;                                                /* return error */
        }
        i = freq;                                                    /* set spi frequence */
        if (ioctl(*fd, SPI_IOC_WR_MAX_SPEED_HZ, &i) < 0)             /* set write max frequence */
        {
            perror("spi: set spi write speed failed.\n");            /* set spi write speed failed */
     
            return 1;                                                /* return error */
        }  
        if (ioctl(*fd, SPI_IOC_RD_MAX_SPEED_HZ, &i) < 0)             /* set read max frequence */
        {
            perror("spi: set spi read speed failed.\n");             /* set spi read speed failed */
     
            return 1;                                                /* return error */
        }  
        i = 0;
        if (ioctl(*fd, SPI_IOC_WR_LSB_FIRST, &i) < 0)                /* set write MSB first */
        {
            perror("spi: set spi write msb first failed.\n");        /* set spi write msb first failed */
     
            return 1;                                                /* return error */
        } 
        if (ioctl(*fd, SPI_IOC_RD_LSB_FIRST, &i) < 0)                /* set read MSB first */
        {
            perror("spi: set spi read msb first failed.\n");         /* set spi read msb first failed */
     
            return 1;                                                /* return error */
        } 
        i = 8;                                                       /* set 8 bits */
        if (ioctl(*fd, SPI_IOC_WR_BITS_PER_WORD, &i) < 0)            /* set write bits */
        {
            perror("spi: set spi wirte 8 bit failed.\n");            /* set spi wirte 8 bit failed */
     
            return 1;                                                /* return error */
        } 
        if (ioctl(*fd, SPI_IOC_RD_BITS_PER_WORD, &i) < 0)            /* set read bits */
        {
            perror("spi: set spi read 8 bit failed.\n");             /* set spi read 8 bit failed */
     
            return 1;                                                /* return error */
        } 

        return 0;                                                    /* success return 0 */
    }
}

/**
 * @brief     spi bus deinit
 * @param[in] fd is the spi device handle
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 * @note      none
 */
uint8_t spi_deinit(int fd)
{
    if (close(fd) < 0)                                  /* close spi */
    {
        perror("spi: close failed.\n");                 /* close failed */
     
        return 1;                                       /* return error */
    }
    else
    {
        return 0;                                       /* success return 0 */
    }
}

/**
 * @brief      spi bus read command
 * @param[in]  fd is the spi handle
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t spi_read_cmd(int fd, uint8_t *buf, uint16_t len)
{
    struct spi_ioc_transfer k;
    int l;

    memset(&k, 0, sizeof(struct spi_ioc_transfer));        /* clear ioc transfer */
    k.rx_buf = (unsigned long) buf;                        /* set rx buffer */
    k.len = len;                                           /* set rx length */
    k.cs_change = 0;                                       /* set cs change */
    l = ioctl(fd, SPI_IOC_MESSAGE(1), &k);                 /* send data */
    if (l != len)                                          /* check length */
    {
        perror("spi: length check error.\n");              /* length check error */

        return 1;                                          /* return error */
    }

    return 0;                                              /* success return 0 */
}

/**
 * @brief      spi bus read
 * @param[in]  fd is the spi handle
 * @param[in]  reg is spi register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t spi_read(int fd, uint8_t reg, uint8_t *buf, uint16_t len)
{
    struct spi_ioc_transfer k;
    uint8_t command[len + 1];
    uint8_t recv[len + 1];
    int l;

    command[0] = reg;                                      /* set reg */
    memset(&command[1], 0x00, len);                        /* clear the rest */
    memset(&k, 0, sizeof(struct spi_ioc_transfer));        /* clear ioc transfer */
    k.tx_buf = (unsigned long) command;                    /* set command buffer */
    k.rx_buf = (unsigned long) recv;                       /* set recv buffer */
    k.len = len + 1;                                       /* set written length */
    k.cs_change = 0;                                       /* enable cs change */
    l = ioctl(fd, SPI_IOC_MESSAGE(1), &k);                 /* send data */
    if (l != k.len)                                        /* check length */
    {
        perror("spi: length check error.\n");              /* length check error */

        return 1;                                          /* return error */
    }
    memcpy(buf, recv + 1, len);                            /* copy data */

    return 0;                                              /* success return 0 */
}

/**
 * @brief     spi bus write command
 * @param[in] fd is the spi handle
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t spi_write_cmd(int fd, uint8_t *buf, uint16_t len)
{
    struct spi_ioc_transfer k;
    int l;

    memset(&k, 0, sizeof(k));                         /* clear ioc transfer */
    k.tx_buf = (unsigned long) buf;                   /* set tx buffer */
    k.len = len;                                      /* set tx length */
    k.cs_change = 0;                                  /* set cs change */
    l = ioctl(fd, SPI_IOC_MESSAGE(1), &k);            /* send data */
    if (l != len)                                     /* check length */
    {
        perror("spi: length check error.\n");         /* length check error */

        return 1;                                     /* return error */
    }

    return 0;                                         /* success return 0 */
}

/**
 * @brief     spi bus write
 * @param[in] fd is the spi handle
 * @param[in] reg is spi register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t spi_write(int fd, uint8_t reg, uint8_t *buf, uint16_t len)
{
    struct spi_ioc_transfer k;
    uint8_t command[len + 1];
    int l;

    command[0] = reg;                                      /* set reg */
    memcpy(&command[1], buf, len);                         /* set the rest */
    memset(&k, 0, sizeof(struct spi_ioc_transfer));        /* clear ioc transfer */
    k.tx_buf = (unsigned long) command;                    /* set command buffer */
    k.len = len + 1;                                       /* set written length */
    k.cs_change = 0;                                       /* enable cs change */
    l = ioctl(fd, SPI_IOC_MESSAGE(1), &k);                 /* send data */
    if (l != k.len)                                        /* check length */
    {
        perror("spi: length check error.\n");              /* length check error */

        return 1;                                          /* return error */
    }

    return 0;                                              /* success return 0 */
}
