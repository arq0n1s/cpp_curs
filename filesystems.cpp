#include <filesystem>
#include <iostream>
#include <tuple>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <variant>
#include <format>

namespace fs = std::filesystem;

using value_t = std::variant<int, double, std::string>;
std::map <std::string, value_t> cfg_map;

void read_config(std::string config_file_path)
{
    fs::path cfg_path = fs::path(config_file_path);
    if(fs::exists(cfg_path)&&fs::is_regular_file(cfg_path))
    {
        std::cout << "cfg file has: "
                    << fs::file_size(cfg_path) << " bytes." << std::endl;
    }
    else
    {
            std::cerr << "the file: " << cfg_path.filename()
                        << " doesn't exists in folder: "
                        << cfg_path.parent_path() << std::endl;
    }
}

void read_config_to_tuple(const fs::path& config_file_path)
{   

    std::ifstream file(config_file_path);
    
    if(!file.is_open())
    {
        std::cerr << "failed to open. the file: " << config_file_path.filename()
                        << " is opened right now. "
                        << config_file_path.parent_path() << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) 
        {
            value.erase(0, value.find_first_not_of(" "));
            value.erase(value.find_last_not_of(" ") + 1);

            if (value.find_first_not_of("0123456789") == std::string::npos) {
                std::cout << "Int: " << key << " -> " << value << std::endl;
                cfg_map[key] = std::stoi(value);
            } else if (value.find_first_not_of("0123456789.") == std::string::npos && value.find('.') != std::string::npos) {
                cfg_map[key] = std::stod(value);
            } else {
                cfg_map[key] = value;
            }
        }
    }

}

void print_username(std::string_view user_name)
{
    std::cout << "Username: " << user_name << std::endl;
}


std::string visitor(std::string &&arg)
{
    return arg;
}

std::string visitor(int &&arg)
{
    return std::to_string(arg);
}

std::string visitor(double &&arg)
{
    return std::to_string(arg);
}

int main()
{
    std::cout << "start programm" << std::endl;


    const char *my_test_cfg_path = "C:/Users/bachm/Zomboid/options.ini";

    const char *greetings = "Hello TestUser, how are you?";
    std::string_view user_name((greetings+6), 8);
    print_username(user_name);

    read_config(my_test_cfg_path);

    read_config_to_tuple("C:/Users/bachm/Zomboid/options.ini");
    
    // auto visitor = [](const auto &&val) -> std::string {
    //     return std::format("{}, val");
    // };

    for (const auto& [key, value] : cfg_map) {
        std::string val = std::visit(visitor, value);
        std::cout << key << " = " << val << std::endl;
    }

    // auto print_map = [](cfg_map[key],cfg_map[value]) -> string {return key+" = "+value};
    // for(const auto& n : cfg_map){
    //     std::cout << print_map(n) << std::endl;
    // }

    std::cout << "finish programm" << std::endl;


    return 0;
}

