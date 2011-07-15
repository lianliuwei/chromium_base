#test gyp 
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
  ],

}
