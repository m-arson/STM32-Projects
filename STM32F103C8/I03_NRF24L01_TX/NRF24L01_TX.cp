#line 1 "C:/Users/armst/Desktop/STM32F103C8T6/MikroC/I03_NRF24L01_TX/NRF24L01_TX.c"
#line 1 "c:/users/armst/desktop/stm32f103c8t6/mikroc/i03_nrf24l01_tx/nrf24l01_tx.h"
#line 122 "c:/users/armst/desktop/stm32f103c8t6/mikroc/i03_nrf24l01_tx/nrf24l01_tx.h"
char init_Radio();
void sendBuffer();
char readBuffer();
void makeMsg(char* msg);
char Get_FIFO_Flags();
char *getConst(char dest[], const char source[]);
char Get_Status();
void toggleCSN();
void Clear_Data(char dat[]);
#line 20 "C:/Users/armst/Desktop/STM32F103C8T6/MikroC/I03_NRF24L01_TX/NRF24L01_TX.c"
extern char Data_In[21];
extern char Data_Out[21];
extern char stat;
extern short dataLength = 20;

sbit Irq_pin at GPIOB_ODR.B13; sfr;
sbit Ce_pin at GPIOB_ODR.B15; sfr;
sbit Csn_pin at GPIOB_ODR.B14; sfr;






const char adr0[] = {0x78,0x78,0x78,0x78,0x78};
const char adr1[] = {0xf1,0xb4,0xb5,0xb6,0xb3};
const char adr2[] = {0xb3,0xb4,0xb5,0xb6,0xb3};
const char adr3[] = {0x83,0xb4,0xb5,0xb6,0xb3};
const char adr4[] = {0xcf,0xb4,0xb5,0xb6,0xb3};
const char adr5[] = {0x75,0xb4,0xb5,0xb6,0xb3};


void Clear_Data(char dat[])
{
 char i;
 for(i=0;i<dataLength;i++)dat[i] = ' ';
}

void toggleCSN()
{
 Csn_pin = 1;
 Delay_us(20);
 Csn_pin = 0;
 Delay_us(10);
}

char Get_Status()
{
 char s;
 Ce_pin = 0;
 toggleCSN();
 SPI1_Write( 0x07 );
 Delay_us(10);
 s = SPI1_Read( 0xFF );
 Delay_us(10);
 Csn_pin = 1;
 return s;
}

char *getConst(char dest[], const char source[])
{
 int i = 0;
 while (source[i])
 {dest[i] = source[i]; i++;}
 dest[i] = '\0';
 return dest;
}

char Get_FIFO_Flags()
{
 char s;
 Ce_pin = 0;
 toggleCSN();
 SPI1_Write( 0x17 );
 Delay_us(10);
 s = SPI1_Read( 0xFF );
 Delay_us(10);
 Csn_pin = 1;
 return s;
}

void makeMsg(char* msg)
{
 Clear_Data(Data_Out);
 getConst(Data_Out, msg);
}

char readBuffer()
{
 char i, s;
 Ce_pin = 0;
 Clear_Data(Data_In);
 s = Get_FIFO_Flags();
 if((s & 2) != 0){
 toggleCSN();
 SPI1_Write( 0x61 );
 for(i=0; i < dataLength; i++){Delay_us(10); Data_In[i] = SPI1_Read(0);}
 Delay_us(10);
 }
 Csn_pin = 1;
 Ce_pin = 1;
 return s;
}

void sendBuffer()
{
 char i, j;
 do{
 toggleCSN();
 SPI1_Write( 0x07  |  0x20 );
 Delay_us(10);
 SPI1_Write(0xff);
 Delay_us(10);
 toggleCSN();
 SPI1_Write( 0xE1 );
 Delay_us(10);
 toggleCSN();
 SPI1_Write( 0xA0 );
 for(i = 0; i < dataLength; i++) {Delay_us(10); SPI1_Write(Data_Out[i]);}
 Delay_us(10);
 Csn_pin = 1;
 Ce_pin = 1;
 Delay_ms(10);
 j = (Get_Status() & 0x20);
 }while(j==0);
}

char init_Radio()
{
 char i;
 Ce_pin = 0;
 Delay_us(10);
 toggleCSN();
 SPI1_Write( 0x00  |  0x20 );
 Delay_us(10);
#line 163 "C:/Users/armst/Desktop/STM32F103C8T6/MikroC/I03_NRF24L01_TX/NRF24L01_TX.c"
 SPI1_Write( 0x02  +  0x04  +  0x08 );
 Delay_us(10);

 toggleCSN();
 SPI1_Write( 0x01  |  0x20 );
 Delay_us(10);
 SPI1_Write( 0x01 );
 Delay_us(10);

 toggleCSN();
 SPI1_Write( 0x02  |  0x20 );
 Delay_us(10);
 SPI1_Write( 0x01 );
 Delay_us(10);

 toggleCSN();
 SPI1_Write( 0x0A  |  0x20 );
 for(i=0;i<5;i++){Delay_us(10); SPI1_Write(adr0[i]);}
 Delay_us(10);

 toggleCSN();
 SPI1_Write( 0x10  |  0x20 );
 for(i=0;i<5;i++){Delay_us(10); SPI1_Write(adr0[i]);}
 Delay_us(10);


 toggleCSN();
 SPI1_Write( 0x03  |  0x20 );
 Delay_us(10);
 SPI1_Write( 0x03 );
 Delay_us(10);

 toggleCSN();
 SPI1_Write( 0x04  |  0x20 );
 Delay_us(10);
 SPI1_Write(0xfaf);
 Delay_us(10);

 toggleCSN();
 SPI1_Write( 0x05  |  0x20 );
 Delay_us(10);
 SPI1_Write(83);
 Delay_us(10);

 toggleCSN();
 SPI1_Write( 0x06  |  0x20 );
 Delay_us(10);
 SPI1_Write( 0x06  +  0x01 );
 Delay_us(10);
#line 280 "C:/Users/armst/Desktop/STM32F103C8T6/MikroC/I03_NRF24L01_TX/NRF24L01_TX.c"
 toggleCSN();
 SPI1_Write( 0x11  |  0x20 );
 Delay_us(10);
 SPI1_Write(dataLength);
 Delay_us(10);

 Csn_pin = 1;
 i = Get_Status();
 return i;
}
