#ifndef __LOADER_H__
#define __LOADER_H__

#include <cstdint>
#include <filesystem>

#include "logger.h"
#include "chip8.h"

class TLoader{
    
    std::shared_ptr<TLogger> logger;
    std::string rom_root;
    TChip8* chip8;

public: 
    TLoader(TChip8* machine);
    ~TLoader();
    void init(std::string root_path);
    void deinit();
    void update();
};



#endif