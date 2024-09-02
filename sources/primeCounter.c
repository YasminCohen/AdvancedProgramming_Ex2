#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
	if (n <= 1)
		return false;
	
	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
			return false;
	}

	return true;
}

int main() {
	int num;
	int total_counter = 0;

	while (scanf("%d", &num) != EOF)
	{
		if (isPrime(num))
		{
			total_counter++;
		}
	}

	printf("%d total primes.\n", total_counter);

	return 0;
}