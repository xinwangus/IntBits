#include <stdio.h>
#include <iostream>

// Swap all bits in an int.
// method one is much better.

// method one. use a temp int
void
revertBits1(unsigned int& a)
{
	unsigned int temp = 0;
	int shift_count = sizeof(a)*8 - 1 ;

	// take care of last bit before we do any shift.
	if (a & 1) {
		temp = 1;
	}

	while (shift_count) {
		a = a >> 1;
		temp = temp << 1;
		shift_count--;

		if (a & 1) {
			temp += 1;
		}
	}
	a = temp;
}

// method two, do it in place.
// helper functions
void
_setBit (unsigned int& a, unsigned int p)
{
	if (p >= sizeof(a)*8) { return; }
	a |= (1 << (p));
}

void
_unsetBit (unsigned int& a, unsigned int p)
{
	if (p >= sizeof(a)*8) { return; }
	a &= ~(1 << (p));
}

static
bool
_isBitSet (unsigned int& a, unsigned int p)
{
	if (p >= sizeof(a)*8) { return false; }
	if (a & (1 << (p))) {
		return true;
	} else {
		return false;
	}
}

void
revertBits2(unsigned int& a)
{
	int s = sizeof(a)*8; 
	bool left, right;

	for (int i = 0; i < s/2; i++) {
		left = _isBitSet(a, (s-1-i));
		right = _isBitSet(a, i);

		// already the same, no need to swap.
		if (left == right) { continue; }
	
		// need to change.
		if (left) {
			_unsetBit(a, (s-1-i));
		} else {
			_setBit(a, (s-1-i));
		}

		// need to change.
		if (right) {
			_unsetBit(a, i);
		} else {
			_setBit(a, i);
		}
	}
}

bool
areBitMirrored(unsigned int& a, unsigned int& b)
{
	int s = sizeof(a)*8; 
	bool left, right;

	// do a bit-by-bit check.
	for (int i = 0; i < s; i++) {
		left = _isBitSet(a, i);
		right = _isBitSet(b, s-1-i);
		if (left != right) { return false; }
	}
	return true;
}


// Change the endian-ness of an integer.
// using shift and an byte bit-mask.
static unsigned int
change_endian(unsigned int a)
{
	int shift = sizeof(a) - 1;
	unsigned int ret = 0;

	// before we shift, take the last byte.
	ret = a & 0xff;

	while (shift) {
		a = a >> 8;
		ret = ret << 8;
		shift--;
		ret |= (a & 0xff);
	}
	return ret;
}

int
main()
{
	unsigned int input;
	unsigned int input1;
	unsigned int input2;

	while (true) {
		std::cout << "Please input an positive int: ";
 		std::cin >> input;
		printf("Input in hex: 0x%x\n", input);
		printf("change_endian result in hex: 0x%x\n",
			change_endian(input));

		std::cout << std::endl;
		input1 = input;
		revertBits1(input1);
		std::cout << "revertBits1 result:" << input1;
		printf("\nrevertBits1 result in hex: 0x%x\n", input1);

		std::cout << "input and Result1 are mirrored:"
			  << areBitMirrored(input, input1);

		input2 = input;
		revertBits2(input2);
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "revertBits2 result:" << input2;
		printf("\nrevertBits2 result in hex: 0x%x\n", input2);

		std::cout << "input and Result2 are mirrored:"
			  << areBitMirrored(input, input2);

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "-----------" << std::endl;
	}
}

