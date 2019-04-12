#include "spi.h"
#include <stdio.h>

#include <xc.h>
#include <plib.h>
#include "hw_profile.h"

#define SPI_DEBUG_ACTIVE
#ifdef SPI_DEBUG_ACTIVE
	#define SPI_OUT(...)  printf(__VA_ARGS__)
#else
	#define SPI_OUT(...)
#endif

enum{
	NOP = 0,
	
	DIGIT_0,
	DIGIT_1,
	DIGIT_2,
	DIGIT_3,
	DIGIT_4,
	DIGIT_5,
	DIGIT_6,
	DIGIT_7,

	DECODE_MODE,
	INTENSITY,
	SCAN_LIMIT,
	SHUTDOWN,
	DISPLAY_TEST,
}matrix_led_reg_addr;

typedef union {
	struct{
		uint8_t data15:1,
			data14:1,
			data13:1,
			data12:1,
			address:4;
	
		uint8_t data;
	}format;
	uint16_t raw_data;
}matrix_led_t;

matrix_led_t red_matrix;

static void spi_set_baudrate(uint16_t baudrate);

void spi_set_row(uint8_t row, uint8_t column){
	red_matrix.format.address = row;
	red_matrix.format.data = column;
	spi_send_command (red_matrix.raw_data);	
}
void matrix_display_test(void){
	red_matrix.format.address = DISPLAY_TEST;
	red_matrix.format.data = 0;
	spi_send_command (red_matrix.raw_data);

}
void matrix_led_shutdown_mode(void)
{
	red_matrix.format.address = SHUTDOWN;
	red_matrix.format.data = 0;
	spi_send_command (red_matrix.raw_data);

}
#if 0

int rData;
IEC0CLR=0x03800000; // disable all interrupts
SPI1CON = 0; // Stops and resets the SPI1.
rData=SPI1BUF; // clears the receive buffer
IFS0CLR=0x03800000; // clear any existing event
IPC5CLR=0x1f000000; // clear the priority
IPC5SET=0x0d000000; // Set IPL=3, Subpriority 1
IEC0SET=0x03800000; // Enable Rx, Tx and Error interrupts
SPI1BRG=0x1; // use F PB /4 clock frequency
SPI1STATCLR=0x40; // clear the Overflow
SPI1CON=0x8220; // SPI ON, 8 bits transfer, SMP=1, Master mode
// from now on, the device is ready to transmit and receive
data
SPI1BUF=’A’; // transmit an A character

#endif


void spi_setup(void){

	SPI2CON = 0;
	SPI2CONbits.ON = 0;
	spi_set_baudrate(100);
	SPI2CONbits.FRMEN = 0 ;
	//SPI2CONbits.FRZ = 0 ;
	SPI2CONbits.SIDL = 0;
	//SPI2CONbits.SDO = 0;
	SPI2CONbits.MODE16 = 1; /* 16 bit mode*/
	SPI2CONbits.SMP = 1;

	SPI2CONbits.CKE = 0;
	SPI2CONbits.CKP = 0;
	SPI2CONbits.SSEN = 1;
	SPI2CONbits.MSTEN = 1;
	/*
	SPI2CONCLR =
	SPI2CONSET =
	SPI2CONINV =
	SPI2STAT =
	SPI2STATCLR =
	SPI2BUF =
	SPI2BRG =
	SPI2BRGCLR = 
	SPI2BRGSET =
	SPI2BRGINV =
	*/

	while( SPI2STATbits.SPIBUSY);
	if (SPI2STATbits.SPIRBF){
		/*Data received*/
	}

	SPI2CONbits.ON = 1 ;
}
/*
	Baudrate = Fpb / ( 2 * SPIxBRG + 1 )
	BRG = (PBclk/(SPIclk*2))-1
 */
void spi_set_baudrate(uint16_t baudrate){
	
	SPI2BRG =479; /*100k*/

}



void spi_send_command(uint16_t my_data)
{
//	while( SPI2STATbits.SPIBUSY);
	if  (SPI2STATbits.SPITBE){
		SPI2BUF = my_data;
		SPI_OUT("SPI data was send! \n");
	}
	SPI_OUT("SPI not ready\n");
}
