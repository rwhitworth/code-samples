#pragma once

#if defined (__cplusplus)
extern "C" {
#endif

#define rle_decode_memory_multipler 128
#define rle_encode_memory_multipler 128

char* rle_enc(const char *input);
char* rle_dec(const char *input);

#if defined (__cplusplus)
}
#endif