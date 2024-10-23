//////////////////////////////////////////////////////////////
// wrapper written by Scott Baker / https://www.perturb.org //
// Written: 2024-10-24                                      //
//////////////////////////////////////////////////////////////

#include <cstdint>

class skel {
	public:
		void     seed(uint64_t seeds[2]);
		void     seed(uint64_t seed1, uint64_t seed2);
		uint32_t rand();
		uint64_t rand32();
		uint64_t rand64();

		bool debug            = 0;
		const char* prng_name = "skel";
	private:
		uint64_t s[2];
};

//////////////////////////////////////////////////////////////////

// Two params
void skel::seed(uint64_t seed1, uint64_t seed2) {
	s[0] = seed1;
	s[1] = seed2;

	if (this->debug) {
		printf("%s SEED: #1 = %llu\n", prng_name, s[0]);
		printf("%s SEED: #2 = %llu\n", prng_name, s[1]);
	}
}

// An array of params
void skel::seed(uint64_t seeds[2]) {
	for (int i = 0; i < 2; i++) {
		s[i] = seeds[i];

		if (this->debug) {
			printf("%s SEED: %d = %llu\n", prng_name, i+1, s[i]);
		}
	}
}

// Return a random 64 bit integer
uint64_t skel::rand64(void) {
	//printf("You called rand64\n");
	const uint64_t result = 123456789;

	return result;
}

// Return a random 32 bit integer
uint32_t skel::rand() {
	//printf("You called rand\n");
	uint64_t ret = rand64();

	ret = 1234;

	return ret;
}
