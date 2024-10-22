/////////////////////////////////////////////////////////////////////////
// SplitMix64 wrapper written by Scott Baker / https://www.perturb.org //
// Written: 2024-10-24                                                 //
/////////////////////////////////////////////////////////////////////////

/* This is a fixed-increment version of Java 8's SplittableRandom generator
   See http://dx.doi.org/10.1145/2714064.2660195 and
   http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html

   It is a very fast generator passing BigCrush, and it can be useful if
   for some reason you absolutely want 64 bits of state. */

#include <cstdint>

class sm64 {
	public:
		void seed(uint64_t seed1, uint64_t seed2);
		void seed(uint64_t seed);
		void seed(uint64_t seeds[2]);
		uint32_t rand();
		uint64_t rand64();

		bool debug = 0;
		const char* prng_name = "split_mix_64";
	private:
		uint64_t x;
};

//////////////////////////////////////////////////////////////

// There are two seeds here to be compatible with other PRNGs
// The second is ignore for split mix
void sm64::seed(uint64_t seed1, uint64_t seed2) {
	x = seed1;

	if (this->debug) { printf("%s SEED: %llu\n", prng_name, x); }
}

// This only takes ONE seed
void sm64::seed(uint64_t seed) {
	x = seed;

	if (this->debug) { printf("%s SEED: %llu\n", prng_name, x); }
}

// Array of seeds
void sm64::seed(uint64_t seeds[1]) {
	x = seeds[0];

	if (this->debug) { printf("%s SEED: %llu\n", prng_name, x); }
}

uint64_t sm64::rand64() {
	uint64_t z;

	z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;

	return z ^ (z >> 31);
}

uint32_t sm64::rand() {
	uint64_t ret = sm64::rand64();

	ret = ret >> 32;

	return ret;
}
