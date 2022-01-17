/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>

int main()
{
    int failed = 0;
    int tested = 0;
    CyGlobalIntEnable;
    UART_Start();
    Pin_Select_Write(1); 
    int x00, x01, x10, x11, x20, x21, x30, x31;
    int y0, y1, y2, y3;
    int out;
    char errorMess[100];
    for(;;)
    {
        if (tested || failed)
        {
            continue;
        }
        Pin_Led_Blue_Write(0);
        UART_UartPutString("Start\r\n");
        CyDelay(2000);
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                Pins_In_1_2_Write(i);
                Pins_In_3_4_Write(j);
                x00 = ((i >> 4) << 1) ^ (i >> 3);
                x01 = ((i >> 3) << 1) ^ (i >> 2);
                x10 = ((i >> 2) << 1) ^ (i >> 1);
                x11 = ((i >> 1) << 1) ^ i;
                x20 = ((j >> 4) << 1) ^ (j >> 3);
                x21 = ((j >> 3) << 1) ^ (j >> 2);
                x30 = ((j >> 2) << 1) ^ (j >> 1);
                x31 = ((j >> 1) << 1) ^ j;
                
                Pin_Select_Write(0);
                out = Pins_Out_Read();
                y0 = ((out >> 4) << 1) ^ (out >> 3);
                y1 = ((out >> 3) << 1) ^ (out >> 2);
                y2 = ((out >> 2) << 1) ^ (out >> 1);
                y3 = ((out >> 1) << 1) ^ out;
                if (y0 != x00 || y1 != x10 || y2 != x20 || y3 != x30)
                {
                    UART_UartPutString("ERROR\r\n");
                    sprintf(errorMess, "0 %d %d %d %d %d %d\r\n", i, j, y0, y1, y2, y3);
                    UART_UartPutString(errorMess);
                    Pin_Led_Blue_Write(1);
                    Pin_Led_Red_Write(0);
                    failed = 1;
                    break;
                }
                
                Pin_Select_Write(1);
                out = Pins_Out_Read();
                y0 = ((out >> 4) << 1) ^ (out >> 3);
                y1 = ((out >> 3) << 1) ^ (out >> 2);
                y2 = ((out >> 2) << 1) ^ (out >> 1);
                y3 = ((out >> 1) << 1) ^ out;
                if (y0 != x01 || y1 != x11 || y2 != x21 || y3 != x31)
                {
                    UART_UartPutString("ERROR\r\n");
                    sprintf(errorMess, "1 %d %d %d %d %d %d\r\n", i, j, y0, y1, y2, y3);
                    UART_UartPutString(errorMess);
                    Pin_Led_Blue_Write(1);
                    Pin_Led_Red_Write(0);
                    failed = 1;
                    break;
                }
            }
            if (failed)
            {
                break;
            }
        }
        if (failed)
        {
            continue;
        }
        tested = 1;
        Pin_Led_Blue_Write(1);
        Pin_Led_Green_Write(0);
        UART_UartPutString("End\r\n");
        
    }
}


/* [] END OF FILE */
