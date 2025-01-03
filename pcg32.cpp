/////////////////////////////////////////////////////////////////////////
// PCG32 wrapper written by Scott Baker / https://www.perturb.org      //
// Written: 2024-10-24                                                 //
/////////////////////////////////////////////////////////////////////////

// This is borrowed from: https://www.pcg-random.org/download.html

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

	if (this->debug) {
		printf("%s SEED: %d = %llu\n", prng_name, 0, seed1);
		printf("%s SEED: %d = %llu\n", prng_name, 1, seed2);
	}
}

void pcg32::seed(uint64_t seeds[2]) {
	seed(seeds[0], seeds[1]);
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
