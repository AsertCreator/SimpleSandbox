#include "Utilities.hpp"
#include <stdarg.h>

EXPORT std::vector<std::string> Utilities::Split(std::string str, std::string delim) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> res = std::vector<std::string>();

    while ((pos = str.find(delim)) != std::string::npos) {
        token = str.substr(0, pos);
        res.push_back(token);
        str.erase(0, pos + delim.length());
    }

    res.push_back(str);

    return res;
}
EXPORT std::string Utilities::ReadFile(std::string filepath) {
	// ofstream and ifstream never work with me :P
	FILE* file = fopen(filepath.c_str(), "rb");

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (size == 0) return "";

	char* buf = (char*)malloc(size + 1);

	if (buf != 0) {
		fread(buf, 1, size, file);
		buf[size] = 0;

		return std::string(buf);
	}
	else {
		return nullptr;
	}
}
EXPORT std::string Utilities::FormatText(std::string fmt, ...) {
	char out[512];
	va_list list;
	va_start(list, fmt);
	out[vsprintf(out, fmt.c_str(), list)] = 0;
	va_end(list);
	return std::string(out);
}
EXPORT void Utilities::WriteFile(std::string filepath, std::string data) {
	// ofstream and ifstream never work with me :P
	FILE* file = fopen(filepath.c_str(), "r+");
	fwrite(data.c_str(), 1, data.length(), file);
	fclose(file);
}