/**
 ******************************************************************************
 * @file     main.c
 * @brief    Checksum and CRC calculation example for AVR
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     This example demonstrates:
 *           - 16-bit checksum calculation over a data buffer
 *           - CRC-8, CRC-16, and CRC-32 with configurable parameters
 *             (polynomial, initial value, input/output reflection, final XOR)
 *           - Showing the results on a 16x2 alphanumeric LCD
 * 
 * @note     CRC-8 and CRC-16 blocks are commented out. Uncomment the block
 *           you want to test (use only one result on LCD row 2 at a time).
 ******************************************************************************
 */

#include "aKaReZa.h"

/* ============================================================================
 *                            GLOBAL VARIABLES
 * ============================================================================ */
uint8_t  dataBuffer[] = {'a', 'K', 'a', 'R', 'e', 'Z', 'a'};
char     alcdBuffer[16];
uint8_t  checkSumValue = 0x00;
uint32_t CRCValue     = 0x00;

/* -------------------------------------------------------
 * @brief CRC configuration handles
 * @note Each handle holds the CRC parameters:
 *       Poly   : generator polynomial
 *       Init   : initial register value
 *       refIn  : reflect each input byte
 *       refOut : reflect the final result
 *       xorOut : value XORed with the final result
 * ------------------------------------------------------- */
hcrc8_T hcrc8;
hcrc16_T hcrc16;
hcrc32_T hcrc32;


/* ============================================================================
 *                             MAIN PROGRAM
 * ============================================================================ */

/* -------------------------------------------------------
 * @brief Application entry point
 * @retval None
 * @note Row 1 of the LCD shows the checksum, row 2 shows the CRC result
 * ------------------------------------------------------- */
int main(void)
{
    /* Initialize the LCD */
    alcd_init();

    /* ------------------------------------------------------
     * 16-bit checksum of the data buffer, shown on row 1
     * ------------------------------------------------------ */
    alcd_clear();
    checkSumValue = checkSum16_Calc(dataBuffer, sizeof(dataBuffer));
    sprintf(alcdBuffer, "CheckSum: 0x%04X", checkSumValue);
    alcd_gotoxy(0, 0);
    alcd_puts(alcdBuffer);


    /* ------------------------------------------------------
     * CRC-8 (optional): poly 0x07, init 0xFF, reflected in/out, no final XOR
     * Uncomment to test; result is shown on row 2
     * ------------------------------------------------------ */
    // hcrc8.Poly   = 0x07;
    // hcrc8.Init   = 0xFF;
    // hcrc8.refIn  = true;
    // hcrc8.refOut = true;
    // hcrc8.xorOut = 0x00;
    // CRCValue = CRC8_Calc(&hcrc8, dataBuffer, sizeof(dataBuffer));
    // sprintf(alcdBuffer, "CRC8: 0x%02X", CRCValue);
    // alcd_gotoxy(0, 1);
    // alcd_puts(alcdBuffer);  


    /* ------------------------------------------------------
     * CRC-16 (optional): poly 0x8005, init 0x0000, reflected in/out, final XOR 0xFFFF
     * Uncomment to test; result is shown on row 2
     * ------------------------------------------------------ */
    // hcrc16.Poly   = 0x8005;
    // hcrc16.Init   = 0x0000;
    // hcrc16.refIn  = true;
    // hcrc16.refOut = true;
    // hcrc16.xorOut = 0xFFFF;
    // CRCValue = CRC16_Calc(&hcrc16, dataBuffer, sizeof(dataBuffer));
    // sprintf(alcdBuffer, "CRC16: 0x%04X", CRCValue);
    // alcd_gotoxy(0, 1);
    // alcd_puts(alcdBuffer);    

    /* ------------------------------------------------------
     * CRC-32 (active): poly 0xA833982B, init 0xFFFFFFFF, reflected in/out,
     * final XOR 0xFFFFFFFF
     * Result is shown on row 2
     * ------------------------------------------------------ */
    hcrc32.Poly   = 0xA833982B;
    hcrc32.Init   = 0xFFFFFFFF;
    hcrc32.refIn  = true;
    hcrc32.refOut = true;
    hcrc32.xorOut = 0xFFFFFFFF;
    CRCValue = CRC32_Calc(&hcrc32, dataBuffer, sizeof(dataBuffer));
    sprintf(alcdBuffer, "CRC32:0x%08lX", CRCValue);
    alcd_gotoxy(0, 1);
    alcd_puts(alcdBuffer);     

    /* Nothing more to do: results stay on the LCD */
    while(1)
    {
        
    };
};