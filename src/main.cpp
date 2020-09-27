#include <filesystem>
#include <iostream>
#include <vector>

#include "directoryViewer.h"

namespace fs = std::filesystem;

int main(int argc, const char * argv[]) {
	std::string command;

    for (int i = 1; i < argc; i++) {
		command += argv[i];
	}
    const fs::path workdir = fs::current_path();
    if(fs::is_directory(workdir)) {
        directoryViewer(workdir, command);
    }

    return 0;
}