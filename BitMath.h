#ifndef BITMATH_H
#define BITMATH_H

#define SET_BIT(reg, bit) ((reg) |= (1 << (bit)))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1 << (bit)))
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit)))
#define GET_BIT(reg, bit) (((reg) >> (bit)) & 0x01)

#endif /* BITMATH_H */