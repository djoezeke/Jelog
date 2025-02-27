#include <gtest/gtest.h>
#include "logger.h"

class LoggerTest : public ::testing::Test {
protected:
    Logger logger;

    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

TEST_F(LoggerTest, LogInfo) {
    testing::internal::CaptureStdout();
    logger.logInfo("This is an info message.");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("INFO: This is an info message.") != std::string::npos);
}

TEST_F(LoggerTest, LogWarning) {
    testing::internal::CaptureStdout();
    logger.logWarning("This is a warning message.");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("WARNING: This is a warning message.") != std::string::npos);
}

TEST_F(LoggerTest, LogError) {
    testing::internal::CaptureStdout();
    logger.logError("This is an error message.");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("ERROR: This is an error message.") != std::string::npos);
}