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
 * @file      client.c
 * @brief     client source file
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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                              /**< uart buffer */
volatile uint16_t g_len;                         /**< uart buffer length */
static int gs_sock_fd;                           /**< network handle */
static int gs_conn_fd;                           /**< network handle */
static struct sockaddr_in gs_server_addr;        /**< server address */

/**
 * @brief main function
 * @note  none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t *p;
    
    /* creat a socket */
    gs_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (gs_sock_fd < 0) 
    {
        printf("ssd1306: creat socket failed.\n");
       
        return 1;
    }
    
    /* set connect port */
    memset(&gs_server_addr,0,sizeof(gs_server_addr));
    gs_server_addr.sin_family = AF_INET;
    gs_server_addr.sin_port = htons(6666);
    
    /* set the server address */
    if (inet_pton(AF_INET, "127.0.0.1", &gs_server_addr.sin_addr) < 0) 
    {
        printf("ssd1306: set address failed.\n");
        (void)close(gs_sock_fd);

        return 1;
    }
    
    /* connect to the server */
    if (connect(gs_sock_fd, (struct sockaddr*)&gs_server_addr, sizeof(gs_server_addr)) <0) 
    {
        printf("ssd1306: connect failed.\n");
        (void)close(gs_sock_fd);

        return 1;
    }
    
    /* cat the full command */
    memset(g_buf, 0, 256);
    for (int i = 0; i < argc; i++)
    {
        strcat(g_buf, argv[i]);
        strcat(g_buf, " ");
    }
    
    /* adjust the command */
    g_len = strlen(g_buf);
    if (strstr(g_buf, "./") != NULL)
    {
        g_len -= 2;
        p = g_buf + 2;
    }
    else
    {
        p = g_buf;
    }
    
    /* output */
    printf("ssd1306: send %s\n", p);
    
    /* send data */
    if (send(gs_sock_fd, p, g_len, 0) <0) 
    {
        printf("ssd1306: send failed.\n");
        (void)close(gs_sock_fd);

        return 1;
    }
    
    /* close the socket */
    (void)close(gs_sock_fd);
    
    return 0;
}
