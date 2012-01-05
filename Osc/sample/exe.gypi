{
  'type': 'executable',
  'dependencies': [
    '<(DEPTH)/base/base.gyp:base',
    '<(DEPTH)/skia/skia.gyp:skia',
    '<(DEPTH)/ui/ui.gyp:ui',
    '<(DEPTH)/ui/ui.gyp:gfx_resources',
    '<(DEPTH)/ui/ui.gyp:ui_resources',
    '<(DEPTH)/ui/ui.gyp:ui_resources_standard',
    '<(DEPTH)/views/views.gyp:views',
  ],
  'include_dirs': [
   '..',
  ],
  'sources': [
    '<(SHARED_INTERMEDIATE_DIR)/ui/gfx/gfx_resources.rc',
    '<(SHARED_INTERMEDIATE_DIR)/ui/ui_resources/ui_resources.rc',
    '<(SHARED_INTERMEDIATE_DIR)/ui/ui_resources_standard/ui_resources_standard.rc',
  ],
  'conditions': [
    ['OS=="win"', {
      'link_settings': {
        'libraries': [
          '-limm32.lib',
          '-loleacc.lib',
        ]
      },
      'include_dirs': [
        '<(DEPTH)/third_party/wtl/include',
      ],
      'msvs_settings': {
        'VCManifestTool': {
          'AdditionalManifestFiles': '$(ProjectDir)\\exe.manifest',
        },
      },
      'msvs_settings': {
        'VCLinkerTool': {
          #   2 == /SUBSYSTEM:CONSOLE
          'SubSystem': '1',
        },
      }, 
    }],
  ],
}