{
  'targets': [
    {
      'target_name': 'base',
      'type': 'static_library',
      'sources': [
        '../build/build_config.h',
		'port.h',
		'base_api.h',
		'basictypes.h',
		'string_piece.h',
		'string_piece.cc',
		'compiler_specific.h',
		'base_switches.h',
		'base_switches.cc',
		'atmicops.h',
		'atmicops_internals_x86_msvc.h',
      ],
      'include_dirs': [
          '..',
      ],
    },
  ],
}