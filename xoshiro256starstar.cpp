//////////////////////////////////////////////////////////////
// wrapper written by Scott Baker / https://www.perturb.org //
// Written: 2024-10-24                                      //
//////////////////////////////////////////////////////////////

#include <cstdint>

class xoshiro256starstar {
	public:
		void     seed(uint64_t seeds[4]);
		uint64_t rotl(const uint64_t x, int k);
		uint32_t rand();
		uint64_t rand32();
		uint64_t rand64();

		bool debug            = 0;
		const char* prng_name = "xoshiro256starstar";
	private:
		uint64_t s[4];
};

//////////////////////////////////////////////////////////////////

uint64_t xoshiro256starstar::rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

// An array of params
void xoshiro256starstar::seed(uint64_t seeds[4]) {
	for (int i = 0; i < 4; i++) {
		s[i] = seeds[i];

		if (this->debug) {
			printf("%s SEED: %d = %llu\n", prng_name, i, s[i]);
		}
	}
}

// Return a random 64 bit integer
uint64_t xoshiro256starstar::rand64(void) {
	const uint64_t result = rotl(s[1] * 5, 7) * 9;
	const uint64_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl(s[3], 45);

	return result;
}

// Return a random 32 bit integer
uint32_t xoshiro256starstar::rand() {
	uint64_t ret = rand64();

	ret = ret >> 32;

	return ret;
}
