#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#include <esp_log_level.h>

extern const char LOG_DOMAIN[];

void ssd1306_do_dump_data(const void* data, size_t size, const char* format, ...);

#define ssd1306_dump_data(data, size, format, ...) \
	do { \
		if( _ESP_LOG_ENABLED(ESP_LOG_VERBOSE) && (esp_log_level_get(LOG_DOMAIN) >= ESP_LOG_VERBOSE) ) { \
			ssd1306_do_dump_data(data, size, format, ##__VA_ARGS__); \
		} \
	} while( 0 )

#if defined(__cplusplus)
}
#endif
