#include "lcd_api.h"

void lcd_start_message(void)
{
	mOPEN_LCD;
	mCURSOR_LINE1;
	LCDPutStr("Ejemplo_000");
	mCURSOR_LINE2;
	LCDPutStr("Blinking Led");
}
