#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "4b6b.h"

void print_bytes(const uint8_t *buf, size_t len)
{
	int i;

	for (i = 0; i < len; ++i) {
		printf("%02X ", buf[i]);
		if ((i + 1) % 20 == 0)
			printf("\n");
	}
	if (i % 20 != 0)
		printf("\n");
}

uint8_t enc_test_1[] = {
	0xA7, 0x47, 0x33, 0x62, 0x5D, 0x02, 0x01, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0C
};

uint8_t enc_test_2[] = { 0xA7, 0x47, 0x33, 0x62, 0x8D, 0x00, 0xA6 };

uint8_t dec_test_1[] = {
	0xA9, 0x6D, 0x16, 0x8E, 0x39, 0xB2, 0x68, 0xD5, 0x59, 0x56,
	0x38, 0xD6, 0x8F, 0x28, 0xF2, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0xB3, 0x25
};

uint8_t dec_test_2[] = {
	0xA9, 0x6D, 0x16, 0x8E, 0x39, 0xB2, 0x56, 0x65, 0x55, 0x56, 0x35
};

uint8_t result[256], test[256], tmp[256];

void randomly_fill(uint8_t *buf, size_t len)
{
	int i;

	for (i = 0; i < len; ++i)
		buf[i] = random() >> 8;
}

int main(void)
{
	int i, len, n;
	const int num_tests = 500000;

	printf("Encode test #1:\n");
	len = sizeof(enc_test_1);
	n = encode_4b6b(enc_test_1, result, len);
	print_bytes(result, n);

	printf("Encode test #2:\n");
	len = sizeof(enc_test_2);
	n = encode_4b6b(enc_test_2, result, len);
	print_bytes(result, n);

	printf("Decode test #1:\n");
	len = sizeof(dec_test_1);
	n = decode_4b6b(dec_test_1, result, len);
	if (n >= 0) {
		print_bytes(result, n);
	} else {
		printf("Decoding error!\n");
		return 1;
	}

	printf("Decode test #2:\n");
	len = sizeof(dec_test_2);
	n = decode_4b6b(dec_test_2, result, len);
	if (n >= 0) {
		print_bytes(result, n);
	} else {
		printf("Decoding error!\n");
		return 1;
	}

	printf("Inverse test:\n");
	for (i = 0; i < num_tests; ++i) {
		randomly_fill(test, 128);
		n = encode_4b6b(test, tmp, 128);
		len = decode_4b6b(tmp, result, n);
		if (len != 128) {
			printf("Decoding error!\n");
			return 1;
		}
		if (memcmp(result, test, 128) != 0) {
			printf("Decoded to wrong value!\n");
			return 1;
		}
	}

	return 0;
}
