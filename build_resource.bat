PATH=%PATH%;D:\Program Files\Python27
tools\grit\grit.py -v  -i ui/base/strings/app_locale_settings.grd build -o ./ -f tools/gritsettings/resource_ids
tools\grit\grit.py -v  -i ui/base/strings/ui_strings.grd build -o ./ -f tools/gritsettings/resource_ids
tools\grit\grit.py -v  -i ui/gfx/gfx_resources.grd build -o ./ -f tools/gritsettings/resource_ids
tools\grit\grit.py -v  -i ui/resources/ui_resources.grd build -o ./ -f tools/gritsettings/resource_ids -D toolkit_views=1
tools\grit\grit.py -v  -i ui/resources/ui_resources_standard.grd build -o ./ -f tools/gritsettings/resource_ids
tools\grit\grit\format\repack.py grit/resources.pak grit/app_locale_settings_en-US.pak