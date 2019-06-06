//  factorize.c
//  The code was written in the purpose of efficiency. So it does not comply with all software engineering criteria.
//  The code is Unix friendly. If the executable file is named factorize, it might be used like: factorize 54 9 23
//  Created by Sina Firoozabadi on 5/8/15.
//
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
// This array is used to store prime/composite feature of the corresponding number
byte *magic;

void sieve(unsigned long long n) {
	static unsigned long long N = 0;
	if(n > N) {
		if((n / 24 > N / 24) || N == 0)
		magic = (byte *)realloc(magic, n / 24 + 1);
		for(int i = N / 24; i <= n / 24; i++)
			magic[i] = (1 << 8) - 1;
		unsigned int place = 1;
		while(place <= n / 3) {
			while(!((magic[place / 8] >> (place % 8)) & 1) && place <= n / 3)
				place++;
			byte r = (place & 1)? 2: 1;
			byte s;
			if(r == 1)
				s = 4 * place + 1;
			else
				s = 2 * place + 1;
			for(unsigned int i = 3 * place * place + 2 * place * r + r * r / 3; i <= n / 3; i += s, s = 2 * (place * 3 + r) - s)
				if(i > N)
					magic[i / 8] &= (((1 << 8) - 1) - (1 << (i % 8)));
				place++;
		}
		N = n;
	}
}

int main(int argc, const char * argv[]) {
	magic = malloc(0);
	if(argc < 2) {
		printf("Usage: %s <numbers separated by whitespaces>\n", argv[0]);
		return 0;
	}
	for(int i = 1; i < argc; i++) {
		long long n = atoll(argv[i]);
		printf("%lld: ", n);
		if(n < 0) {
			printf("- ");
			n *= -1;
		}
		if(n < 2) {
			printf("%lld", n);
		} else {
			int power = 0;
			while(n % 2 == 0) {
				power++;
				n /= 2;
			}
			if(power) {
				printf("2^%d", power);
				if(n != 1)
				printf(" * ");
			}

			power = 0;
			while(n % 3 == 0) {
				power++;
				n /= 3;
			}
			if(power) {
				printf("3^%d", power);
				if(n != 1)
				printf(" * ");
			}

			unsigned long long place = 1;
			if(n != 1)
				sieve(n);
			while(n != 1) {
				power = 0;
				while(!((magic[place / 8] >> (place % 8)) & 1) && (place < n / 3))
					place++;
				unsigned long long prime = place * 3 + ((place & 1) ? 2 : 1);
				while(n % prime == 0) {
					power++;
					n /= prime;
				}
				if(power) {
					printf("%llu^%d", prime, power);
					if(n != 1)
					printf(" * ");
				}
				place++;
			}
		}
		printf("\n");
	}
}
