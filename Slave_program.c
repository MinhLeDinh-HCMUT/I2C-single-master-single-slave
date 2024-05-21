/*
 * File:   Slave_program.c
 * Author: MinhLeDinh
 */

#include <xc.h>
#define _XTAL_FREQ 4000000 
int charcount=0,index=0;
char str[10];
short clearBuffer;
int datareturn[6]={53,54,46,0,0,13};

void I2C_Slave_Init(unsigned char address)
{
    SSPADD = address; 
    SSPSTAT = 0x80;
    SSPCON = 0x36;
    SSPCON2 = 0x01;
    TRISC3 = 1; 
    TRISC4 = 1; 
    GIE = 1;    
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1;
}

void UART_init(void)    // Use for display data to virtual terminal, remove if not use
{
    BRGH=1;
    SPBRG=25;   // Baudrate 9600 bps
    SYNC=0;
    SPEN=1;
    TRISC6=1;   
    TXEN=1;     // Transmit enabled 
}
 
void UART_write_c(char data)
{
    while(!TRMT);
    TXREG = data;
}
 
void main(void)
{
    I2C_Slave_Init(0x40); // I2C address
    UART_init();
    while(1)
    {
    }
    return;
}

void __interrupt() I2C_Slave()
{ 
    if(SSPIF == 1)
    {
        SSPCONbits.CKP=0;
        if((SSPCONbits.SSPOV)||(SSPCONbits.WCOL))
        {
            clearBuffer = SSPBUF;     // Clear buffer
            SSPCONbits.SSPOV = 0;     // Clear overflow flag
            SSPCONbits.WCOL = 0;      // Clear collision bit
            SSPCONbits.CKP = 1;
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) 
        {
            clearBuffer = SSPBUF;
            while(!BF);
            str[charcount] = SSPBUF;   // Receive data from buffer
            UART_write_c(str[charcount]);      // Print data to virtual terminal
            charcount+=1;
            if(charcount==6) charcount=0; 
            SSPCONbits.CKP = 1;
        }   
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
        {
            clearBuffer = SSPBUF;
            BF = 0;
            if((index==3)||(index==4)) datareturn[index]=str[index];   // Change two last digits same the received data from master
            SSPBUF = datareturn[index];    // Give data to the buffer
            index+=1;
            if(index==6) index=0;         
            SSPCONbits.CKP = 1;
            while(SSPSTATbits.BF);
        }
            SSPIF = 0;
    }
}

