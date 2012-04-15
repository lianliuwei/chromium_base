{
  'targets' : [

    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'AxisBackground',
      'sources': [
        'AxisBackground/axis.cc',
        'main.cc',
        'example_view.h',
      ],
       'dependencies': [
		    '../Osc.gyp:osc_views',
	    ],
    },
    
    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'handleBar',
      'sources': [
        'handleBar/handleBar.cc',
        'main.cc',
        'example_view.h',
      ],
       'dependencies': [
		    '../Osc.gyp:osc_views',	
	    ],
    },
    
    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'BarLayout',
      'sources': [
        'BarLayout/bar_layout.cc',
        'main.cc',
        'example_view.h',
      ],
       'dependencies': [
		    '../Osc.gyp:osc_views',	
	    ],
    },
	
    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'WaveView',
      'sources': [
        'wave_view/wave_view.cc',
        'main.cc',
        'example_view.h',
      ],
       'dependencies': [
		    '../Osc.gyp:osc_views',	
	    ],
    },
    
  ],
}