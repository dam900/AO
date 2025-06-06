#pragma once
#include <fstream>
#include <string>
#include <vector>

template <typename T>
class ResultsSaver {
public:
    std::string path;


    /**
     * @brief Adds a result to the results container and dont save it to the file immediately.
     * 
     * @param result The result object to be added.
     */
    void put(const std::pair<int, T>& result) {
        results.push_back(result);
    };

    /**
     * @brief Saves all results to the specified file.
     * 
     */
    void save() {
        std::ofstream file(path, std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + path);
        }

        for (const auto& result : results) {
            file << result.first << ","; 
            file << result.second << "\n"; 
        }

        file.close();
        results.clear();
    };

public:
    std::vector<std::pair<int, T>> results;

};

