#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

namespace bf = boost::filesystem;

namespace fs {

void write(const std::string &data, const std::string &file_name) {
    bf::ofstream file(file_name);
    file << data;
    file.close();
}


std::string read(const std::string &file_name) {
    if (!bf::exists(file_name))
        return "";
    bf::ifstream file(file_name);
    std::string res;
    std::string line;
    while (std::getline(file, line, '\n')) {
        res += line + '\n';
    }
    file.close();
    return res;
}

}