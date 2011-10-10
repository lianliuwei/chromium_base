{
  'targets' : [
    {
      'target_name': 'singleton',
      'type': 'executable',
      'sources': [
        'singleton/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
    {
      'target_name': 'observer_list',
      'type': 'executable',
      'sources': [
        'observer_list/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
    {
      'target_name': 'scoped_ptr',
      'type': 'executable',
      'sources': [
        'scoped_ptr/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
    {
      'target_name': 'log',
      'type': 'executable',
      'sources': [
        'log/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
    {
      'target_name': 'arraySize',
      'type': 'executable',
      'sources': [
        'arraySize/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
	  {
      'target_name': 'callback',
      'type': 'executable',
      'sources': [
        'callback/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
	  {
      'target_name': 'time',
      'type': 'executable',
      'sources': [
        'time/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
    {
      'target_name': 'message_loop',
      'type': 'executable',
      'sources': [
        'message_loop/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
    {
      'target_name': 'platform_thread',
      'type': 'executable',
      'sources': [
        'platform_thread/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
    {
      'target_name': 'thread',
      'type': 'executable',
      'sources': [
        'thread/main.cc',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
  	{
      'target_name': 'testing',
      'type': 'executable',
      'sources': [
	    # Infrastructure files.
        'testing/run_all_unittests.cc',
        'testing/gtest_unittest.cc',
      ],
      'dependencies': [
        '../testing/gtest.gyp:gtest',
      ],
    },
	  {
      'target_name': 'mocking',
      'type': 'executable',
      'sources': [
	      'mocking/FooInterface.h',
		    'mocking/FooMock.h',
        'mocking/FooMain.cc',
        'mocking/Foo_test.cc',
      ],
      'dependencies': [
        '../testing/gmock.gyp:gmock',
      ],
    },
  ],
}
