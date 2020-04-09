#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void complete_reverse_unsigned_long(unsigned long * array, unsigned int array_len);
void bubble_sort_unsigned_long(unsigned long * array, unsigned int array_dimension);

#ifdef __SIZEOF_INT128__

// non c'entra con la soluzione dell'esercizio:
// gcc versione > 4.6 ha un tipo dati int a 128 bit
// nota: printf non supporta __int128
// versione a 128 bit di fibonacci
unsigned __int128 fibonacci_128(unsigned int n) {

	unsigned __int128 fib_n, fib_n_1, fib_n_2;

	if (n < 0) {
		return -1;
	}

	switch (n) {
	case 0:
		return 0;
	case 1:
		return 1;
	default:
		fib_n_2 = 0;
		fib_n_1 = 1;

		for (unsigned int i = 2; i <= n; i++) {
			fib_n = fib_n_1 + fib_n_2;
			fib_n_2 = fib_n_1;
			fib_n_1 = fib_n;
		}

		return fib_n;
	}
}

#endif

// versione a 64 bit di fibonacci, usata per la soluzione
unsigned long fibonacci(unsigned int n) {

	unsigned long fib_n, fib_n_1, fib_n_2;

	if (n < 0) {
		return -1;
	}

	switch (n) {
	case 0:
		return 0;
	case 1:
		return 1;
	default:
		fib_n_2 = 0;
		fib_n_1 = 1;

		for (unsigned int i = 2; i <= n; i++) {
			fib_n = fib_n_1 + fib_n_2;
			fib_n_2 = fib_n_1;
			fib_n_1 = fib_n;
		}

		return fib_n;
	}
}

// provare a scoprire quale è il valore massimo di n per cui fibonacci(n)
// restituisce un valore della serie corretto
unsigned int max_correct_fibonacci(int print_messages) {
	unsigned long fib, prev_fib = 0;
	unsigned int n = 0;

	while(1) {
		fib = fibonacci(n);

		if (prev_fib > fib) {
			if (print_messages)
				printf("!!!! n=%u\t%lu (< fib(n-1))\n",n ,fib);

			break; // esci dal ciclo for
		}

		if (print_messages)
			printf("fib(%u)=\t%lu\n",n ,fib);

		prev_fib = fib;

		n++;
	}

	return n-1;
}


unsigned long * fibonacci_array(unsigned int n) {
	//questa funzione restituisce un array di unsigned long di dimensione n+1 (n è l'argomento della funzione)
	//dove la cella i-ma contiene il valore di fibonacci(i).

	unsigned long fib_n, fib_n_1, fib_n_2;

	unsigned long * result;

	if (n < 0) {
		return NULL;
	}

	result = malloc(sizeof(unsigned long) * (n+1));
	if (result == NULL)
		return NULL;

	switch (n) {
	case 0:
		result[0] = 0;
		return result;
	case 1:
		result[0] = 0;
		result[1] = 1;
		return result;
	default:
		fib_n_2 = 0;
		fib_n_1 = 1;
		result[0] = 0;
		result[1] = 1;

		for (unsigned int i = 2; i <= n; i++) {
			fib_n = fib_n_1 + fib_n_2;
			fib_n_2 = fib_n_1;
			fib_n_1 = fib_n;

			result[i] = fib_n;
		}

		return result;
	}

}

int main(int argc, char *argv[]) {

	unsigned int n;
	unsigned int i;

	n = max_correct_fibonacci(0);

	printf("il valore massimo per cui fibonacci() calcola correttamente la serie è %u\n", n);

	// calcola fibonacci_array(39)
	// e lo assegna alla varibile 'fibonacci_result'  // fibonacci(39) = 63245986

	unsigned long * fibonacci_result = fibonacci_array(39);
	// l'array restituito da fibonacci_array(n) ha dimensione n+1

	for (i = 0; i <= 39; i++)
		printf("fib(%i)=%lu\n", i, fibonacci_result[i]);

	printf("\n");

	// fare una copia dell'array fibonacci_result in 'fibonacci_result_copy' (i due array devono avere aree di memoria distinte)
	unsigned long * fibonacci_result_copy = malloc( 40 * sizeof(unsigned long));

	if (fibonacci_result_copy == NULL) {
		exit(EXIT_FAILURE);
	}

	printf("copio fibonacci_result in fibonacci_result_copy\n\n");
	memcpy(fibonacci_result_copy, fibonacci_result, 40 * sizeof(unsigned long));

	// fibonacci_result_copy: fare il 'reverse' dell'array ('copiare' da esempio 004.1arrays-operations)
	printf("reverse di fibonacci_result_copy\n");
	complete_reverse_unsigned_long(fibonacci_result_copy, 40);

	for (i = 0; i <= 39; i++)
		printf("array(%i)=%lu\n", i, fibonacci_result_copy[i]);

	printf("\n");

	// su fibonacci_result_copy: applicare bubble_sort ('copiare' da esempio 004.1arrays-operations)
	printf("sort di fibonacci_result_copy\n");
	bubble_sort_unsigned_long(fibonacci_result_copy, 40);

	for (i = 0; i <= 39; i++)
		printf("array(%i)=%lu\n", i, fibonacci_result_copy[i]);

	printf("\n");

	// confrontare fibonacci_result e fibonacci_result_copy, verificare che i due array siano uguali (scrivere su stdout il risultato).
	int equal = 1;
	for (unsigned int i = 0; i <= 39; i++) {
		if (fibonacci_result_copy[i] != fibonacci_result[i]) {
			equal = 0;
			break; // esci da ciclo for
		}
	}

	printf("i due array fibonacci_result e fibonacci_result_copy sono uguali? %s\n",
			equal ? "SI" : "NO");

	// se il programma continuasse ed avesse bisogno di liberare le risorse,
	// allora bisogna liberare gli array che non servono più
	free(fibonacci_result);
	free(fibonacci_result_copy);

	printf("\nfinito!\n");

	return 0;
}

void swap_unsigned_long(unsigned long *x, unsigned long *y) {
	unsigned long t = *x;
	*x = *y;
	*y = t;
}

unsigned long * reverse_unsigned_long(unsigned long * array, unsigned int i, unsigned int j)
{
	while (i < j)
		swap_unsigned_long(&array[i++], &array[--j]);

	return array;
}

void complete_reverse_unsigned_long(unsigned long * array, unsigned int array_len) {
	reverse_unsigned_long(array, 0, array_len);
}

void bubble_sort_unsigned_long(unsigned long * array, unsigned int array_dimension) {
	unsigned int n = array_dimension;
	unsigned int newn;
	do {
		newn = 0;
		for (unsigned int i = 1; i < n; i++) {
			if (array[i-1] > array[i]) {
				swap_unsigned_long(&array[i-1], &array[i]);
				newn = i;
			}

		}

		n = newn;

	} while (n > 1);
}
