#include <cstdlib>

#include "loader.h"

TLoader::TLoader(){
    logger = TLogger::getInstance();
    logger->log("Loader Constructed", ELogLevel::DEBUG);
}

TLoader::~TLoader(){
    logger->log("Loader Destructed", ELogLevel::DEBUG);
}

void TLoader::init(std::string root){
    root_path = root;
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
            menu_list.push_back(one);
        }
    }

    numFiles = menu_list.size();
    keyboard->init();
    logger->log("Loader Initialized", ELogLevel::DEBUG);
}

void TLoader::deinit(){
    logger->log("Loader Deinitialized", ELogLevel::DEBUG);
}

void TLoader::update(){
    if(keys[0x2]){
        activeIdx -= 1;
    }
    else if(keys[0x8]){
        activeIdx += 1;
    }
    else if(keys[0x5]){
        menu_running = false;
    }
    if(activeIdx < 0){
        activeIdx = 0;
    }
    if(activeIdx > numFiles-1){
        activeIdx = numFiles-1;
    }
}

void TLoader::run(){
    using clock = std::chrono::high_resolution_clock;
    clock::time_point start, end;
    const std::chrono::microseconds desired_cycle_time(1000);
    int display_update_delay_time = 0;
    
    menu_running = true;
    while(menu_running){
        start = clock::now();

        // Update menu display
        if(display_update_delay_time >= 50){
            update();
            display->update_menu(activeIdx);
            display_update_delay_time = 0;
        }

        keyboard->update(keys, &menu_running);
        end = clock::now();
        std::chrono::duration<double, std::micro> loop_time = end - start;
        auto sleep_time = desired_cycle_time - loop_time;
        auto later = end + sleep_time;
        std::this_thread::sleep_until(later);
        display_update_delay_time++;
    }
    
    // Load ROM in memory
    int indx = activeIdx % numFiles;
    rom_path = root_path + menu_list[indx];
}

void TLoader::setDisplay(TDisplayInterface* displayInterface){
    display = displayInterface;
}

void TLoader::setKeyboard(TKeyboard* keyboardInterface){
    keyboard = keyboardInterface;
}

std::vector<std::string>& TLoader::getMenuList(){
    return menu_list;
}

std::string TLoader::getRomPath(){
    return rom_path;
}