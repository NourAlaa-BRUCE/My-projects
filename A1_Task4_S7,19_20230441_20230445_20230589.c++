// File: A1_Task4_S7,19_20230441_20230445_20230589.c++

// Purpose: Vole Machine program

// Author1: Nada Samir Hanfy Ahmed, ID: 20230441
// Author2: Nour Alaa Hasan, ID: 20230445
// Author3: Husam Abdelhady Zaid, ID: 20230589

// Date: 3/11/2024

// Sectoin: S7,19


#include <bits/stdc++.h> // Include all standard libraries like <iostream>, <fstream>, <vector>
#include "CPU.h" // Include the CPU class definitions to use it within VoleMachine

using namespace std;

class VoleMachine {
private:
    CPU cpu; // CPU object used to simulate machine instructions

public:
    void run() {
        cout << "Please input the file name such as (your file name.txt): ";
        string file_name, word;
        cin >> file_name; // Get the file name from user input
        ifstream file(file_name); // Open the file for reading

        vector<string> instructions; // Vector to store instructions loaded from the file
        while (file >> word) { // Read each word (instruction) from the file
            instructions.push_back(word);
        }

        int programCounter = 0; 
        int i = 0;
        // Start executing instructions in a loop until reaching the end of instructions or encountering an exit signal
        while (programCounter < instructions.size() && !cpu.isExit()) {
            cpu.executeInstruction(instructions[programCounter], i); // Execute the current instruction
            i += 2; // Increment by 2 because each instruction is split into two memory cells
            programCounter = cpu.isExit() ? programCounter : programCounter + 1; // Update program counter or exit if CPU signals exit
            cpu.setProgramCounter(programCounter); // Set the updated program counter in the CPU
        }

        cpu.displayState(); // Display the state of CPU memory and registers after execution ends
    }
};

int main() {
    VoleMachine vm; // Create an instance of VoleMachine
    vm.run(); // Run the VoleMachine instance, starting the instruction execution

    return 0;
}

