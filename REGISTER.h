#ifndef REGISTER_H
#define REGISTER_H

#include <bits/stdc++.h>
using namespace std;

// Class representing a Register which can hold multiple values
class Register {
private:
    // Vector to store register values as strings
    vector<string> regs;

public:
    // Constructor that initializes the register with a specified size (default is 16) and fills it with "00"
    Register(int size = 16) {
        regs = vector<string>(size, "00");
    }

    // Method to get the value of a register at a specific index
    string get(int index) {
        return regs[index];
    }

    // Method to set the value of a register at a specific index
    void set(int index, string value) {
        regs[index] = value;
    }

    // Method to display the values of all registers
    void display() {
        for (int i = 0; i < regs.size(); i++) {
            cout << "Register " << i << ": " << regs[i] << "\n"; // Output the value of each register
        }
    }
};

#endif
