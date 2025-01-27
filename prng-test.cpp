#include <stdio.h>
#include <stdlib.h>
#include <time.h> // clock_gettime()

#include "splitmix64.cpp"
#include "pcg32.cpp"
#include "xoroshiro128plus.cpp"
#include "xoshiro256starstar.cpp"
#include "skel.cpp"

// Pick which PRNG you want to use
pcg32 prng;

//splitmix64 prng;
//xoroshiro128plus prng;
//xoshiro256starstar prng;
//skel prng;

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

// Nanoseconds since Unix epoch
uint64_t nanos() {
	struct timespec ts;

	// int8_t ok = clock_gettime(CLOCK_MONOTONIC, &ts); // Uptime
	int8_t ok = clock_gettime(CLOCK_REALTIME, &ts);  // Since epoch

	if (ok != 0) {
		return 0; // Return 0 on failure (you can handle this differently)
	}

	// Calculate nanoseconds
	uint64_t ret = (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;

	return ret;
}

// https://prng.di.unimi.it/#remarks
static double _uint64_to_double(uint64_t num) {
	// A standard 64bit double floating-point number in IEEE floating point
	// format has 52 bits of significand. Thus, the representation can actually
	// store numbers with 53 significant binary digits.
	double scale = 1.0 / (1ULL << 53);  // 1 divided by 2^53
	double ret   = (num >> 11) * scale; // Top 53 bits divided by 1/2^53

	//printf("Double: %0.15f\n", ret);

	return ret;
}

int main(int argc, char *argv[]) {
	uint8_t iterations = 5;

	prng.seed(get_urandom_u64(), get_urandom_u64());

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
		printf("rand64(): %lu\n", prng.rand64());
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
		printf("0 - %-4lu: %lu\n", range, num % range);
	}
}

// vim: tabstop=4 shiftwidth=4 noexpandtab autoindent softtabstop=4
