#include <stdio.h>
#include <stdlib.h>
#include <time.h> // clock_gettime()

#include "splitmix64.cpp"
#include "pcg32.cpp"
#include "xoroshiro128plus.cpp"
#include "xoshiro256starstar.cpp"
#include "skel.cpp"

// Microseconds of uptime
uint64_t nanos() {
    struct timespec ts;

    // Get the monotonic time
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return 0; // Return 0 on failure (you can handle this differently)
    }

	// Calculate uptime in nanoseconds
	return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

int main(int argc, char *argv[]) {
	// We make a small splitmix64 PRNG to generate seeds
	splitmix64 sm;
	sm.seed(nanos());
	sm.warmup();

	//splitmix64 prng;
	pcg32 prng;
	//xoroshiro128plus prng;
	//xoshiro256starstar prng;
	//skel prng;

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
		printf("rand32(): %llu\n", prng.rand());
	}

	// 64 bit randoms
	for (int i = 0; i < 5; i++) {
		printf("rand64(): %llu\n", prng.rand64());
	}
}

// vim: tabstop=4 shiftwidth=4 noexpandtab autoindent softtabstop=4

