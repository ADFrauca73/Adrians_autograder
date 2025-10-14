#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<filesystem>

std::vector<std::string> getSubmissionPaths() {
    std::vector<std::string> paths;
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("./submissions/")) {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
            paths.push_back(entry.path().string());
        }
    }
    return paths;
}

std::vector<std::string> getTestPaths() {
    std::vector<std::string> paths;
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("./tests/")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            paths.push_back(entry.path().string());
        }
    }
    return paths;
}

std::string getFileNameFromPath(const std::string& path) {
    size_t lastSlash = path.find_last_of("/\\");
    size_t lastDot = path.find_last_of('.');
    if (lastSlash == std::string::npos) lastSlash = -1; // No slash found
    if (lastDot == std::string::npos || lastDot < lastSlash) lastDot = path.length(); // No dot found or dot before slash
    return path.substr(lastSlash + 1, lastDot - lastSlash - 1);
}

int compile(const std::string& submissionPath, const std::string& exePath, const std::string& errorPath) {
    std::cout << "Called compile with submissionPath: " << submissionPath 
              << ", exePath: " << exePath 
              << ", errorPath: " << errorPath << std::endl;

    namespace fs = std::filesystem;

    // Make sure the parent directories for both outputs and exe exist
    fs::create_directories("./outputs/" + getFileNameFromPath(submissionPath));
    fs::create_directories(fs::path(exePath).parent_path());

    // Compile the file
    std::string compileCommand = "g++ " + submissionPath + " -o " + exePath + " 2> " + errorPath;
    int compileStatus = system(compileCommand.c_str());

    if (compileStatus != 0) {
        std::cout << "Compilation failed for " << submissionPath 
                  << ". Check " << errorPath << " for details." << std::endl;
        return -1;
    }

    std::cout << "Compilation succeeded for " << submissionPath << "." << std::endl;
    return 0;
}


void testExe(const std::string& exePath, std::vector<std::string>& testPaths) {
    std::string fileName = getFileNameFromPath(exePath);
    for (const auto& testPath : testPaths) {
        std::string testName = getFileNameFromPath(testPath);
        // make a directory within outputs with the file name if it doesn't exist
        namespace fs = std::filesystem;
        fs::create_directories("./outputs/" + fileName);
        std::string command = exePath + " < " + testPath + " > ./outputs/" + fileName + "/" + testName + "_output.txt 2> ./outputs/" + fileName + "/" + testName + "_error.txt";
        int runStatus = system(command.c_str());
        if (runStatus != 0) {
            std::cout << "Runtime error for " << fileName << " on test " << testName << ". Check " << testName << "_error.txt for details." << std::endl;
        }
        else {
            std::cout << "Test " << testName << " passed for " << fileName << "." << std::endl;
        }
    }
}

void testSubmissions(const std::vector<std::string>& submissionPaths, const std::vector<std::string>& testPaths) {
    for (const auto& submissionPath : submissionPaths) {
        std::string fileName = getFileNameFromPath(submissionPath);
        std::string exePath = "./executables/" + fileName;
        std::string errorPath = "./outputs/" + fileName + "/compile_error.txt";
        if (compile(submissionPath, exePath, errorPath) == 0) {
            testExe(exePath, const_cast<std::vector<std::string>&>(testPaths));
        }
    }
}

int main() {
    std::cout << "Starting autograder..." << std::endl;

    // ensure the outputs and executables directories exist, and create them if they don't
    namespace fs = std::filesystem;
    fs::create_directories("./outputs/");
    fs::create_directories("./executables/");

    std::vector<std::string> submissionPaths = getSubmissionPaths();
    std::cout << "Found " << submissionPaths.size() << " submissions." << std::endl;
    for (const auto& path : submissionPaths) {
        std::cout << " - " << path << std::endl;
    }
    std::vector<std::string> testPaths = getTestPaths();
    std::cout << "Found " << testPaths.size() << " test cases." << std::endl;
    for (const auto& path : testPaths) {
        std::cout << " - " << path << std::endl;
    }
    testSubmissions(submissionPaths, testPaths);
    std::cout << "Autograding complete. Check the output directory for results." << std::endl;
    return 0;
}