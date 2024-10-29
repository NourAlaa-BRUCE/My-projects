#ifndef CPU_H
#define CPU_H

#include <bits/stdc++.h> // Include standard libraries
#include "REGISTER.h"    // Include Register class
#include "MEMORY.h"      // Include Memory class
#include "ALU.h"         // Include ALU class for arithmetic and logical operations

using namespace std;

class CPU {
private:
    Register reg;         // Register object to handle register operations
    Memory mem;           // Memory object to handle memory operations
    ALU alu;              // ALU object for arithmetic and logical operations
    bool exitFlag = false; // Flag to check if the CPU should stop execution
    int programCounter = 0; // Holds the address of the next instruction

public:
    // Constructor initializes the Register, Memory, and ALU objects
    CPU() : reg(), mem(), alu() {}

    // Executes an instruction at a given index in memory
    void executeInstruction(string instruction, int index) {
        string opcode = instruction.substr(0, 1); // Extract operation code
        string R = instruction.substr(1, 1);      // Extract register identifier
        string XY = instruction.substr(2, 2);     // Extract memory location or immediate value

        int i_R = stoi(R, nullptr, 16);           // Convert register identifier to integer
        int i_XY = stoi(XY, nullptr, 16);         // Convert memory location/immediate value to integer
        mem.set(index, opcode+R);                 // Set memory cell with opcode and register identifier
        mem.set(index+1, XY);                     // Set following memory cell with XY value

        if (opcode == "1") {                      // Load from memory
            reg.set(i_R, mem.get(i_XY));
        } 
        else if (opcode == "2") {                 // Load immediate value to register
            reg.set(i_R, XY);
        } 
        else if (opcode == "3") {                 // Output register or store to memory
            if (XY == "00") {
                cout << reg.get(i_R) << "\n";     // Output register contents
            } else {
                mem.set(i_XY, reg.get(i_R));      // Store register contents in memory
            }
        } 
        else if (opcode == "4") {                 // Copy between registers
            int r = stoi(XY.substr(0, 1), nullptr, 16);
            int s = stoi(XY.substr(1, 1), nullptr, 16);
            reg.set(s, reg.get(r));
        } 
        else if (opcode == "5") {                 // Integer addition
            int s = stoi(XY.substr(0, 1), nullptr, 16);
            int t = stoi(XY.substr(1, 1), nullptr, 16);
            reg.set(i_R, alu.add(reg.get(s), reg.get(t)));
        }
        else if (opcode == "6") {                 // Floating-point addition
            int s = stoi(XY.substr(0, 1), nullptr, 16);
            int t = stoi(XY.substr(1, 1), nullptr, 16);
            reg.set(i_R, alu.addFloat(reg.get(s), reg.get(t)));
        }
        else if (opcode == "B") {                 // Conditional branch
            int r = stoi(R, nullptr, 16);
            if (reg.get(r) == reg.get(0)) {
                programCounter = i_XY;            // Update program counter for branching
            }
        }
        else if (opcode == "C") {                 // Exit instruction
            exitFlag = true;
        } 
        else {                                    // Invalid opcode handling
            cout << "Invalid operation code\n";
        }
    }

    // Check if the CPU has encountered an exit instruction
    bool isExit() {
        return exitFlag;
    }

    // Get the current program counter value
    int getProgramCounter() {
        return programCounter;
    }

    // Set a new value for the program counter
    void setProgramCounter(int newPC) {
        programCounter = newPC;
    }

    // Display the current state of memory and registers
    void displayState() {
        mem.display();
        cout << "========================\n";
        reg.display();
    }
};

#endif
