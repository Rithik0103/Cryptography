#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRIME_NUMBER 11

unsigned int public_key;  

void generate_keys(unsigned int *private_key, unsigned int *public_key) {
  *private_key = rand() % PRIME_NUMBER;


  *public_key = (unsigned int)pow(*private_key, 2) % PRIME_NUMBER;
}

unsigned int mod_inverse(unsigned int a, unsigned int m) {

  for (unsigned int i = 1; i < m; i++)
    if ((a * i) % m == 1)
      return i;
  return 0;
}

unsigned int sign(unsigned int message, unsigned int private_key) {

  unsigned int k = rand() % PRIME_NUMBER;
  unsigned int r = (k * public_key) % PRIME_NUMBER;
  unsigned int s = (mod_inverse(k, PRIME_NUMBER) * (message + private_key * r)) % PRIME_NUMBER;

  return (r << 16) | s;
}

int verify(unsigned int message, unsigned int signature, unsigned int public_key) {
  unsigned int r = signature >> 16;
  unsigned int s = signature & 0xffff;

  unsigned int w = mod_inverse(s, PRIME_NUMBER);

  unsigned int u1 = (message * w) % PRIME_NUMBER;
  unsigned int u2 = (r * w) % PRIME_NUMBER;
  unsigned int v = ((unsigned int)pow(public_key, u1) * (unsigned int)pow(r, u2)) % PRIME_NUMBER;
  return v == r;
}

int main() {
  unsigned int private_key;
  generate_keys(&private_key, &public_key);
  unsigned int message;
  printf("Enter the message to be signed: ");
  scanf("%u", &message);
  unsigned int signature = sign(message, private_key);
  int is_valid = verify(message, signature, public_key);
  if (is_valid) {
    printf("The signature is valid.\n");
  } else {
    printf("The signature is invalid.\n");
  }

  return 0;
}

