#include "puzzle_io.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace hashi {

std::vector<std::vector<int>> read_puzzle_file(const std::string& path) {
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("File not found: " + path);
    }

    std::vector<std::vector<int>> values;
    std::string line;
    while (std::getline(input, line)) {
        const std::size_t comment = line.find('#');
        if (comment != std::string::npos) line.erase(comment);

        std::istringstream row_stream(line);
        std::vector<int> row;
        int value = 0;
        while (row_stream >> value) row.push_back(value);
        if (!row.empty()) values.push_back(std::move(row));
    }

    if (values.empty()) {
        throw std::runtime_error("The puzzle file does not contain any numeric lines.");
    }
    return values;
}

} // namespace hashi
