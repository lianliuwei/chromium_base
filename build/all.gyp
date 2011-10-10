{
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'dependencies': [
		    '../base/base.gyp:*',
		    '../ui/ui.gyp:*',
	      '../sample/base.gyp:*',
        '../sample/ui.gyp:*',
        '../sample/views.gyp:*',
		    '../testing/gtest.gyp:*',
		    '../testing/gmock.gyp:*',
        '../views/views.gyp:*',
	  ],
    },
  ],
}