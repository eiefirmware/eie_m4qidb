/***********************************************************************************************************************
File: utilities.h
***********************************************************************************************************************/

#ifndef __UTILITIES_H
#define __UTILITIES_H

/***********************************************************************************************************************
Type Definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Constants / Definitions
***********************************************************************************************************************/
#define NUMBER_ASCII_TO_DEC     (u8)48        /* Difference between ASCII character 0-9 and the value 0-9 */
#define UPPERCASE_ASCII_TO_DEC  (u8)55        /* Difference between ASCII character A-F and the value 10-15 */
#define LOWERCASE_ASCII_TO_DEC  (u8)87        /* Difference between ASCII character a-f and the value 10-15 */

#define ASCII_CARRIAGE_RETURN   (u8)0x0D      /* ASCII CR char \r */
#define ASCII_LINEFEED          (u8)0x0A      /* ASCII LF char \n */
#define ASCII_BACKSPACE         (u8)0x08      /* ASCII Backspace char */

#define RESET_TARGET_TIMER      (u8)0x1       /* Switch for IsTimeUp to reset the reference timer */
#define NO_RESET_TARGET_TIMER   (u8)0x0       /* Switch for IsTimeUp to not reset the reference timer */

#define MESSAGE_OK              "OK\r\n"
#define MESSAGE_OK_SIZE         (u8)sizeof(MESSAGE_OK)

#define MESSAGE_FAIL            "FAIL\r\n"
#define MESSAGE_FAIL_SIZE       (u8)sizeof(MESSAGE_FAIL)


/***********************************************************************************************************************
* Function Declarations
***********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions */
/*--------------------------------------------------------------------------------------------------------------------*/
bool IsTimeUp(volatile u32 *u32CurrentTick_, u32 *pu32SavedTick_, u32 u32Period_, u8 u8TimerResetSwitch_);
u8 ASCIIHexCharToChar(u8);
u8 HexToASCIICharUpper(u8 u8Char_);
u8 HexToASCIICharLower(u8 u8Char_);
bool SearchString(u8* pu8TargetString_, u8* pu8MatchString_);
u8 NumberToAscii(int u32Number_, u8* pu8AsciiString_, u8 u8Decimals, bool isSigned);



/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions */
/*--------------------------------------------------------------------------------------------------------------------*/


#endif /* __UTILITIES_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/
