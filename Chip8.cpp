#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

class Chip8 {

public:
    uint8_t registers[16]{}; // 16 8-bit registers
    uint8_t memory[4096]{}; // 4096 bytes (1 byte = 8 bit) of memory
    uint16_t index{}; // 16 bit index register
    uint16_t pc{}; // 16 bit program counter
    uint16_t stack[16]{}; // 16 level stack able to hold 16 different PCs contains addresses
    uint8_t sp{}; // 8 bit stack pointer
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad[16]{};
    uint32_t video[64 * 32]{};
    uint16_t opcode;

    // const unsigned int START_ADDRESS = 0x200;
    // const unsigned int FONTSET_SIZE = 80;
    // const unsigned int FONTSET_START_ADDRESS = 0x50;

    static constexpr unsigned int START_ADDRESS = 0x200;
    static constexpr unsigned int FONTSET_SIZE = 80;
    static constexpr unsigned int FONTSET_START_ADDRESS = 0x50;

    default_random_engine randGen;
	uniform_int_distribution<uint8_t> randByte;

    /*
    static constexpr guarantees compile time initialisation and forces the value to be compile time constant
    const only quarantees run time immutability
    */

    uint8_t fontset[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    Chip8() 
        : randGen(std::chrono::system_clock::now().time_since_epoch().count())
        /*
        this is a constructor member initialiser list
        initialises members as object is being built before {} body runs
        Order of event:
        1. Allocate Object
        2. Run initialiser (ranGen gets seeded)
        3. Run the constructor body {}
        */
    {
        pc = START_ADDRESS;

        // Load fonts into memory
        for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
        {
            memory[FONTSET_START_ADDRESS + i] = fontset[i];
        }

        randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
        // configures randByte to produce integers from 0 to 255

    }

    void LoadROM(char const* filename) {
        // Open the file as a stream of binary and move the file pointer to the end
        std::ifstream file(filename, std::ios::binary | std::ios::ate);

        if (file.is_open())
        {
            // Get size of file and allocate a buffer to hold the contents
            std::streampos size = file.tellg();
            char* buffer = new char[size];

            // Go back to the beginning of the file and fill the buffer
            file.seekg(0, std::ios::beg);
            file.read(buffer, size);
            file.close();

            // Load the ROM contents into the Chip8's memory, starting at 0x200
            for (long i = 0; i < size; ++i)
            {
                memory[START_ADDRESS + i] = buffer[i];
            }

            // Free the buffer
            delete[] buffer;
        }
    }



};



int main() {



    
    return -1;

}