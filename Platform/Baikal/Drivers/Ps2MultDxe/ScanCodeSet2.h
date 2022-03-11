#ifndef __SCANCODESET2_H__
#define __SCANCODESET2_H__

#define SCANCODE_SET_ID                 0x02
#define SCANCODE_EXTENDED0              0xE0
#define SCANCODE_EXTENDED1              0xE1
#define SCANCODE_BREAK                  0xF0
#define SCANCODE_CTRL_MAKE              0x14
#define SCANCODE_ALT_MAKE               0x11
#define SCANCODE_LEFT_SHIFT_MAKE        0x12
#define SCANCODE_SLASH_MAKE             0x4A
#define SCANCODE_RIGHT_SHIFT_MAKE       0x59
#define SCANCODE_CAPS_LOCK_MAKE         0x58
#define SCANCODE_NUM_LOCK_MAKE          0x77
#define SCANCODE_SCROLL_LOCK_MAKE       0x7E
#define SCANCODE_DELETE_MAKE            0x71
#define SCANCODE_LEFT_LOGO_MAKE         0x1F //GUI key defined in Keyboard scan code
#define SCANCODE_RIGHT_LOGO_MAKE        0x27
#define SCANCODE_MENU_MAKE              0x2F //APPS key defined in Keyboard scan code
#define SCANCODE_SYS_REQ_MAKE           0x7C
#define SCANCODE_SYS_REQ_MAKE_WITH_ALT  0x84

struct KeyCodeData ConvertKeyboardScanCodeToEfiKey[] = {
  {
    0x01,
    SCAN_F9,
    0x0000,
    0x0000
  },
  {
    0x02,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x03,
    SCAN_F5,
    0x0000,
    0x0000
  },
  {
    0x04,
    SCAN_F3,
    0x0000,
    0x0000
  },
  {
    0x05,
    SCAN_F1,
    0x0000,
    0x0000
  },
  {
    0x06,
    SCAN_F2,
    0x0000,
    0x0000
  },
  {
    0x07,
    SCAN_F12,
    0x0000,
    0x0000
  },
  {
    0x08,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x09,
    SCAN_F10,
    0x0000,
    0x0000
  },
  {
    0x0A,
    SCAN_F8,
    0x0000,
    0x0000
  },
  {
    0x0B,
    SCAN_F6,
    0x0000,
    0x0000
  },
  {
    0x0C,
    SCAN_F4,
    0x0000,
    0x0000
  },
  {
    0x0D,
    SCAN_NULL,
    0x0009,
    0x0009
  },
  {
    0x0E,
    SCAN_NULL,
    L'`',
    L'~'
  },
  {
    0x0F,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x10,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x11,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x12,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x13,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x14,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x15,
    SCAN_NULL,
    L'q',
    L'Q'
  },
  {
    0x16,
    SCAN_NULL,
    L'1',
    L'!'
  },
  {
    0x17,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x18,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x19,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x1A,
    SCAN_NULL,
    L'z',
    L'Z'
  },
  {
    0x1B,
    SCAN_NULL,
    L's',
    L'S'
  },
  {
    0x1C,
    SCAN_NULL,
    L'a',
    L'A'
  },
  {
    0x1D,
    SCAN_NULL,
    L'w',
    L'W'
  },
  {
    0x1E,
    SCAN_NULL,
    L'2',
    L'@'
  },
  {
    0x1F,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x20,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x21,
    SCAN_NULL,
    L'c',
    L'C'
  },
  {
    0x22,
    SCAN_NULL,
    L'x',
    L'X'
  },
  {
    0x23,
    SCAN_NULL,
    L'd',
    L'D'
  },
  {
    0x24,
    SCAN_NULL,
    L'e',
    L'E'
  },
  {
    0x25,
    SCAN_NULL,
    L'4',
    L'$'
  },
  {
    0x26,
    SCAN_NULL,
    L'3',
    L'#'
  },
  {
    0x27,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x28,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x29,
    SCAN_NULL,
    L' ',
    L' '
  },
  {
    0x2A,
    SCAN_NULL,
    L'v',
    L'V'
  },
  {
    0x2B,
    SCAN_NULL,
    L'f',
    L'F'
  },
  {
    0x2C,
    SCAN_NULL,
    L't',
    L'T'
  },
  {
    0x2D,
    SCAN_NULL,
    L'r',
    L'R'
  },
  {
    0x2E,
    SCAN_NULL,
    L'5',
    L'%'
  },
  {
    0x2F,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x30,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x31,
    SCAN_NULL,
    L'n',
    L'N'
  },
  {
    0x32,
    SCAN_NULL,
    L'b',
    L'B'
  },
  {
    0x33,
    SCAN_NULL,
    L'h',
    L'H'
  },
  {
    0x34,
    SCAN_NULL,
    L'g',
    L'G'
  },
  {
    0x35,
    SCAN_NULL,
    L'y',
    L'Y'
  },
  {
    0x36,
    SCAN_NULL,
    L'6',
    L'^'
  },
  {
    0x37,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x38,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x39,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x3A,
    SCAN_NULL,
    L'm',
    'M'
  },
  {
    0x3B,
    SCAN_NULL,
    L'j',
    L'J'
  },
  {
    0x3C,
    SCAN_NULL,
    L'u',
    L'U'
  },
  {
    0x3D,
    SCAN_NULL,
    L'7',
    L'&'
  },
  {
    0x3E,
    SCAN_NULL,
    L'8',
    L'*'
  },
  {
    0x3F,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x40,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x41,
    SCAN_NULL,
    L',',
    L'<'
  },
  {
    0x42,
    SCAN_NULL,
    L'k',
    L'K'
  },
  {
    0x43,
    SCAN_NULL,
    L'i',
    L'I'
  },
  {
    0x44,
    SCAN_NULL,
    L'o',
    L'O'
  },
  {
    0x45,
    SCAN_NULL,
    L'0',
    L')'
  },
  {
    0x46,
    SCAN_NULL,
    L'9',
    L'('
  },
  {
    0x47,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x48,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x49,
    SCAN_NULL,
    L'.',
    L'>'
  },
  {
    0x4A,
    SCAN_NULL,
    L'/',
    L'?'
  },
  {
    0x4B,
    SCAN_NULL,
    L'l',
    L'L'
  },
  {
    0x4C,
    SCAN_NULL,
    L';',
    L':'
  },
  {
    0x4D,
    SCAN_NULL,
    L'p',
    L'P'
  },
  {
    0x4E,
    SCAN_NULL,
    L'-',
    L'_'
  },
  {
    0x4F,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x50,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x51,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x52,
    SCAN_NULL,
    L'\'',
    L'\"'
  },
  {
    0x53,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x54,
    SCAN_NULL,
    L'[',
    L'{'
  },
  {
    0x55,
    SCAN_NULL,
    L'=',
    L'+'
  },
  {
    0x56,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x57,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x58,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x59,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x5A,
    SCAN_NULL,
    0x000d,
    0x000d
  },
  {
    0x5B,
    SCAN_NULL,
    L']',
    L'}'
  },
  {
    0x5C,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x5D,
    SCAN_NULL,
    L'\\',
    L'|'
  },
  {
    0x66,
    SCAN_NULL,
    0x0008,
    0x0008
  },
  {
    0x69,
    SCAN_END,
    L'1',
    L'1'
  },
  {
    0x6A,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x6B,
    SCAN_LEFT,
    L'4',
    L'4'
  },
  {
    0x6C,
    SCAN_HOME,
    L'7',
    L'7'
  },
  {
    0x6D,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x6E,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x6F,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x70,
    SCAN_INSERT,
    L'0',
    L'0'
  },
  {
    0x71,
    SCAN_DELETE,
    L'.',
    L'.'
  },
  {
    0x72,
    SCAN_DOWN,
    L'2',
    L'2'
  },
  {
    0x73,
    SCAN_NULL,
    L'5',
    L'5'
  },
  {
    0x74,
    SCAN_RIGHT,
    L'6',
    L'6'
  },
  {
    0x75,
    SCAN_UP,
    L'8',
    L'8'
  },
  {
    0x76,
    SCAN_ESC,
    0x0000,
    0x0000
  },
  {
    0x77,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x78,
    SCAN_F11,
    0x0000,
    0x0000
  },
  {
    0x79,
    SCAN_NULL,
    L'+',
    L'+'
  },
  {
    0x7A,
    SCAN_PAGE_DOWN,
    L'3',
    L'3'
  },
  {
    0x7B,
    SCAN_NULL,
    L'-',
    L'-'
  },
  {
    0x7C,
    SCAN_NULL,
    L'*',
    L'*'
  },
  {
    0x7D,
    SCAN_PAGE_UP,
    L'9',
    L'9'
  },
  {
    0x7E,
    SCAN_NULL,
    0x0000,
    0x0000
  },
  {
    0x83,
    SCAN_F7,
    0x0000,
    0x0000
  },
  {
    TABLE_END,
    TABLE_END,
    SCAN_NULL,
    SCAN_NULL
  },
};

#endif
