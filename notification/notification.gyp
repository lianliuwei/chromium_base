{
  'targets': [
    {
      'target_name': 'notification',
      'type': 'static_library',
      'sources': [
        'notification_details.h',
        'notification_observer.h',
        'notification_registrar.cc',
        'notification_registrar.h',
        'notification_service.h',
        'notification_source.h',
        'notification_types.h',
        'notification_service_impl.h',
        'notification_service_impl.cc',
       ],
      'include_dirs': [
          '..',
      ],
      'defines': [
         'NOTIFICATION_IMPLEMENTATION',
      ],
      'dependencies': [
        '../base/base.gyp:base',
      ],
    },
  ],
}