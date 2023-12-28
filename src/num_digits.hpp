#ifndef NUM_DIGITS_H
#define NUM_DIGITS_H

#include<concepts>

template <std::integral T>
int numDigits(T num) {
	int d = 0;
	while (num != 0) {
		d += 1;
		num /= 10;
	}
	return d;
}


#endif // NUM_DIGITS_H