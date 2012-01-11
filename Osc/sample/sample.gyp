{
  'targets' : [
  
    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'AxisBackground',
      'sources': [
        'AxisBackground/axis.cc',
        'main.cc',
        'example_vew.h',
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
        'example_vew.h',
      ],
       'dependencies': [
		'../Osc.gyp:osc_views',	
	  ],
    },
    
 ],
}