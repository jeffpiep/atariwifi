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

        // Okimate 10 extras codes:
        // ESC CTRL-T ESC CTRL-N - 8.25 char/inch (0x14, 0x0E)
        // 0x99     Align Ribbon (for color mode)
        // 0x9B     EOL for color mode

        // 0x8A n    n/144" line advance (n * 1/2 pt vertial line feed)
        // 0x8C     form feed
        // ESC A - perforation skip OFF
        // ESC B - perforation skip ON

        // ESC % - start graphics mode
        // 0x91 - stop graphics mode
        // 0x9A n data - repeat graphics data n times

        // 0x90 n - dot column horizontal tab

        switch (c)
        {
        case 0x0E:
            // change font to elongated like
            if (!compressedMode)
            {
                fprintf(_file, ")]TJ\n 200 Tz [(");
                charWidth = 14.4; //72.0 / 5.0;
            }
            else
            {
                fprintf(_file, ")]TJ\n 121.21 Tz [(");
                charWidth = 72.0 / 8.25;
            }
            break;
        case 0x0F:
            // change font to normal
            fprintf(_file, ")]TJ\n 100 Tz [(");
            charWidth = 7.2; //72.0 / 10.0;
            compressedMode = false;
            break;
        case 0x14:
            // change font to compressed
            fprintf(_file, ")]TJ\n 60.606 Tz [(");
            charWidth = 72.0 / 16.5;
            compressedMode = true;
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
