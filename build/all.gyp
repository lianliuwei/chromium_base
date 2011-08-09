{
  'targets': [
    {
      'target_name': 'All',
      'type': 'none',
      'dependencies': [
		'../base/base.gyp:*',
	    '../sample/test.gyp:*',
		'../testing/gtest.gyp:*',
		'../testing/gmock.gyp:*',
	  ],
    },
  ],
}