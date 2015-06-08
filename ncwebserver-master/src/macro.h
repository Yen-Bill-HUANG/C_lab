#ifndef NCWEBSERVER_MACRO_H
#define NCWEBSERVER_MACRO_H

// Expands to check if the value is between
// min and max, not inclusive.
#define between(i, min, max) \
    (i > min && i < max)

// Expands to check if the value is between
// min and max, inclusive. For example, we use
// this macro to check if a port number is within
// the range of port numbers, [0, 2^16 - 1].
#define in_range(i, min, max) \
    (i >= min && i <= max)

#endif