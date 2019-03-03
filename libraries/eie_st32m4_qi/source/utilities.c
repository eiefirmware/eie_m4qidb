/***********************************************************************************************************************
File: utilities.c

Description:
Various useful functions.
***********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Util_" and be declared as static.
***********************************************************************************************************************/


/***********************************************************************************************************************
Function Definitions
***********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
/* Public Functions */
/*--------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------/
Function: ASCIIHexCharToChar

Description:
Determines the numerical value of a hexidecimal ASCII char of that number
('0' - 'F' or '0' - 'f' -> 0 - 15).

Requires:
  - Standard ASCII table is in use

Promises:
  - If valid 0-9, A-F or a-f, returns the numerical value of the ASCII char
  - Otherwise returns 0xff
*/
u8 ASCIIHexCharToChar(u8 u8Char_)
{
  if( (u8Char_ >= '0') && (u8Char_ <= '9') )
    return(u8Char_ - NUMBER_ASCII_TO_DEC);

  if( (u8Char_ >= 'A') && (u8Char_ <= 'F') )
    return(u8Char_ - UPPERCASE_ASCII_TO_DEC);

  if( (u8Char_ >= 'a') && (u8Char_ <= 'f') )
    return(u8Char_ - LOWERCASE_ASCII_TO_DEC);

  return(0xff);

} /* end ASCIIHexChartoChar */


/*-----------------------------------------------------------------------------/
Function: HexToASCIICharUpper

Description:
Determines the ASCII char of a single digit number
0 - 15 -> '0' - 'F'

Requires:
  - Standard ASCII table is in use

Promises:
  - If valid 0-15, returns the corresponding ASCII hex char 0-9, A-F
  - Otherwise returns 0xff
*/
u8 HexToASCIICharUpper(u8 u8Char_)
{
  u8 u8ReturnValue = 0xFF;

  if( u8Char_ <= 9 )
  {
    u8ReturnValue = u8Char_ + NUMBER_ASCII_TO_DEC;
  }

  else if( (u8Char_ >= 10) && (u8Char_ <= 15) )
  {
    u8ReturnValue = u8Char_ + UPPERCASE_ASCII_TO_DEC;
  }

  return(u8ReturnValue);

} /* end HexToASCIICharUpper */


/*-----------------------------------------------------------------------------/
Function: NumberToAscii

Description:
Converts a long into an ASCII string.  Maximum of 10 digits + NULL.

Requires:
  - u32Number_ is the number to convert
  - *pu8AsciiString_ points to the destination string location

Promises:
  - Null-terminated string of the number is loaded to pu8AsciiString_
  - Returns the number of digits
*/
u8 NumberToAscii(int u32Number_, u8* pu8AsciiString_, u8 u8Decimals, bool isSigned)
{
  bool bFoundDigit = false;
  u8 au8AsciiNumber[11];
  u8 u8CharCount = 0;
  u32 u32Divider = 1000000000;
  u8 u8Temp;
  u8 u8MaxDigits = 10;

  if (isSigned && u32Number_ < 0)
  {
	  au8AsciiNumber[u8CharCount] = '-';
	  u8CharCount++;
	  u32Number_ *= -1;
  }


  if (u8Decimals > 0)
  {
    u32Divider /= 10;
    u8MaxDigits--;   // room for decimal point
  }


  /* Parse out all the digits, start counting after leading zeros */
  for(u8 i = 0; i < u8MaxDigits; i++)
  {
    u8Temp = (u32Number_ / u32Divider);

    /* Check for first non-leading zero */
    if(u8Temp != 0)
    {
      bFoundDigit = true;
    }

    /* As long as a non-leading zero has been found, add the ASCII char */
    if(bFoundDigit)
    {
      au8AsciiNumber[u8CharCount] = u8Temp + 0x30;
      u8CharCount++;
    }


    // add decimal point?
    if ((u8Decimals > 0) && (i == (u8MaxDigits - u8Decimals -1)))
    {
      au8AsciiNumber[u8CharCount++] = '.';
    }


    /* Update for next iteration */
    u32Number_ %= u32Divider;
    u32Divider /= 10;

  }

  /* Handle special case where u32Number == 0 */
  if(!bFoundDigit)
  {
    u8CharCount = 1;
    au8AsciiNumber[0] = '0';
  }

  /* Add the null and copy to destination */
  au8AsciiNumber[u8CharCount] = NULL;
  strcpy((char *)pu8AsciiString_, (const char*)au8AsciiNumber);

  return(u8CharCount);

} /* end NumberToAscii() */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected Functions */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions */
/*--------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/
