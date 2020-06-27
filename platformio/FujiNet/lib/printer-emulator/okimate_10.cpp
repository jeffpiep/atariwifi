#include "okimate_10.h"
#include "../../include/debug.h"

void okimate10::pdf_handle_char(uint8_t c, uint8_t aux1, uint8_t aux2)
{
    if (escMode)
    {
        // Atari 1025 escape codes:
        // ESC CTRL-T - 16.5 char/inch        0x14
        // ESC CTRL-O - 10 char/inch          0x0F
        // ESC CTRL-N - 5 char/inch           0x0E
        // ESC L - long line 80 char/line     0x4C
        // ESC S - short line 64 char/line    0x53
        // ESC 6 - use 6 lines per inch       0x36
        // ESC 8 - use 8 lines per inch       0x38
        // ESC CTRL-W - start international   0x17 23
        // ESC CTRL-X - stop international    0x18 24

        switch (c)
        {
        case 0x0E:
            // change font to elongated like
            fprintf(_file, ")]TJ\n 200 Tz [(");
            charWidth = 14.4; //72.0 / 5.0;
            break;
        case 0x0F:
            // change font to normal
            fprintf(_file, ")]TJ\n 100 Tz [(");
            charWidth = 7.2; //72.0 / 10.0;
            break;
        case 0x14:
            // change font to compressed
            fprintf(_file, ")]TJ\n 60.606 Tz [(");
            charWidth = 72.0 / 16.5;
            break;
        case 0x17: // 23
            intlFlag = true;
            break;
        case 0x18: // 24
            intlFlag = false;
            break;
        case 0x36:             // '6'
            lineHeight = 12.0; //72.0/6.0;
            break;
        case 0x38:            // '8'
            lineHeight = 9.0; //72.0/8.0;
            break;
        case 0x4c: // 'L'
            set_line_long();
            break;
        case 0x53: // 'S'
            set_line_short();
            break;
        default:
            break;
        }

        escMode = false;
    }
    else if (c == 27)
        escMode = true;
    else
    { // maybe printable character
        print_char(c);
    }
}

void okimate10::post_new_file()
{
    atari1025::post_new_file();
   // shortname = "oki10";
}
