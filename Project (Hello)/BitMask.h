#pragma once

#include <cstdint>

class BitMask {
public:
	BitMask();
	~BitMask();

	/* Get-Set Whole Mask */
	void setBitMask(BitMask&);
	uint32_t getBitMask() const;

	/* Set-Get bit at specified position */
	bool getBit(int) const;
	void setBit(int, bool);

	/* Set all bits to 0 */
	void clear();
	
private:
	uint32_t mask;
};

