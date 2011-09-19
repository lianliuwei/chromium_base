{
  'targets': [
    {
      'target_name': 'ui',
      'type': 'static_library',
      'sources': [
		'base/ui_export.h',
		'base/resource/data_pack.cc',
		'base/resource/data_pack.h',
      ],

      'include_dirs': [
          '..',
      ],
      
      'defines': [
        'UI_IMPLEMENTATION',
      ],
      
      'dependencies': [
        '../base/base.gyp:base',
      ],

      'direct_dependent_settings': {
        'include_dirs': [
          '..',
        ],
      },

    },
  ],
}