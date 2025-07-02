#ifndef HLCD_Interface_H
#define HLCD_Interface_H

void HLCD_void_Init(void);
void HLCD_voidLcdWriteCmd(u8 Copy_u8Cmd);
void HLCD_voidWriteChar(u8 Copy_u8Char);
u8 HLCD_SetCursor(u8 Copy_LineNb,u8 Copy_CharNb);
void HLCD_WriteStirng(const u8 *Copy_u8PtrString);
void HLCD_CLEAR(void);
void HLCD_voidWriteNumbers(u16 Copy_u16Number);

void HLCD_voidSendExtraChar(u8 Copy_LineNb,u8 Copy_CharNb);

void HLCD_voidSendExtraChar2(u8 Copy_LineNb,u8 Copy_CharNb,u8 * Copy_pointer);
void HLCD_voidWriteFloat(float number);


#define HLCD_Line1     1
#define HLCD_Line2     2
#define HLCD_Clear     0x01
#define HLCD_CGRAM     0x40
#endif
