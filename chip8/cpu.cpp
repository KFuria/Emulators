#include <cstdlib>
#include <ctime> 

#include "cpu.h"

TCpu::TCpu(TChip8* machine){
    logger = TLogger::getInstance();
    chip8 = machine;    
}

TCpu::~TCpu(){

}

void TCpu::init(){
    // Initialize registers
    I = 0;
    pc = PC_START;
    sp = 0;
    for(int i = 0; i < NUM_REGISTERS; i++){
        reg[i] = 0;
    }
    opcode = 0;
    instruction = 0;
}

void TCpu::cycle(){
    // fetch
    opcode = ((uint16_t)chip8->memory[pc] << 8) | chip8->memory[pc+1]; 
    pc += 2;

    // std::stringstream buff;
    // buff << "PC:" << std::hex << pc << " ";
    // buff << "SP:" << sp << " ";
    // buff << "I:" << I << " ";
    // buff << "OPCODE:" << std::hex << opcode << " ";
    // for(auto i = 0; i<NUM_REGISTERS; i++){
    //     buff << "R" << i << ":" << std::to_string(reg[i]) << " ";
    // }
    // std::string s = buff.str();
    // logger->log(s, ELogLevel::DEBUG);

    // execute
    instruction = opcode >> 12; //decode
    switch(instruction){
        case 0x0: OP_0();       break;
        case 0x1: OP_1NNN();    break;
        case 0x2: OP_2NNN();    break;
        case 0x3: OP_3XNN();    break;
        case 0x4: OP_4XNN();    break;
        case 0x5: OP_5XY0();    break;
        case 0x6: OP_6XNN();    break;
        case 0x7: OP_7XNN();    break;
        case 0x8: OP_8();       break;
        case 0x9: OP_9XY0();    break;
        case 0xA: OP_ANNN();    break;
        case 0xB: OP_BNNN();    break;
        case 0xC: OP_CXNN();    break;
        case 0xD: OP_DXYN();    break;
        case 0xE: OP_E();       break;
        case 0xF: OP_F();       break;
        default: logger->log("INVALID INSTRUCTION" + std::to_string(instruction), ELogLevel::ERROR);
    }

}

void TCpu::deinit(){

}


// 00EZ
inline void TCpu::OP_0(){
    switch(opcode & 0xFF){
        case 0xE0: OP_00E0(); break;
        case 0xEE: OP_00EE(); break;
        default: logger->log("INVALID CODE: 00" + std::to_string(opcode & 0xFF), ELogLevel::ERROR);
    }
}

// 8XYZ
inline void TCpu::OP_8(){
    switch (opcode & 0xF){
        case 0x0: OP_8XY0(); break;
        case 0x1: OP_8XY1(); break;
        case 0x2: OP_8XY2(); break;
        case 0x3: OP_8XY3(); break;
        case 0x4: OP_8XY4(); break;
        case 0x5: OP_8XY5(); break;
        case 0x6: OP_8XY6(); break;
        case 0x7: OP_8XY7(); break;
        case 0xE: OP_8XYE(); break;
        default: 
            logger->log("INVALID CODE: 8XY" + std::to_string(opcode & 0xF), ELogLevel::ERROR);
    }
}

// EXZZ
inline void TCpu::OP_E(){
    switch(opcode & 0xFF){
        case 0x9E: OP_EX9E(); break;
        case 0xA1: OP_EXA1(); break;
        default: 
            logger->log("INVALID CODE: EX" + std::to_string(opcode & 0xFF), ELogLevel::ERROR);
    }
}

// FXZZ
inline void TCpu::OP_F(){
    switch(opcode & 0xFF){
        case 0x07: OP_FX07(); break;
        case 0x0A: OP_FX0A(); break;
        case 0x15: OP_FX15(); break;
        case 0x18: OP_FX18(); break;
        case 0x1E: OP_FX1E(); break;
        case 0x29: OP_FX29(); break;
        case 0x33: OP_FX33(); break;
        case 0x55: OP_FX55(); break;
        case 0x65: OP_FX65(); break;
        default: 
            logger->log("INVALID CODE: FX" + std::to_string(opcode & 0xFF), ELogLevel::ERROR);
    }
}


// 00E0: Clear the display
inline void TCpu::OP_00E0(){
    for(int i = 0; i < SCREEN_HEIGHT; i++){
        for(int j = 0; j < SCREEN_WIDTH; j++){
            chip8->screen[i][j] = 0;
        }
    }
}

// 00EE: Return from a subroutine
inline void TCpu::OP_00EE(){
    sp--;
    pc = chip8->stack[sp];
}

// 1NNN: Jump to location NNN
inline void TCpu::OP_1NNN(){
    pc = opcode & 0x0FFF;
}

// 2NNN: Call subroutine at NNN
inline void TCpu::OP_2NNN(){
    uint16_t nnn = opcode & 0x0FFF;
    chip8->stack[sp] = pc;
    sp++;
    pc = nnn;
}

// 3XNN: Skip next instruction if Vx = NN
inline void TCpu::OP_3XNN(){
    uint8_t kk = opcode & 0x00FF;
    uint8_t x = (opcode >> 8) & 0x0F;
    if(kk == reg[x])
        pc+=2;
}

// 4XNN: Skip next instruction if Vx != NN
inline void TCpu::OP_4XNN(){
    uint8_t kk = opcode & 0x00FF;
    uint8_t x = (opcode >> 8) & 0x0F;
    if(kk != reg[x])
        pc+=2;
}

// 5XY0: Skip next instruction if Vx = Vy
inline void TCpu::OP_5XY0(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    if(reg[x] == reg[y])
        pc+=2;
}

// 6XNN: Set Vx = NN
inline void TCpu::OP_6XNN(){
    uint8_t kk = opcode & 0x00FF;
    uint8_t x = (opcode >> 8) & 0xF;
    reg[x] = kk;
}

// 7XNN: Set Vx = Vx + NN
inline void TCpu::OP_7XNN(){
    uint8_t kk = opcode & 0x00FF;
    uint8_t x = (opcode >> 8) & 0x0F;
    reg[x] = reg[x] + kk;
}

// 8XY0: Set Vx = Vy
inline void TCpu::OP_8XY0(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    reg[x] = reg[y];
}

// 8XY1: Set Vx = Vx OR Vy
inline void TCpu::OP_8XY1(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    reg[x] = reg[x] | reg[y];
}

// 8XY2: Set Vx = Vx AND Vy
inline void TCpu::OP_8XY2(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    reg[x] = reg[x] & reg[y];
}

// 8XY3: Set Vx = Vx XOR Vy
inline void TCpu::OP_8XY3(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    reg[x] = reg[x] ^ reg[y];
}

// 8XY4: Set Vx = Vx + Vy, set VF = carry
inline void TCpu::OP_8XY4(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    uint16_t sum = reg[x] + reg[y];
    if(sum > 0xFF)
        reg[0xF] = 1;
    else
        reg[0xF] = 0;
    reg[x] = sum & 0xFF;
}

// 8XY5: Set Vx = Vx - Vy, set VF = NOT borrow
inline void TCpu::OP_8XY5(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    if(reg[x] > reg[y])
        reg[0xF] = 1;
    else
        reg[0xF] = 0;
    reg[x] = reg[x] - reg[y];
}

// 8XY6: Set Vx = Vx SHR 1
inline void TCpu::OP_8XY6(){
    uint8_t x = (opcode >> 8) & 0x0F;
    if(reg[x] & 0x01)
        reg[0xF] = 1;
    else
        reg[0xF] = 0;
    reg[x] = reg[x] >> 1;
}

// 8XY7: Set Vx = Vy - Vx, set VF = NOT borrow
inline void TCpu::OP_8XY7(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    if(reg[y] > reg[x])
        reg[0xF] = 1;
    else
        reg[0xF] = 0;
    reg[x] = reg[y] - reg[x];
}

// 8XYE: Set Vx = Vx SHL 1
inline void TCpu::OP_8XYE(){
    uint8_t x = (opcode >> 8) & 0x0F;
    if(reg[x] & 0x80)
        reg[0xF] = 1;
    else
        reg[0xF] = 0;
    reg[x] = reg[x] << 1;
}

// 9XY0: Skip next instruction if Vx != Vy
inline void TCpu::OP_9XY0(){
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t x = (opcode >> 8) & 0x0F;
    if(reg[x] != reg[y])
        pc+=2;
}

// ANNN: Set I = NNN
inline void TCpu::OP_ANNN(){
    I = opcode & 0x0FFF;
}

// BNNN: Jump to location NNN + V0
inline void TCpu::OP_BNNN(){
    pc = (opcode & 0x0FFF) + reg[0];
}

// CXNN: Set Vx = random byte AND NN
inline void TCpu::OP_CXNN(){
    uint8_t kk = opcode & 0x00FF;
    uint8_t x = (opcode >> 8) & 0x0F;
    uint8_t rnd = rand() % 256;
    reg[x] = rnd & kk; 
}

// DXYN: Display n-byte sprite starting at location I at screen location (Vx,Vy), set VF = collision
inline void TCpu::OP_DXYN(){
    uint8_t n = opcode & 0xF;
    uint8_t y = (opcode >> 4) & 0xF;
    uint8_t x = (opcode >> 8) & 0xF;
    
    uint8_t screen_x = reg[x] % SCREEN_WIDTH;
    uint8_t screen_y = reg[y] % SCREEN_HEIGHT;

    reg[0xF] = 0;
    for(int i = 0; i < n; i++){
        uint8_t pixels = chip8->memory[I + i];  //read each row of 8 pixels from memory
        for(int j = 0; j < 8; j++){             //for each pixel, 
            if((pixels & (0x80 >> j)) != 0){    //if pixel is 1,
                if(chip8->screen[screen_y + i][screen_x + j] == 1) //if the same pixel in screen is 1
                    reg[0xF] = 1;                                  // set VF = 1 for collision
                chip8->screen[screen_y + i][screen_x + j] ^= 0x1;  //update screen pixel with ^0x1;
            }
        }
    }
}

// EX9E: Skip next instruction if key with value of vx is pressed
inline void TCpu::OP_EX9E(){
    uint8_t x = (opcode >> 8) & 0xF;
    if(chip8->keys[reg[x]] != 0)
        pc += 2;
}

// EXA1: Skip next instruction if key with value of vx is not pressed
inline void TCpu::OP_EXA1(){
    uint8_t x = (opcode >> 8) & 0xF;
    if(chip8->keys[reg[x]] == 0)
        pc += 2;
}

// FX07: Set Vx = delay timer value
inline void TCpu::OP_FX07(){
    uint8_t x = (opcode >> 8) & 0xF;
    reg[x] = chip8->delay_timer;
}

// FX0A: Wait for key press, store the value of key in Vx
inline void TCpu::OP_FX0A(){
    uint8_t x = (opcode >> 8) & 0xF;
    bool key_pressed = false;
    for(int i = 0; i < NUM_KEYS; i++){
        if(chip8->keys[i] != 0){
            reg[x] = i;
            key_pressed = true;
        }
    }
    if(!key_pressed)
        pc -= 2;
}

// FX15: Set delay timer = Vx
inline void TCpu::OP_FX15(){
    uint8_t x = (opcode >> 8) & 0xF;
    chip8->delay_timer = reg[x];
} 

// FX18: Set sound timer = Vx
inline void TCpu::OP_FX18(){
    uint8_t x = (opcode >> 8) & 0xF;
    chip8->sound_timer = reg[x];
} 

// FX1E: Set I = I + Vx
inline void TCpu::OP_FX1E(){
    uint8_t x = (opcode >> 8) & 0xF;
    I = I + reg[x];
}

// FX29: Set I = location of sprite for digit Vx
inline void TCpu::OP_FX29(){
    uint8_t x = (opcode >> 8) & 0xF;
    I = reg[x] * 0x5;
}

// FX33: Store BCD representation of Vx in memory locations I, I+1, I+2
inline void TCpu::OP_FX33(){
    uint8_t x = (opcode >> 8) & 0xF;
    chip8->memory[I] = reg[x] / 100;
    chip8->memory[I+1] = (reg[x] / 10) % 10;
    chip8->memory[I+2] = (reg[x] % 100) % 10;
}

//FX55: Store registers V0 through Vx in memory starting at location I
inline void TCpu::OP_FX55(){
    uint8_t x = (opcode >> 8) & 0xF;
    for(auto i = 0; i <= x; i++){
        chip8->memory[I + i] = reg[i];
    }
}

//FX65: Read data from memory starting at I into registers V0 through Vx
inline void TCpu::OP_FX65(){
    uint8_t x = (opcode >> 8) & 0xF;
    for(auto i = 0; i <= x; i++){
        reg[i] = chip8->memory[I + i];
    }
}
