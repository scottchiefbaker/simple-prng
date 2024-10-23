#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "split_mix_64.cpp"
#include "pcg32.cpp"
#include "xoroshiro128plus.cpp"
#include "xoshiro256starstar.cpp"
#include "skel.cpp"

int main(int argc, char *argv[]) {
	// We make a small sm64 PRNG to generate seeds
	sm64 sm;
	sm.seed(time(NULL));
	sm.warmup();

	//sm64 prng;
	//pcg32 prng;
	//xoroshiro128plus prng;
	//xoshiro256starstar prng;
	skel prng;

	prng.debug = 1;

	// Use SplitMix64 to generate some seeds
	uint64_t seeds[4];
	for (int i = 0; i < 4; i++) {
		seeds[i] = sm.rand64();
	}

	// Seed the PRNG we're wanting numbers from
	prng.seed(seeds);

	// Warm up the PRNG
	for (int i = 0; i < 1024; i++) {
		prng.rand();
	}

	// 32 bit randoms
	for (int i = 0; i < 5; i++) {
		printf("%llu\n", prng.rand());
	}

	// 64 bit randoms
	for (int i = 0; i < 5; i++) {
		printf("%llu\n", prng.rand64());
	}
}

// vim: tabstop=4 shiftwidth=4 noexpandtab autoindent softtabstop=4

