{
  'targets' : [
    {
      'target_name': 'osc_views',
      'type': 'static_library',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/ui/ui.gyp:ui',
        '<(DEPTH)/ui/ui.gyp:ui_resources',
        '<(DEPTH)/views/views.gyp:views',
        '<(DEPTH)/skia/skia.gyp:skia',
      ],
      'sources': [
        'ui/views/axis_painter.h',
        'ui/views/axis_painter.cc',
        'ui/views/axis_background.h',
        'ui/views/axis_background.cc',
        'ui/views/yt_view.h',
        'ui/views/yt_view.cc',
        'ui/views/yt_view_container.h',
        'ui/views/yt_view_container.cc',
        'ui/views/handle.h',
        'ui/views/handle.cc',
        'ui/views/handle_bar.h',
        'ui/views/handle_bar.cc',
        'ui/views/handle_bar_observer.h',
        'ui/views/handle_bar_model.h',
        'ui/views/handle_bar_model_observer.h',
      ],
    }, 
 ],
}