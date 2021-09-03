#include "../../kernel/interfaces/BasicRenderer/cstr.h"

char uint_to_string_output[128];
const char *ToString(uint64_t value)
{

    uint8_t size;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while (value / 10 > 0)
    {
        uint8_t remainder = value % 10;
        value /= 10;
        uint_to_string_output[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    uint_to_string_output[size - index] = remainder + '0';
    uint_to_string_output[size + 1] = 0;
    return uint_to_string_output;
}

char int_to_string_output[128];
const char *ToString(int64_t value)
{
    uint8_t isNegative = 0;

    if (value < 0){
        isNegative = 1;
        value *= -1;
        int_to_string_output[0] = '-';
    }

    uint8_t size;
    uint64_t sizeTest = value;
    while (sizeTest / 10 > 0){
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while(value / 10 > 0){
        uint8_t remainder = value % 10;
        value /= 10;
        int_to_string_output[isNegative + size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    int_to_string_output[isNegative + size - index] = remainder + '0';
    int_to_string_output[isNegative + size + 1] = 0; 
    return int_to_string_output;
}
