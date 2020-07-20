#include <string>

constexpr char DEF_FILE[] = "output_file.log";

namespace fs {

void write(const std::string &data, const std::string &file_name = DEF_FILE);
std::string read(const std::string &file_name = DEF_FILE);

}