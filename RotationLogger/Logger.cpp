#include <fstream>
#include <sstream>
#include "Logger.h"

Logger::Logger(int vNumber, int vMaxSize, std::string vPath) {
    this->mMaxNumberOfFiles = vNumber;
    this->mMaxFileSize = vMaxSize;
    this->mPathToFolderWithFiles = vPath;
    this->mCurrentFileNumber = 0;
    this->LogFilePath = std::vector<std::string>(mMaxNumberOfFiles);
}

void Logger::Write(std::string vText) {
    if (CurrentFileNotExist()) {
        CreateCurrentFile();
    }
    std::string logDataDelimiter = "\n";
    std::string logData = vText + logDataDelimiter;

    if (CanBePlacedInCurrentFile(logData)) {
        WriteDataToFile(logData);
    } else {
        GoToNextFile();
        this->Write(vText);
    }
}

void Logger::DateWrite(std::string vText) {
    this->Write(vText + " " + generateCurrentDate());
}

bool Logger::CurrentFileNotExist() {
    bool fileNotExist = LogFilePath[mCurrentFileNumber].empty();
    bool fileDeleted = !FileExists(LogFilePath[mCurrentFileNumber].c_str());

    return fileNotExist || fileDeleted;
}

void Logger::CreateCurrentFile() {
    std::ofstream logFile;
    std::string logFilePath = mPathToFolderWithFiles + GenerateFileName();
    logFile.open(logFilePath);
    LogFilePath[mCurrentFileNumber] = logFilePath;
    logFile.close();
}

std::string Logger::GenerateFileName() {

    static long long int file_id;
    file_id++;

    long long int now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();

    std::string fileName;
    std::stringstream stringStream;
    stringStream << now << "_" << file_id;
    stringStream >> fileName;

    return fileName;
}

bool Logger::CanBePlacedInCurrentFile(const std::string &logData) {
    std::ifstream file(LogFilePath[mCurrentFileNumber], std::ios::binary | std::ios::ate);
    long long int currentFileSize = file.tellg();
    bool fileDeleted = currentFileSize == -1;
    if (fileDeleted) {
        return false;
    }
    file.close();
    return currentFileSize + logData.size() <= mMaxFileSize;
}

void Logger::WriteDataToFile(const std::string &logData) {
    std::fstream logFile;
    logFile.open(LogFilePath[mCurrentFileNumber], std::ios::app);
    logFile << logData;
    logFile.close();
}

void Logger::GoToNextFile() {
    mCurrentFileNumber++;
    if (mCurrentFileNumber >= mMaxNumberOfFiles) {
        mCurrentFileNumber = 0;
    }
    if (!LogFilePath[mCurrentFileNumber].empty()) {
        std::remove(LogFilePath[mCurrentFileNumber].c_str());
        LogFilePath[mCurrentFileNumber] = "";
    }
}

std::string Logger::generateCurrentDate() {
    time_t rawTime;
    struct tm *timeInfo;
    const int bufferSize = 80;
    char buffer[bufferSize];

    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeInfo);

    std::string currentDate(buffer);

    return currentDate;
}

bool Logger::FileExists(const char *fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
