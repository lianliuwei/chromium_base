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
        'osc_wave.cc',
        'osc_wave_observer.h',
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
        
        'osc_wave_group/osc_wave_group.h',
        'osc_wave_group/osc_wave_group.cc',
        'osc_wave_group/trigger_part.h',
        'osc_wave_group/horizontal_part.h',
        'osc_wave_group/vertical_part.h',
        'osc_wave_group/osc_wave_group_observer.h',
        
        'views/wave_control_view_factory.h',
        'views/wave_control_view_factory.cc',
        'views/wave_control_view.h',
        'views/wave_control_view.cc',
        'views/yt_wave_container_view.h',
        'views/ana_wave_view.h',
 
        'osc_wave_group/test_osc_wave.h',
        'osc_wave_group/test_osc_wave.cc',
        'osc_wave_group/common_osc_wave_group.h',
        'osc_wave_group/common_osc_wave_group.cc',
        
        'list_model.h',
        'list_model_observer.h',
        'supports_user_data.h',
        'supports_user_data.cc',
      ],
    }, 
 ],
}