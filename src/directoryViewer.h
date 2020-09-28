#pragma once
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class directoryViewer {
public:
    directoryViewer(fs::path workingDirectory, std::string keys);
    ~directoryViewer() {}
    std::vector<fs::path> getDirectoryPaths(fs::path workDir);
    void getFilesData(std::vector<fs::path> paths);
private:
    void displayDirectory(std::string out);
    void displayDirectory(std::vector<std::string> out);
    void parseCommand(std::string command);
    std::string getFilePermissions(fs::perms p);
    std::string getFileOwner(const fs::path &filePath);
    std::string getFileLastWriteTime(const fs::path &filePath);
    std::string getFileSize(const fs::path &filePath);
    std::string getHardLinksCount(const fs::path &filePath);
    bool isFileHidden(const fs::path &filePath);
    bool lKey = false;
    bool aKey = false;
    int total = 0;
};
