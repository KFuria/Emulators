#include <cstdlib>

#include "loader.h"

TLoader::TLoader(TChip8* machine){
    logger = TLogger::getInstance();
    chip8 = machine;
    logger->log("Loader Constructed", ELogLevel::DEBUG);
}

TLoader::~TLoader(){
    logger->log("Loader Destructed", ELogLevel::DEBUG);
}

void TLoader::init(std::string root_path){
    namespace fs = std::filesystem;
    std::vector<fs::path> paths;
    for (const auto& entry : fs::recursive_directory_iterator(root_path)){
        if(!fs::is_directory(entry)){
            auto relative_path = fs::relative(entry, root_path);
            paths.push_back(relative_path);
        }   
    }
    int n = paths.size();
    for(auto i = 0; i < n; i++){
        if(paths[i].extension() == ".ch8"){
            std::string one = paths[i].string();
            std::replace(one.begin(), one.end(), '\\', '/');
            chip8->file_map.push_back(one);
        }
    }

    chip8->numFiles = chip8->file_map.size();
    logger->log("Loader Initialized", ELogLevel::DEBUG);
}

void TLoader::deinit(){

}

void TLoader::update(){

    if(chip8->keys[0x2]){
        chip8->activeIdx -= 1;
        chip8->sound_timer = 1;
    }
    else if(chip8->keys[0x8]){
        chip8->activeIdx += 1;
        chip8->sound_timer = 1;
    }
    else if(chip8->keys[0x5]){
        chip8->menu_running = false;
    }
    if(chip8->activeIdx < 0){
        chip8->activeIdx = 0;
    }
    if(chip8->activeIdx > chip8->numFiles-1){
        chip8->activeIdx = chip8->numFiles-1;
    }
}