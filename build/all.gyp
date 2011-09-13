{
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'dependencies': [
		'../base/base.gyp:*',
		'../ui/ui.gyp:*',
	    '../sample/test.gyp:*',
		'../testing/gtest.gyp:*',
		'../testing/gmock.gyp:*',
	  ],
    },
  ],
}