/**
 * FujiNet Configuration Program
 *
 * Screen macros
 */

#ifndef SCREEN_H
#define SCREEN_H

#define SetChar(x,y,a) video_ptr[(x)+(y)*40]=(a);
#define GetChar(x,y) video_ptr[(x)+(y)*40]
#define GRAPHICS_0_SCREEN_SIZE (40*25)
#define DISPLAY_LIST 0x0600
#define DISPLAY_MEMORY 0x2400
#define FONT_MEMORY 0x2000

/**
 * Print ATASCII string to display memory
 */
void screen_puts(unsigned char x,unsigned char y,char *s);

/**
 * Clear screen
 */
void screen_clear(void);

#endif /* SCREEN_H */
