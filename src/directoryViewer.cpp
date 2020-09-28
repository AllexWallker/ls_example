#include "directoryViewer.h"

#include <iostream>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>


directoryViewer::directoryViewer(fs::path workingDirectory, std::string keys) {
    parseCommand(keys);
    auto paths = getDirectoryPaths(workingDirectory);
    getFilesData(paths);
}

void directoryViewer::parseCommand(std::string command) {
    if(command.find("-l") != std::string::npos) {
        lKey = true;
    }
    if(command.find("-a") != std::string::npos) {
        aKey = true;
    }
}

std::vector<fs::path> directoryViewer::getDirectoryPaths(fs::path workDir) {
    std::vector<fs::path> dirs; 
    std::vector<fs::path> files;
    for (const auto & entry : fs::directory_iterator(workDir)) {
        if(!aKey && isFileHidden(entry.path())) {
            continue;
        }
        
        if(entry.is_directory()) {
            dirs.push_back(entry.path());
        }
        else if(entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    dirs.insert(dirs.end(), files.begin(), files.end());
    return dirs;
}

void directoryViewer::getFilesData(std::vector<fs::path> paths) {
    if(true) {
        std::vector<std::string> outputs;
        for (const auto filePath : paths) {
            std::string output = "";
            output += getFilePermissions(fs::status(filePath).permissions());
            output += getHardLinksCount(filePath);
            output += getFileOwner(filePath);
            output += getFileSize(filePath);
            output += getFileLastWriteTime(filePath);            
            output += filePath.filename().native().c_str();
            outputs.push_back(output);
        }
        displayDirectory(outputs);
    }
    else {
        std::string output = "";        
        for (const auto filePath : paths) {
            output += filePath.filename().native().c_str();
            output += "    ";
        }
        displayDirectory(output); 
    }
}

void directoryViewer::displayDirectory(std::string out) {
    std::cout << out << std::endl;
}

void directoryViewer::displayDirectory(std::vector<std::string> out) {
    for(auto pathInfo : out) {
        std::cout << pathInfo << std::endl;
    } 
}

std::string directoryViewer::getFilePermissions(fs::perms p) {
    std::string out = "";
    ((p & fs::perms::owner_read) != fs::perms::none ? out += "r" : out += "-");
    ((p & fs::perms::owner_write) != fs::perms::none ? out += "w" : out += "-");
    ((p & fs::perms::owner_exec) != fs::perms::none ? out += "x" : out += "-");
    ((p & fs::perms::group_read) != fs::perms::none ? out += "r" : out += "-");
    ((p & fs::perms::group_write) != fs::perms::none ? out += "w" : out += "-");
    ((p & fs::perms::group_exec) != fs::perms::none ? out += "x" : out += "-");
    ((p & fs::perms::others_read) != fs::perms::none ? out += "r" : out += "-");
    ((p & fs::perms::others_write) != fs::perms::none ? out += "w" : out += "-");
    ((p & fs::perms::others_exec) != fs::perms::none ? out += "x" : out += "-");
    out += "   ";
    return out;
}

std::string directoryViewer::getFileOwner(const fs::path &filePath) {
    std::string out = "";
    struct stat info;
    stat(filePath.c_str(), &info);
    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);
    if(pw) {
        out += pw->pw_name;
        out += "  ";
    }
    if(gr) {
        out += gr->gr_name;
        out += "  ";
    }
    return out;
}

std::string directoryViewer::getFileLastWriteTime(const fs::path &filePath) {
    std::string out = "";
    auto last_time = fs::last_write_time(filePath);
    const std::time_t cftime = decltype(last_time)::clock::to_time_t(last_time);
    out = std::asctime(std::localtime(&cftime));
    auto point = out.find("\n");
    out.erase(point);
    out += " ";
    return out;
}

std::string directoryViewer::getFileSize(const fs::path &filePath) {
    std::string out = "";
    if(fs::is_directory(filePath)) {
        for(const auto & entry : fs::recursive_directory_iterator(filePath)) {   
            if(!fs::is_directory(entry.path())) {
                out = std::to_string(fs::file_size(entry.path()));
                out += "    ";
            }
        }   
    }
    else {
        out = std::to_string(fs::file_size(filePath));
        out += "    ";
    }
    return out;
}

std::string directoryViewer::getHardLinksCount(const fs::path &filePath) {
    std::string out = "";
    auto ll = fs::hard_link_count(filePath);
    out = std::to_string(ll) + " ";
    return out;
}

bool directoryViewer::isFileHidden(const fs::path &filePath) {
    fs::path::string_type name = filePath.filename();
    return (name != ".." && name != "."  && name[0] == '.'); 
}



std::string dist = "     192 ";