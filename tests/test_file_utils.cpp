#include "file_utils.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>

TEST(FileUtilsTest, WriteLogToFile) {
    const std::string filename = "test_log.txt";
    const std::string logMessage = "Test log message";

    // Open the log file
    openLogFile(filename);

    // Write a log message
    writeLog(logMessage);

    // Close the log file
    closeLogFile();

    // Verify that the log message was written to the file
    std::ifstream logFile(filename);
    std::string line;
    bool messageFound = false;

    while (std::getline(logFile, line)) {
        if (line == logMessage) {
            messageFound = true;
            break;
        }
    }

    logFile.close();
    EXPECT_TRUE(messageFound);

    // Clean up the test log file
    std::remove(filename.c_str());
}

TEST(FileUtilsTest, OpenLogFileInvalid) {
    // Attempt to open an invalid log file
    EXPECT_FALSE(openLogFile("invalid_path/test_log.txt"));
}