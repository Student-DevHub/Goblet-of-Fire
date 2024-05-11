#include "BitMask.h"

BitMask::BitMask() 
	: mask(0) {

}

BitMask::~BitMask() {

}

void BitMask::setBitMask(BitMask& other) {
	mask = other.getBitMask();
}

uint32_t BitMask::getBitMask() const {
	return mask;
}

bool BitMask::getBit(int position) const {
	return (mask & (1 << position)) != 0;
}

void BitMask::setBit(int position, bool value) {
	mask = mask & ~(1 << position) | (value << position);
	
	/*
	if (value)
		mask = mask | 1 << position;
	else
		mask = mask & ~(1 << position);
	*/
}

void BitMask::clear() {
	mask = 0;
}
