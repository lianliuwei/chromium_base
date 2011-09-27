#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"
#include "ui/gfx/image/image.h"
#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/sys_string_conversions.h"

#include "resource.h"

int main(int argc, char** argv)
{
    using namespace logging;

    CommandLine::Init(argc, argv);
    InitLogging(L"debug.log", 
        LOG_TO_BOTH_FILE_AND_SYSTEM_DEBUG_LOG, 
        DONT_LOCK_LOG_FILE,
        DELETE_OLD_LOG_FILE,
        DISABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS);
    base::AtExitManager exit_manager;
    ui::RegisterPathProvider();
    ui::ResourceBundle::InitSharedInstance("en-US");
    
    ui::ResourceBundle& bundle = ui::ResourceBundle::GetSharedInstance();
    LOG(INFO) << bundle.GetLocalizedString(IDS_HELLO_WORLD);
    // CAN not call this to get the image in locale file. because ResourceBundle only check
    // the main instance. so compile the image file in to exe or dll.
    // gfx::Image& image =  bundle.GetImageNamed(IDR_HELLO_WORLD);

    ui::ResourceBundle::CleanupSharedInstance();
    ui::ResourceBundle::InitSharedInstance("zh-CN");
    ui::ResourceBundle& bundle2 = ui::ResourceBundle::GetSharedInstance();
    LOG(INFO) << base::SysWideToNativeMB(bundle2.GetLocalizedString(IDS_HELLO_WORLD));

    
    return 0;
}