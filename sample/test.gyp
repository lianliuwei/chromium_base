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
  ],
}
