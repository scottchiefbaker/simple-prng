#include <stdio.h>
#include <stdlib.h>
#include <time.h> // clock_gettime()

#include "splitmix64.cpp"
#include "pcg32.cpp"
#include "xoroshiro128plus.cpp"
#include "xoshiro256starstar.cpp"
#include "skel.cpp"

uint64_t get_urandom_u64();
uint64_t nanos();

uint8_t iterations = 4;

int main(int argc, char *argv[]) {
	// Get a random number from /dev/urandom or fall back to nanos()
	uint64_t seed = get_urandom_u64();
	if (seed == 0 ) { seed = nanos(); }

	// We make a small splitmix64 PRNG to generate seeds
	splitmix64 sm;
	sm.seed(seed);
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

	printf("\n");
	// 32 bit randoms
	for (int i = 0; i < iterations; i++) {
		printf("rand32(): %llu\n", prng.rand());
	}

	printf("\n");
	// 64 bit randoms
	for (int i = 0; i < iterations; i++) {
		printf("rand64(): %llu\n", prng.rand64());
	}

	printf("\n");
	double max = 18446744073709551615.0; // 2^64 - 1
	for (int i = 0; i < iterations; i++) {
		double num = prng.rand64() / max;
		// A double is about 16 decimal digits
		printf("float   : %0.16f\n", num);
	}

	printf("\n");
	// Biased random number in a range
	for (int i = 0; i < iterations; i++) {
		uint64_t num   = prng.rand64();
		uint64_t range = 999;

		// A double is about 16 decimal digits
		printf("0 - %-4d: %d\n", range, num % range);
	}
}

uint64_t get_urandom_u64() {
	uint64_t random_value = 0; // Default to 0 in case of failure
	FILE *urandom = fopen("/dev/urandom", "rb");

	// Return 0 if /dev/urandom cannot be opened
	if (urandom == NULL) {
		return 0;
	}

	size_t bytes_read = fread(&random_value, sizeof(random_value), 1, urandom);
	fclose(urandom);

	// Check if fread successfully read 8 bytes
	if (bytes_read != 1) {
		return 0;
	}

	return random_value;
}

// Nanoseconds of uptime
uint64_t nanos() {
	struct timespec ts;

	// Get the monotonic time
	int8_t ok = clock_gettime(CLOCK_MONOTONIC, &ts);
	if (ok != 0) {
		return 0; // Return 0 on failure (you can handle this differently)
	}

	// Calculate uptime in nanoseconds
	uint64_t ret = (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;

	return ret;
}

// vim: tabstop=4 shiftwidth=4 noexpandtab autoindent softtabstop=4
