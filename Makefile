default:
	@g++ prng-test.cpp -o prng-test

run: default
	@./prng-test 10
