{
  'targets' : [
  
    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'AxisBackground',
      'sources': [
        'AxisBackground/main.cc',
      ],
       'dependencies': [
		'../Osc.gyp:osc_views',	
	  ],
    },
    
    {
      'includes': [ 'exe.gypi' ],
      'target_name': 'handleBar',
      'sources': [
        'handleBar/main.cc',
      ],
       'dependencies': [
		'../Osc.gyp:osc_views',	
	  ],
    },
    
 ],
}