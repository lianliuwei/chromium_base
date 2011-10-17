{
  'targets' : [

    {
      'target_name': 'resource_en',
      'type': 'loadable_module',
      'sources': [
	      'resource/resource_en.rc',
      ],
	    'msvs_settings': {
		    'VCLinkerTool': {
		      'BaseAddress': '0x3CF00000',
          'OutputFile': '$(OutDir)\\locales\\$(ProjectName).dll',
          'LinkIncremental': '1',  # 1 == No
          'LinkTimeCodeGeneration': '0',
          'ResourceOnlyDLL': 'true',
        },
      },
      'defines': [
        '_USRDLL',
        'GENERATED_RESOURCES_DLL_EXPORTS',
      ],
    },

	  {
      'target_name': 'resource_zh-CN',
      'type': 'loadable_module',
      'sources': [
	      'resource/resource_zh-CN.rc',
      ],
	    'msvs_settings': {
		    'VCLinkerTool': {
		      'BaseAddress': '0x3CF00000',
          'OutputFile': '$(OutDir)\\locales\\$(ProjectName).dll',
          'LinkIncremental': '1',  # 1 == No
          'LinkTimeCodeGeneration': '0',
          'ResourceOnlyDLL': 'true',
        },
      },
      'defines': [
        '_USRDLL',
        'GENERATED_RESOURCES_DLL_EXPORTS',
      ],
    },

	  {
      'target_name': 'data_pack',
      'type': 'executable',
      'sources': [
        'data_pack/main.cc',
		    'data_pack/resource.h',
		    'data_pack/data.pak',
      ],
      'dependencies': [
        '../ui/ui.gyp:ui',
      ],
    },

    {
      'target_name': 'resource_bundle',
      'type': 'executable',
      'sources': [
        'resource_bundle/main.cc',
		    'resource_bundle/resource.h',
		    'resource_bundle/resources.pak',
        'resource_bundle/Locales/en-US.pak',
        'resource_bundle/Locales/zh-CN.pak',
      ],
      'dependencies': [
        '../ui/ui.gyp:ui',
        '../third_party/libpng/libpng.gyp:libpng',
      ],
    },
    # to work around the VS 2008 in XP no build app_locale_settings bug
    {
      'target_name': 'app_locale_settings',
      'type': 'none',
      'variables': {
        'grit_base_out_dir': '<(SHARED_INTERMEDIATE_DIR)/ui',
      },
      'actions': [
        {
          'action_name': 'app_locale_settings',
          'variables': {
            'grit_grd_file': '<(DEPTH)/ui/base/strings/app_locale_settings.grd',
            'grit_out_dir': '<(grit_base_out_dir)/app_locale_settings',
          },
          'includes': [ '../build/grit_action.gypi' ],
        },
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          '<(grit_base_out_dir)/app_locale_settings',
        ],
      },
    },
  ],
}
