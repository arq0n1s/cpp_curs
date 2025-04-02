#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <variant>
#include <sstream>

using ConfigMap = std::map<std::string, std::variant<int, double, std::string>>;

ConfigMap readConfig(const std::filesystem::path& filePath) {
    ConfigMap config;
    if (!std::filesystem::exists(filePath)) {
        throw std::runtime_error("Config file not found: " + filePath.string());
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + filePath.string());
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            value.erase(0, value.find_first_not_of(" "));
            value.erase(value.find_last_not_of(" ") + 1);

            if (value.find_first_not_of("0123456789") == std::string::npos) {
                config[key] = std::stoi(value);
            } else if (value.find_first_not_of("0123456789.") == std::string::npos && value.find('.') != std::string::npos) {
                config[key] = std::stod(value);
            } else {
                config[key] = value;
            }
        }
    }

    return config;
}

int main() {
    try {
        auto config = readConfig("C:/Users/bachm/Zomboid/options.ini");
        for (const auto& [key, value] : config) {
            std::cout << key << " = ";
            std::visit([](const auto& v) { std::cout << v; }, value);
            std::cout << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
