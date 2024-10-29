#ifndef MEMORY_H
#define MEMORY_H

#include <bits/stdc++.h>
using namespace std;

// Class representing memory that can hold multiple values
class Memory {
private:
    // Vector to store memory values as strings
    vector<string> mem;

public:
    // Constructor that initializes the memory with a specified size (default is 256) and fills it with "00"
    Memory(int size = 256) {
        mem = vector<string>(size, "00");
    }

    // Method to get the value from memory at a specific index
    string get(int index) {
        return mem[index];
    }

    // Method to set the value in memory at a specific index
    void set(int index, string value) {
        mem[index] = value;
    }

    // Method to display the values of all memory locations
    void display() {
        for (int i = 0; i < mem.size(); i++) {
            cout << "Memory " << i << ": " << mem[i] << "\n"; // Output the value of each memory location
        }
    }
};

#endif
