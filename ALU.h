#ifndef ALU_H
#define ALU_H

#include <bits/stdc++.h>
using namespace std;

// Class representing an Arithmetic Logic Unit (ALU) for performing arithmetic operations
class ALU {
public:
    // Converts a hexadecimal string to a signed integer based on the specified bit size
    int hexToSignedInt(string hexStr, int bitSize = 8) {
        int num = stoi(hexStr, nullptr, 16); // Convert hex string to integer
        int maxVal = (1 << (bitSize - 1));   // Calculate maximum positive value for given bit size
        if (num >= maxVal) {
            num -= (1 << bitSize); // Adjust for negative values
        }
        return num; // Return the signed integer
    }

    // Converts a signed integer to a hexadecimal string based on the specified bit size
    string signedIntToHex(int num, int bitSize = 8) {
        if (num < 0) {
            num += (1 << bitSize); // Adjust negative numbers to their unsigned equivalent
        }
        stringstream ss;
        ss << hex << uppercase << setfill('0') << setw(bitSize / 4) << num; // Format to hex
        return ss.str(); // Return the hexadecimal string
    }

    // Adds two hexadecimal strings and returns the result as a hexadecimal string
    string add(string a, string b) {
        int num_a = hexToSignedInt(a); // Convert first hex string to signed int
        int num_b = hexToSignedInt(b); // Convert second hex string to signed int
        int sum = num_a + num_b;        // Calculate the sum
        return signedIntToHex(sum);     // Convert the result back to hex and return
    }

    // Adds two floating-point numbers represented as hexadecimal strings
    string addFloat(string a, string b) {
        // Convert hex strings to integers
        int hexint1 = stoi(a, nullptr, 16);
        int hexint2 = stoi(b, nullptr, 16);

        // Extract components for the first number
        int sign1 = (hexint1 >> 7) & 0x1;             // Extract sign bit
        int exponent1 = ((hexint1 >> 4) & 0x7) - 4;   // Extract exponent (3 bits) and adjust bias
        int mantissa1 = hexint1 & 0xF;                 // Extract mantissa (4 bits)

        // Extract components for the second number
        int sign2 = (hexint2 >> 7) & 0x1;             // Extract sign bit
        int exponent2 = ((hexint2 >> 4) & 0x7) - 4;   // Extract exponent (3 bits) and adjust bias
        int mantissa2 = hexint2 & 0xF;                 // Extract mantissa (4 bits)

        // Add implicit leading 1 to mantissas (for normalized form)
        if (exponent1 != -4) mantissa1 |= 0x10; // Add leading 1 if not denormalized
        if (exponent2 != -4) mantissa2 |= 0x10; // Add leading 1 if not denormalized

        // Align exponents by shifting the mantissa of the smaller exponent
        while (exponent1 < exponent2) {
            mantissa1 >>= 1; // Shift mantissa1 right to align with exponent2
            exponent1++;
        }
        while (exponent2 < exponent1) {
            mantissa2 >>= 1; // Shift mantissa2 right to align with exponent1
            exponent2++;
        }

        // Perform addition or subtraction based on signs
        int resultMantissa;
        int resultExponent = exponent1; // Now they are the same
        int resultSign = sign1;          // Default to sign1, might change based on subtraction

        if (sign1 == sign2) {
            resultMantissa = mantissa1 + mantissa2; // Add mantissas if signs are the same
        } else {
            if (mantissa1 >= mantissa2) {
                resultMantissa = mantissa1 - mantissa2; // Subtract mantissas if sign1 >= sign2
            } else {
                resultMantissa = mantissa2 - mantissa1; // Subtract mantissas if sign2 > sign1
                resultSign = sign2; // Set result sign to sign2
            }
        }

        // Normalize the result
        if (resultMantissa & 0x10) { // Check for overflow in mantissa (5th bit set)
            resultMantissa >>= 1; // Shift right if overflow
            resultExponent++; // Increase exponent
        } else {
            while ((resultMantissa & 0x8) == 0 && resultExponent > -4) { // Underflow normalization
                resultMantissa <<= 1; // Shift left to normalize
                resultExponent--; // Decrease exponent
            }
        }

        // Remove implicit leading 1 if exponent is not denormalized
        if (resultExponent != -4) {
            resultMantissa &= 0xF; // Clear the leading 1
        }

        // Handle exponent overflow/underflow
        if (resultExponent > 3) { // Exponent overflow
            resultExponent = 3; // Cap to maximum
            resultMantissa = 0xF; // Set to maximum representable value
        } else if (resultExponent < -4) { // Exponent underflow
            resultExponent = -4; // Cap to minimum
            resultMantissa = 0; // Set to zero for underflow
        }

        // Repack result into 8-bit floating-point format
        int packedResult = (resultSign << 7) | ((resultExponent + 4) << 4) | resultMantissa;

        // Convert packed result to hexadecimal string
        stringstream ss;
        ss << hex << uppercase << setfill('0') << setw(2) << packedResult; // Format to hex
        return ss.str(); // Return the hexadecimal string result
    }
};

#endif
