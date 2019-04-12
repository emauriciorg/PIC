#ifndef _SPI_H_
#define _SPI_H_
#include <stdint.h>
void spi_setup(void);
void spi_send_command(uint16_t my_data);
void spi_read();
void matrix_led_shutdown_mode(void);
void matrix_display_test(void);

#endif /*_SPI_H_*/
