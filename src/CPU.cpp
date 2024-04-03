#include "CPU.h"
#include <iostream>

CacheRegister cache[3];
uint16_t PC;    // 16-bit Program Counter
uint16_t SP;    // 8-bit Stack Pointer
uint8_t A;      // 8-bit Accumulator

CPU::CPU()
{
    PC = 0;
    SP = 0x100;
    A = 0;
    // Constructor implementation
}

CPU::~CPU()
{
    // Destructor implementation
}

void CPU::updateCache(uint16_t location, uint8_t value)
{
    // TODO: Implement Cache Policy when location is already in cache
    // Check if the location already exists in the cache
    

    // TODO: Implement Cache Policy when location is not in cache
    // If the location doesn't exist in the cache, find the cache register with the smallest location to replace
    int mostRecentCacheRegister = 0;
    

    // Update the selected cache register with the new location and value
    cache[mostRecentCacheRegister].location = location;
    cache[mostRecentCacheRegister].value = value;
}

uint8_t CPU::getCachedValue(uint16_t location)
{
    // Check if the location exists in the cache
    for (int i = 0; i < 3; i++)
    {
        if (cache[i].location == location)
        {
            // If the location exists, return its cached value
            return cache[i].value;
        }
    }

    // If the location doesn't exist in the cache, return 0 (cache miss)
    return 0;
}

void CPU::process_instructions(RAM &ram, uint16_t start_address, uint16_t end_address)
{
    PC = start_address;

    // Fetch-Execute Cycle
    while (PC < end_address)
    {
        // Fetch 1 byte for opcode from RAM
        uint8_t opcode = ram.readByte(PC);

        // Fetch 2 bytes for address from RAM
        uint16_t address = 0;
        // address |= static_cast<uint16_t>(ram.readByte(PC + 1)) << 0;
        // address |= static_cast<uint16_t>(ram.readByte(PC + 2)) << 8;
        address = static_cast<uint16_t>(ram.readByte(PC + 1)) | address << 0;
        address = static_cast<uint16_t>(ram.readByte(PC + 2)) | address << 8;

        std::cout << "Opcode: 0x" << std::hex << static_cast<int>(opcode) << ", Address: 0x" << address << std::endl;

        // Decode and execute the instruction
        executeInstruction(ram, opcode, address);

        // Move to the next instruction
        PC += 3;
    }
}

void CPU::executeInstruction(RAM &ram, uint8_t opcode, uint16_t address)
{
    std::cout << "Executing CPU instruction: < ";

    // Print the instruction in binary
    for (int i = 15; i >= 0; --i)
    {
        std::cout << ((address >> i) & 1);
    }
     std::cout << " >";
    std::cout << std::endl;

    // Execute instructions based on the opcode
    switch (opcode)
    {
    case 0b0000: // Handle instructions with opcode starting with '0000'
        ADC(ram, address);
        break;
    case 0b0001: // Handle instructions with opcode starting with '0001'
        SBC(ram, address);
        break;
    case 0b0010: // Handle instructions with opcode starting with '0010'
        LDA(ram, address);
        break;
    case 0b0011: // Handle instructions with opcode starting with '0011'
        AND(ram, address);
        break;
    case 0b0100: // Handle instructions with opcode starting with '0100'
        EOR(ram, address);
        break;
    case 0b0101: // Handle instructions with opcode starting with '0101'
        JMP(ram, address);
        break;
    case 0b0110: // Handle instructions with opcode starting with '0110'
        PSH(ram);
        break;
    case 0b0111: // Handle instructions with opcode starting with '0111'
        POP(ram);
        break;
    default:
        std::cerr << "NOP Unsupported opcode: " << std::bitset<3>(opcode) << std::endl;
        // Handle unsupported opcode
        break;
    }

   
}

void CPU::ADC(RAM &ram, uint16_t address)
{
    uint8_t value = getCachedValue(address);
    if (value == 0)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }

    // TODO: Adding the value to the accumulator
    uint8_t result = 0; 

    // TODO: Writing the result back to memory at the same address
    
    updateCache(address, result & 0xFF);
    // Displaying the operation
    std::cout << "ADC instruction executed. Result stored at memory address: " << std::hex << static_cast<int>(address) << std::endl;
}

void CPU::SBC(RAM &ram, uint16_t address)
{
    uint8_t value = getCachedValue(address);
    if (value == 0)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }

    // TODO: Subtracting the accumulator from the value
    uint8_t result = 0; 

    // TODO: Writing the result back to memory at the same address
    
    updateCache(address, result & 0xFF);

    // Displaying the operation
    std::cout << "SBC instruction executed. Result stored at memory address: " << std::hex << static_cast<int>(address) << std::endl;
}

void CPU::LDA(RAM &ram, uint16_t address)
{
    uint8_t value = getCachedValue(address);
    if (value == 0)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }

    // TODO: Loading the value into the accumulator (A register)
    A = value;

    updateCache(address, value);

    // Displaying the operation
    std::cout << "LDA instruction executed. Value loaded into accumulator (A): " << std::hex << static_cast<int>(A) << std::endl;
}

void CPU::AND(RAM &ram, uint16_t address)
{
    uint8_t value = getCachedValue(address);
    if (value == 0)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }
    updateCache(address, value);

    // TODO: bitwise AND operation between the accumulator (A) and the value
    

    // Displaying the operation
    std::cout << "AND instruction executed. Result stored in accumulator (A): " << std::hex << static_cast<int>(A) << std::endl;
}

void CPU::EOR(RAM &ram, uint16_t address)
{
    uint8_t value = getCachedValue(address);
    if (value == 0)
    {
        value = ram.readByte(address); // Reading the value from memory at the specified address
    }

    // TODO: Performing bitwise XOR (Exclusive OR) operation between the accumulator (A) and the value
    

    // Displaying the operation
    std::cout << "EOR instruction executed. Result stored in accumulator (A): " << std::hex << static_cast<int>(A) << std::endl;
}

void CPU::JMP(RAM &ram, uint16_t address)
{
    // TODO: Set the program counter (PC) to the extracted address


    // Displaying the operation
    std::cout << "JMP instruction executed. Jumping to address: " << std::hex << static_cast<int>(address) << std::endl;
}

void CPU::PSH(RAM &ram)
{
    // TODO: Write the accumulator (A) value to the stack at memory location SP
    

    // TODO: Increment the stack pointer (SP)


    // Displaying the operation
    std::cout << "PSH instruction executed. Accumulator value pushed onto stack." << std::endl;
}

void CPU::POP(RAM &ram)
{
    

    // TODO: Read the value from the stack at memory location SP into the accumulator (A)
    
    // TODO: Decrement the stack pointer (SP)

    // Displaying the operation
    std::cout << "POP instruction executed. Accumulator value popped from stack." << std::endl;
}
