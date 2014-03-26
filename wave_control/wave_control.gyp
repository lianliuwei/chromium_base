{
  'targets' : [
    {
      'target_name': 'wave_control',
      'type': 'static_library',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/ui/ui.gyp:ui',
        '<(DEPTH)/ui/ui.gyp:ui_resources',
        '<(DEPTH)/views/views.gyp:views',
        '<(DEPTH)/skia/skia.gyp:skia',
      ],
      'sources': [
        'wave_control.h',
        'wave_container.h',
        'yt_wave_container.h',
        'yl_wave_container.h',
        'xy_wave_container.h',
        'wave.h',
        'osc_wave.h',
        'simple_ana_wave.h',
        'simple_digit_wave.h',
        
        'wave_control_visitor.h',
        'wave_container_visitor.h',
        'wave_visitor.h',
        
        'ana_wave_data.h',
        'wave_range.h',
        
        'wave_view.h',
 
        'measure_line/measure_line.h',
        'measure_line/dual_line.h',
        'measure_line/single_line.h',
        'measure_line/measure_line_container.h',
        
        'list_model.h',
        'list_model_observer.h',
        'supports_user_data.h',
        'supports_user_data.cc',
      ],
    }, 
 ],
}