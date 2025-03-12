#include <filesystem>
#include <iostream>
#include <tuple>

// #define my_test_cfg_path "C:/Users/bachm/OneDrive/Документы/Overwatch/Settings/Settings_v0.ini" 


namespace fs = std::filesystem;

int n = 0;

std::tuple<std::string, uint8_t> my_cfg_tuple(int id);

void read_config(std::string_view config_file_path)
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
                        << "doesn't exists in folder: "
                        << cfg_path.parent_path() << std::endl;
    }
}

void read_config_to_tuple(const char* config_file_path)
{
    int is_ok = EXIT_FAILURE;
    FILE *f = fopen(config_file_path, "r+");
    
    std::string work_str;

    while(std::getline(f,work_str))
    {
        // id = n;
        n++;
    }


}

void print_username(std::string_view user_name)
{
    std::cout << "Username: " << user_name << std::endl;
}


int main()
{
    std::cout << "start programm" << std::endl;


    const char *my_test_cfg_path = "C:/Users/bachm/OneDrive/Документы/Overwatch/Settings/Settings_v0.ini";
    const char *my_copy_test_cfg_path = "D:/projects/c++/test_cfg.txt";


    const char *greetings = "Hello TestUser, how are you?";
    std::string_view user_name((greetings+6), 8);
    print_username(user_name);

    std::string_view cfg((my_test_cfg_path+6), 8);
    read_config(cfg);

    read_config_to_tuple(my_test_cfg_path);

    std::cout << "finish programm" << std::endl;


    return 0;
}

