# simple-prng

Simple C++ implementations for popular Pseudo Random Number Generators

## Usage

```c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pcg32.cpp"

int main(int argc, char *argv[]) {
	pcg32 prng;

	// Seed the PRNG
	uint64_t seeds[2] = { 38424, 84924 };
	prng.seed(seeds);

	// Warm up the PRNG
	for (int i = 0; i < 1024; i++) {
		prng.rand();
	}

	// 32 bit randoms
	for (int i = 0; i < 5; i++) { printf("%llu\n", prng.rand()); }

	// 64 bit randoms
	for (int i = 0; i < 5; i++) { printf("%llu\n", prng.rand64()); }
}
```

## Methods

`void prng.seed(uint64_t seeds[x])` seed the PRNG with 1 - 4 seeds

`uint32_t prng.rand()` fetch a random 32bit integer

`uint64_t prng.rand64()` fetch a random 64bit integer

## Available PRNGs

* PCG32 - `pcg32.cpp` - pcg32
* SplitMix64 - `split_mix_64.cpp` - sm64
* xoroshiro128+ - `xoroshiro128plus.cpp` - xoroshiro128plus
* xoshiro256** - `xoshiro256starstar.cpp` - xoshiro256starstar
