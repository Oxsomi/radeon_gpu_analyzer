#pragma once

// C++.
#include <string>

// Shared between the CLI and the GUI.
#include "common/rga_version_info.h"

class RgaSharedUtils
{
public:
    // Convert Windows date format.
    static bool ConvertDateString(std::string& date_string);

    // Compares two paths, based on ignored case and with standardized path separators.
    // Returns true if the paths match; false otherwise.
    static bool ComparePaths(const std::string& path1, const std::string& path2);

    // Construct a name for log file based on specified "base_file_name".
    // The file name will be postfixed with the current date & time.
    // Example:
    //   "base_file_name"   --> log.txt
    //   Constructed name --> log-20180215-104536.txt
    static std::string ConstructLogFileName(const std::string& base_file_name);

    // Delete log files matching the "base_file_name" pattern that are older than "days_num" days.
    static bool DeleteOldLogs(const std::string& dir, const std::string& base_file_name, unsigned int days_num);

    // Open new log file and delete old files (older than "old_files_days_num" days).
    // "base_file_name" is the name prefix that will be used to construct log file name.
    // The current date and time will be appended to the base name.
    // Example:
    //   baseFileName:   "rga-cli.log"
    //   Log file name:  "rga-cli-20180210-161055.log
    static bool InitLogFile(const std::string& dir, const std::string& base_file_name, unsigned int old_files_days_num);

    // Close the log file.
    static void  CloseLogFile();

    // Converts the given string to its lower-case version.
    static std::string ToLower(const std::string& str);

    // Convert sthe given string to its upper-case version.
    static std::string ToUpper(const std::string& str);

private:
    RgaSharedUtils() = delete;
    ~RgaSharedUtils() = delete;
};
