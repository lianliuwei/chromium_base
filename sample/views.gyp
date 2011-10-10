{
  'variables': {
    'grit_base_out_dir': '<(SHARED_INTERMEDIATE_DIR)/ui',
    'repack_out_dir': '<(PRODUCT_DIR)/Locales',
    'repack_path': '<(DEPTH)/tools/grit/grit/format/repack.py',
  },
  'targets' : [
    {
      'target_name': 'locales',
      'type': 'none',
      'actions': [
        {
          'action_name': 'en-US',
          'variables': {
            'pak_inputs': [
                '<(grit_base_out_dir)/ui_strings/ui_strings_en-US.pak',
                '<(grit_base_out_dir)/app_locale_settings/app_locale_settings_en-US.pak',
              ],
          },
          'inputs': [
            '<(repack_path)',
            '<@(pak_inputs)',
          ],
          'outputs': [
            '<(repack_out_dir)/en-US.pak',
          ],
          'action': ['<(DEPTH)/setup_env.bat&&python', '<(repack_path)', '<@(_outputs)',
                     '<@(pak_inputs)'],
          'message': 'Generating en-US locales',
        },
      ],
      'dependencies': [
        '<(DEPTH)/ui/base/strings/ui_strings.gyp:ui_strings',
      ],
    },
  ],
}