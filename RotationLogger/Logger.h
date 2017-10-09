#ifndef ROTATIONLOGGER_LOGGER_H
#define ROTATIONLOGGER_LOGGER_H


#include <string>
#include <vector>

class Logger {

public:
    Logger(int vNumber, int vMaxSize, std::string vPath);

    void Write(std::string vText);

    void DateWrite(std::string vText);

private:
    int mMaxNumberOfFiles;
    int mMaxFileSize;
    int mCurrentFileNumber;
    std::string mPathToFolderWithFiles;
    std::vector<std::string> LogFilePath;

    bool CurrentFileNotExist();

    void CreateCurrentFile();

    std::string GenerateFileName();

    bool CanBePlacedInCurrentFile(const std::string &logData);

    void WriteDataToFile(const std::string &logData);

    void GoToNextFile();

    std::string generateCurrentDate();

    bool FileExists(const char *fileName);
};


#endif //ROTATIONLOGGER_LOGGER_H
