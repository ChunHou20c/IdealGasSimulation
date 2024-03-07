#include "shader.h"
#include "simulator.h"
#include <string>
#include <unistd.h>
#include <iostream>

std::string GetExecutablePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        result[count] = '\0';
        return std::string(result);
    } else {
        // Handle error
        return std::string("");
    }
}

std::string GetExecutableDirectory() {
    std::string executablePath = GetExecutablePath();
    size_t lastSlashPos = executablePath.find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        return executablePath.substr(0, lastSlashPos);
    } else {
        // Handle error
        return std::string("");
    }
}

int main(int argc, char *argv[]){

  std::string executablePath = GetExecutableDirectory();
  std::cout << executablePath << std::endl;

  Simulator ideal_gas(600,600,"Ideal Gas Simulation", executablePath);
  ideal_gas.Run();

  return 0;
}
