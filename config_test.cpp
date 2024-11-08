//
// Created by Arindam on 08/11/2024.
//

#include "config.hpp"

int main_config_test(int argc, char *argv[])
{
    const std::string filename = "config.yml";

    // Load the configuration from the YAML file
    Config cfg = load_config(filename);
    std::cout << "Loaded Config:\n";
    std::cout << "AppName: " << cfg.app_name << "\n";
    std::cout << "Version: " << cfg.version << "\n";
    std::cout << "Host: " << cfg.host << "\n";
    std::cout << "Port: " << cfg.port << "\n";

    // Modify the configuration
    cfg.port = 9090;
    std::cout << "\nModified Config:\n";
    std::cout << "Port: " << cfg.port << "\n";

    // Save the modified configuration back to the YAML file
    save_config(filename, cfg);
    std::cout << "\nConfiguration saved back to file." << std::endl;

    return 0;
}
