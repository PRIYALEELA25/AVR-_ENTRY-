/*
 * oled.c
 *
 * Created: 24-06-2026 21:01:41
 *  Author: hp
 */ 
#include "oled.h"
#include "i2c.h"

const uint8_t font[][5] = {
	{0x00, 0x00, 0x00, 0x00, 0x00}, 
	{0x00, 0x00, 0x5F, 0x00, 0x00},
	
	{0x3E, 0x41, 0x41, 0x41, 0x3E}, 
	{0x00, 0x42, 0x7F, 0x40, 0x00}, 
	{0x42, 0x61, 0x51, 0x49, 0x46}, 
	{0x21, 0x41, 0x45, 0x4B, 0x31}, 
	{0x18, 0x14, 0x12, 0x7F, 0x10}, 
	{0x27, 0x45, 0x45, 0x45, 0x39}, 
	{0x3C, 0x4A, 0x49, 0x49, 0x30}, 
	{0x01, 0x71, 0x09, 0x05, 0x03}, 
	{0x36, 0x49, 0x49, 0x49, 0x36}, 
	{0x06, 0x49, 0x49, 0x29, 0x1E}, 
	{0x00, 0x36, 0x36, 0x00, 0x00}, 
	{0x00, 0x00, 0x00, 0x00, 0x00}, 
	{0x7E, 0x11, 0x11, 0x11, 0x7E}, 
	{0x7F, 0x49, 0x49, 0x49, 0x36}, 
	{0x3E, 0x41, 0x41, 0x41, 0x22}, 
	{0x7F, 0x41, 0x41, 0x22, 0x1C}, 
	{0x7F, 0x49, 0x49, 0x41, 0x41}, 
	{0x3E, 0x41, 0x49, 0x49, 0x7A}, 
};

static void oled_command(uint8_t cmd) {
	i2c_start();
	i2c_write(OLED_ADDR << 1);
	i2c_write(0x00); 
	i2c_write(cmd);
	i2c_stop();
}

void oled_init(void) {
	oled_command(0xAE); // Turn display off
	oled_command(0x20); // Set Memory Addressing Mode
	oled_command(0x02); // Page addressing mode
	oled_command(0x8D); // Charge pump setup
	oled_command(0x14); // Enable charge pump
	oled_command(0xAF); // Turn display on
	oled_clear();
}

void oled_clear(void) {
	for (uint8_t page = 0; page < 8; page++) {
		oled_set_cursor(page, 0);
		i2c_start();
		i2c_write(OLED_ADDR << 1);
		i2c_write(0x40); // Data transmission mode
		for (uint8_t col = 0; col < 128; col++) {
			i2c_write(0x00); 
		}
		i2c_stop();
	}
}

void oled_set_cursor(uint8_t page, uint8_t column) {
	oled_command(0xB0 + page);
	oled_command(0x00 + (column & 0x0F));
	oled_command(0x10 + ((column >> 4) & 0x0F));
}

void oled_print_char(char c) {
	uint8_t idx = 0;
	if (c == ' ') idx = 0;
	else if (c >= '0' && c <= ':') idx = c - '0' + 2;
	else if (c == 'A') idx = 14;
	else if (c == 'B') idx = 15;
	else if (c == 'C') idx = 16;
	else if (c == 'D') idx = 17;
	else if (c == 'P') idx = 18;
	else if (c == 'T') idx = 19;
	
	i2c_start();
	i2c_write(OLED_ADDR << 1);
	i2c_write(0x40);
	for (uint8_t i = 0; i < 5; i++) {
		i2c_write(font[idx][i]);
	}
	i2c_write(0x00);
	i2c_stop();
}

void oled_print_string(const char *str) {
	while (*str) {
		oled_print_char(*str++);
	}
}