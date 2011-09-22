{
  'targets': [
    {
      'target_name': 'ui',
      'type': 'static_library',
      'sources': [
		    'base/ui_export.h',
		    'base/resource/data_pack.cc',
		    'base/resource/data_pack.h',
		    'gfx/native_widget_types.h',
		    'base/ui_base_paths.h',
		    'base/ui_base_paths.cc',
		    'base/ui_base_switches.h',
		    'base/ui_base_switches.cc',
		    'gfx/image/image.h',
		    'gfx/image/image.cc',
		    'gfx/font.h',
		    'gfx/font.cc',
		    'gfx/platform_font.h',
		    'gfx/platform_font_win.h',
		    'gfx/platform_font_win.cc',
		    'gfx/canvas.h',
		    'gfx/canvas.cc',
		    'gfx/brush.h',
		    'gfx/rect.h',
		    'gfx/rect.cc',
		    'gfx/transform.h',
		    'gfx/transform.cc',
		    'gfx/point.h',
		    'gfx/point.cc',
		    'gfx/point3.h',
		    'gfx/skia_util.h',
		    'gfx/skia_util.cc',
		    'gfx/canvas_skia_paint.h',
		    'gfx/color_utils.h',
		    'gfx/color_utils.cc',
		    'gfx/canvas_skia.h',
		    'gfx/canvas_skia.cc',
		    'gfx/canvas_skia_win.cc',
		    'base/l10n/l10n_util.h',
		    'base/l10n/l10n_util.cc',
		    'gfx/size.h',
		    'gfx/size.cc',
        'gfx/insets.h',
        'gfx/insets.cc',
        'base/l10n/l10n_util_win.h',
        'base/l10n/l10n_util_win.cc',
        'base/resource/resource_bundle.h',
        'base/resource/resource_bundle.cc',
        'base/resource/resource_bundle_win.cc',
      ],

      'include_dirs': [
          '..',
      ],
      
      'defines': [
        'UI_IMPLEMENTATION',
      ],
      
      'dependencies': [
        '../base/base.gyp:base',
		'../skia/skia.gyp:skia',
		'../third_party/zlib/zlib.gyp:zlib',
		'../third_party/libpng/libpng.gyp:libpng',
      ],

      'direct_dependent_settings': {
        'include_dirs': [
          '..',
        ],
      },

    },
  ],
}