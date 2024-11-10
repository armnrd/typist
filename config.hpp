/**
 * @file config.hpp
 * @brief Functions for loading and saving configuration data.
 *
 * @author Arindam Biswas
 * @date 08/11/2024
 */

#ifndef TYPIST_CONFIG_HPP
#define TYPIST_CONFIG_HPP

#include <string>

// Structure to hold the configuration data
struct Config {
    std::string app_name;
    int version;
    std::string host;
    int port;
};

Config load_config(const std::string& filename);

void save_config(const std::string& filename, const Config& cfg);

#endif //TYPIST_CONFIG_HPP
