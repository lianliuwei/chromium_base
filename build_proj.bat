call setup_env.bat
set PYTHONPATH=%PYTHONPATH%;%CD%\tools\grit
tools\gyp\gyp.bat --depth .  -Ibuild/common.gypi build/all.gyp