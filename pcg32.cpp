/////////////////////////////////////////////////////////////////////////
// PCG32 wrapper written by Scott Baker / https://www.perturb.org      //
// Written: 2024-10-24                                                 //
/////////////////////////////////////////////////////////////////////////

/* This is a fixed-increment version of Java 8's SplittableRandom generator
   See http://dx.doi.org/10.1145/2714064.2660195 and
   http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html

   It is a very fast generator passing BigCrush, and it can be useful if
   for some reason you absolutely want 64 bits of state. */

#include <cstdint>

class pcg32 {
	public:
		void seed(uint64_t seed1, uint64_t seed2);
		void seed(uint64_t seeds[2]);
		uint32_t rand();
		uint64_t rand64();

		const char* prng_name = "pcg32";
		bool debug = 0;
	private:
		uint64_t state;
		uint64_t inc;
};

//////////////////////////////////////////////////////////////

void pcg32::seed(uint64_t seed1, uint64_t seed2) {
	state = seed1;
	inc   = seed2;

	if (this->debug) { printf("%s SEED: %llu / %llu\n", prng_name, state, inc); }
}

void pcg32::seed(uint64_t seeds[2]) {
	state = seeds[0];
	inc   = seeds[1];

	if (this->debug) { printf("%s SEED: %llu / %llu\n", prng_name, state, inc); }
}

uint32_t pcg32::rand() {
    uint64_t oldstate = state;

    // Advance internal state
    state = oldstate * 6364136223846793005ULL + (inc|1);

    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;

    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

uint64_t pcg32::rand64() {
	uint32_t low  = pcg32::rand();
	uint64_t high = pcg32::rand();

	uint64_t ret = (high << 32) | low;

	return ret;
}
