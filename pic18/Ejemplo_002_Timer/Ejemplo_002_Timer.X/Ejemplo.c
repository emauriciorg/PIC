#include "Ejemplo.h"
#include "BBSPI_LCD.h"

void ejemplo(void)
{
  mOPEN_LCD;
  mCURSOR_LINE1;
  LCDPutStr("Ejemplo_002");
  mCURSOR_LINE2;
  LCDPutStr("Timer Servo");

}
