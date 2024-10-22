#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "split_mix_64.cpp"
#include "pcg32.cpp"
#include "xoroshiro128plus.cpp"
//#include "xoshiro256starstar.cpp"

int main(int argc, char *argv[]) {
	//sm64 prng;
	//pcg32 prng;
	xoroshiro128plus prng;
	//xoshiro256starstar prng;

	uint64_t seeds[4] = { (uint64_t)time(NULL), (uintptr_t)printf, 7, 5 };
	prng.seed(seeds);

	// Warm up the PRNG
	for (int i = 0; i < 1024; i++) {
		prng.rand();
	}

	for (int i = 0; i < 5; i++) {
		printf("%llu\n", prng.rand64());
	}
}

// vim: tabstop=4 shiftwidth=4 noexpandtab autoindent softtabstop=4

