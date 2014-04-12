{
  'targets' : [
    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'wave_control_example',
      'sources': [
        'main_view.cc',
        'main.cc',
        'example_view.h',
        'test_osc_wave.h',
        'test_osc_wave.cc',
      ],
       'dependencies': [
		    '../wave_control.gyp:wave_control',
	    ],
    },
    
  ],
}