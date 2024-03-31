#include "RAM.h"

RAM::RAM()
{
    // Constructor implementation
    memory.resize(2 * 1024, 0);
    dump_memory();
}

RAM::~RAM()
{
    // Destructor implementation
    memory.clear();
}

// Additional method to read a byte at a specific address
uint8_t RAM::readByte(uint16_t address) const
{
    if (address < memory.size())
    {
        // Check if the address is within the valid range
        return memory[address];
    }
    else
    {
        // Handle out-of-bounds access
        std::cerr << "Error: Attempted to read from invalid memory address." << std::endl;
        return 0xFF; // Return a default value 
    }
}
void RAM::writeInstructionByte(uint16_t address, uint8_t value)
{
    
    // TODO: 
    // First, check if the address is within the allocated memory address space. If it is not, throw an error.
    // Second, Check if address is within the first 256 bytes allocated for instructions. 
    // If it is, set the value in memory at that location to the value passed in as an argument
    // Throw an error otherwise
    // Hint: use memory.size()
        
    
    dump_memory();
}

void RAM::writeStackByte(uint16_t address, uint8_t value)
{
    // TODO: 
    // First, check if the address is within the allocated memory address space. If it is not, throw an error.
    // Second, Check if address is within the second 256 bytes allocated for the stack. 
    // If it is, set the value in memory at that location to the value passed in as an argument
    // Throw an error otherwise
    // Hint: use memory.size()

    dump_memory();
}

void RAM::writeByte(uint16_t address, uint8_t value)
{
    // TODO: 
    // First, check if the address is within the allocated memory address space. If it is not, throw an error.
    // Second, Check if address is within the second last 1536 bytes allocated for the rest of memory. 
    // If it is, set the value in memory at that location to the value passed in as an argument
    // Throw an error otherwise
    // Hint: use memory.size()

    dump_memory();
}

void RAM::dump_memory_at_address(uint16_t address, std::ostream& out) const {
    // Every 16 bytes, create a line of dump output in hexadecimal
    // Print starting address of bytes in this line of output
    out << "Address 0x" << std::hex << std::setw(4) << address << ": ";

    // Print sixteen bytes in memory from starting address
    for (int i = 0; i < 64; i++) {
        if (address + i < memory.size()) {
            uint8_t byte = readByte(address + i);
            out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        } else {
            // Print spaces for empty spaces in the last line
            out << "   ";
        }
    }

    // Print ASCII representation for each byte
    out << "| ";
    for (int i = 0; i < 64; i++) {
        if (address + i < memory.size()) {
            uint8_t byte = readByte(address + i);
            // Display printable characters, otherwise show a dot
            char printableChar = (byte >= 32 && byte <= 126) ? static_cast<char>(byte) : '.';
            out << printableChar;
        } else {
            // Print spaces for empty spaces in the last line
            out << " ";
        }
    }

    out << std::endl;
}


void RAM::dump_memory() const {
    const int bytesPerLine = 16;
    
    // Open file for writing
    std::ofstream outFile("RAM.txt");
    
    // Check if file opened successfully
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    // Iterate over each byte in memory and print in groups of 16 bytes per line
    for (uint16_t address = 0; address < memory.size(); address += 4 * bytesPerLine) {
        dump_memory_at_address(address, outFile);
    }
    
    // Close the file stream
    outFile.close();
}