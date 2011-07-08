#test gyp 
{
  'targets' : [
    {
      'target_name': 'gyp_test',
      'type': 'executable',
      'sources': [
        'main.cpp',
      ],
      'dependencies': [
        '../base/base.gyp:*',
      ],
    },
  ],
}
