#include <filesystem>
#include <iostream>
#include <vector>

#include "directoryViewer.h"

int main(int argc, const char * argv[]) {
	std::string keys = "";
    std::string path = "";

    for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
        if(arg.find_first_of("-") != std::string::npos) {
            keys += arg;
        }
        else {
            path = arg;
            break;
        }
	}
    fs::path workdir;
    if(!path.empty()) {
        auto argPath = new fs::path(path.c_str());
        workdir = *argPath;
    }
    else {
        workdir = fs::current_path();
    }
    if(fs::is_directory(workdir)) {
        auto dirViewer = new directoryViewer(keys);
        auto paths = dirViewer->getDirectoryPaths(workdir);
        auto filesData = dirViewer->getFilesData(paths);
        dirViewer->displayDirectory(filesData);

        delete dirViewer;
    }
    else {
        std::cout << "no such directory\n";
    }

    return 0;
}