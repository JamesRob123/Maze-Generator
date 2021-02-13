#ifndef _BMP_H_
#define _BMP_H_
// BMP-related data types based on Microsoft's own
#pragma pack(1)
#include <stdint.h>

/**
	https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createbitmap
	----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	@warning LINES THAT ARE NOT WORD ALIGNED MUST BE PADDED WITH ZEROS. WASTED A LOT OF TIME ON THAT OUT SO DON'T MAKE MY MISTAKE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
**/

/**
 * Common Data Types
 *
 * The data types in this section are essentially aliases for C/C++
 * primitive data types.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPINFOHEADER
 *
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx.
 */
typedef struct
{
	WORD   bfType;
    DWORD  bfSize;
    DWORD  bfReserved;
    DWORD  bfOffBits;
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} BITMAPHEADER;

/**
 * RGBTRIPLE
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/aa922590.aspx.
 */
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} RGBTRIPLE;

BITMAPHEADER bmp_create_bitmapheader(int height, int width);
void bmp_create_image(BITMAPHEADER header, uint8_t *data, char *name);

#endif