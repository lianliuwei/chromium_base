#include <iostream>

#include "base/logging.h"
#include "base/command_line.h"

//still leak some memory because the global obj VlogInfo in logging. not method
//to release
int main(int argc, char** argv)
{
    using namespace logging;

    CommandLine::Init(argc, argv);

    InitLogging(L"debug2.log", 
        LOG_TO_BOTH_FILE_AND_SYSTEM_DEBUG_LOG, 
        DONT_LOCK_LOG_FILE,
        DELETE_OLD_LOG_FILE,
        DISABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS);

    int num_cookies = 10;
    LOG(INFO) << "Found " << num_cookies << " cookies";
    LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
    LOG_IF(INFO, num_cookies == 10) << "Got ten cookies";
    LOG_IF(INFO, num_cookies < 10) << "Got less of cookies";
    CHECK(1 == 1);
    //CHECK(2 < 1);
    VLOG(1) << "I'm printed when you run the program with --v=1 or more";
    VLOG(2) << "I'm printed when you run the program with --v=2 or more";
    fopen("a", "r");//error open
    PLOG(WARNING) << "Couldn't do foo";
    LOG(INFO) << "info log";
    LOG(WARNING) << "warning log";
    LOG(ERROR) << "error log";
    LOG(ERROR_REPORT) << "error_report log";
    //LOG(FATAL) << "FATAL log";
    
    //close to release global obj
    CloseLogFile();
    CommandLine::Reset();
    
    return 0;
}