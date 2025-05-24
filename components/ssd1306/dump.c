
#include <stdio.h>
#include <stdio.h>
#include <esp_check.h>

#define NUM_DIGITS 32

void ssd1306_do_dump_data(const void* data, size_t size, const char* format, ...)
{
	const uint8_t* buff = (uint8_t*)data;
	char text[2 + 8 + 2 + 4*NUM_DIGITS + NUM_DIGITS / 8 + 1];

	size_t tpos = 0;
	size_t offs = 0;

	va_list args;

	va_start(args, format);
	vsnprintf(text, sizeof(text), format, args);
	va_end(args);

	for( ; offs < size; offs++, buff++ ) {
		const unsigned rest = offs % NUM_DIGITS;

		if( rest == 0 ) {
			if( text[0] ) {
				printf("%s\n", text);
			}

			tpos = 0;
			tpos += snprintf(text + tpos, sizeof(text) - tpos, "%p:", buff);
		}

		if( tpos > 11 && rest % 8 == 0 ) {
			text[tpos++] = ' ';
		}

		tpos += snprintf(text + tpos, sizeof(text) - tpos, " %02x", *buff);

		ESP_RETURN_VOID_ON_FALSE(tpos <= sizeof(text), "SSD1306", "tpos = %u, offs = %u", tpos, offs);
	}

	if( offs % NUM_DIGITS ) {
		printf("%s\n", text);
	}
}
