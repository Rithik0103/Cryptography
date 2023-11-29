#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MD5_BLOCK_SIZE 64

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define LEFT_ROTATE(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

typedef struct {
    uint32_t A, B, C, D, E;
} MD5_STATE;

void md5_transform(uint32_t state[5], const uint8_t block[MD5_BLOCK_SIZE]) {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4], x[16];
	int i;
    // Convert the block to a 32-bit integer array
    for (i = 0; i < 16; i++) {
        x[i] = (block[i * 4]) | (block[i * 4 + 1] << 8) | (block[i * 4 + 2] << 16) | (block[i * 4 + 3] << 24);
    }

    for (i = 0; i < 64; i++) {
        uint32_t temp, f, g;

        if (i < 16) {
            f = F(b, c, d);
            g = i;
        } else if (i < 32) {
            f = G(b, c, d);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H(b, c, d);
            g = (3 * i + 5) % 16;
        } else {
            f = I(b, c, d);
            g = (7 * i) % 16;
        }

        temp = f + x[g] + state[(i % 4)] + e;
        a = e;
        e = d;
        d = c;
        c = b;
        b = b + LEFT_ROTATE(temp, (i < 16 ? (i % 4) : ((i < 32) ? (5 * i + 1) % 16 : ((i < 48) ? (3 * i + 5) % 16 : (7 * i) % 16))));
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}

void md5_hash(const uint8_t *data, size_t length, uint8_t hash[16]) {
	size_t i;
    MD5_STATE state = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0x76543210};
    size_t block_count = length / MD5_BLOCK_SIZE;

    for ( i = 0; i < block_count; i++) md5_transform((uint32_t*)&state, data + i * MD5_BLOCK_SIZE);

    memcpy(hash, &state, 16);
}

int main() {
    char input[1000];
	int i;
    printf("Enter the input string: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    uint8_t hash[16];
    md5_hash((uint8_t*)input, strlen(input), hash);

    printf("Input: %s\nMD5 Hash: ", input);
    for (i = 0; i < 16; i++) printf("%02x", hash[i]);
    printf("\n");

    return 0;
}
