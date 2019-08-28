/*
    MIT License

    Copyright (c) 2019, Alexey Dynda

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
/* !!! THIS FILE IS AUTO GENERATED !!! */
#include "lcd_hal/io.h"
#ifdef SDL_EMULATION
#include "sdl_core.h"
#endif
#include "nano_gfx_types.h"

#ifndef CMD_ARG
#define CMD_ARG     0xFF
#endif

template <class I>
void InterfaceSSD1351<I>::startBlock(lcduint_t x, lcduint_t y, lcduint_t w)
{
    lcduint_t rx = w ? (x + w - 1) : (m_base.width() - 1);
    commandStart();
    this->send(0x15);
    spiDataMode(1);  // According to datasheet all args must be passed in data mode
    this->send(x);
    this->send( rx < m_base.width() ? rx : (m_base.width() - 1) );
    spiDataMode(0);
    this->send(0x75);
    spiDataMode(1);  // According to datasheet all args must be passed in data mode
    this->send(y);
    this->send(m_base.height() - 1);
    spiDataMode(0);
    this->send(0x5C);
    if (m_dc >= 0)
    {
        spiDataMode(1);
    }
    else
    {
        this->stop();
        this->start();
        this->send(0x40);
    }
}

template <class I>
void InterfaceSSD1351<I>::nextBlock()
{

}

template <class I>
void InterfaceSSD1351<I>::endBlock()
{
    this->stop();
}

template <class I>
void InterfaceSSD1351<I>::spiDataMode(uint8_t mode)
{
    if ( m_dc >= 0 )
    {
        lcd_gpioWrite( m_dc, mode ? LCD_HIGH : LCD_LOW );
    }
}

template <class I>
void InterfaceSSD1351<I>::commandStart()
{
    this->start();
    if (m_dc >= 0)
        spiDataMode(0);
    else
        this->send(0x00);
}


////////////////////////////////////////////////////////////////////////////////
//             SSD1351 basic 16-bit implementation
////////////////////////////////////////////////////////////////////////////////

template <class I>
void DisplaySSD1351x16<I>::begin()
{
}

template <class I>
void DisplaySSD1351x16<I>::end()
{
}

static const PROGMEM uint8_t s_SSD1351_lcd128x128x16_initData[] =
{
#ifdef SDL_EMULATION
    SDL_LCD_SSD1351, 0x00,
    0x00, 0x00,
#endif
    0xFD, 0x01, 0x12,     // Unlock
    0xFD, 0x01, 0xB1,     // Unlock
    0xAE, 0x00,           // SLEEP_ON
    0xB3, 0x01, 0xF1,     // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
    0xCA, 0x01, 127,      // Reset to default MUX. See datasheet
    0xA0, 0x01, 0B00110100,   // 16-bit rgb color mode
    0xA1, 0x01, 0x00,     // First line to start scanning from
    0xA2, 0x01, 0x00,     // Set display offset
    0xB5, 0x01, 0x00,     // GPIO OFF
    0xAB, 0x01, 0x01,     // Set function
    0xB1, 0x01, 0x32,     // Phase 1 and Phase 2 periods
    0xBE, 0x01, 0x05,     // Precharge
    0xBB, 0x01, 0x17,     // Precharge level
    0xA6, 0x00,           // Normal display
    0xC1, 0x03, 0xC8, 0x80, 0xC8, // Contrast RED, GREEN, BLUE
    0xC7, 0x01, 0x0F,     // Master current
    0xB4, 0x03, 0xA0, 0xB5, 0x55, // External VSL
    0xB6, 0x01, 0x01,     // Precharge second
    0xAF, 0x01,           // Disable power-safe mode
    0xA6, 0x00,           // Normal display
};

////////////////////////////////////////////////////////////////////////////////
//             SSD1351 basic 16-bit implementation
////////////////////////////////////////////////////////////////////////////////

template <class I>
void DisplaySSD1351_128x128x16<I>::begin()
{
    ssd1306_resetController2( this->m_rstPin, 20 );
    this->m_w = 128;
    this->m_h = 128;
    // Give LCD some time to initialize. Refer to SSD1351 datasheet
    lcd_delay(0);
    _configureSpiDisplay<I>(this->m_intf,
                            s_SSD1351_lcd128x128x16_initData,
                            sizeof(s_SSD1351_lcd128x128x16_initData));
}

template <class I>
void DisplaySSD1351_128x128x16<I>::end()
{
}
