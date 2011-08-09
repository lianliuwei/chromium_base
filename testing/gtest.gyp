# Copyright (c) 2009 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'targets': [
    {
      'target_name': 'gtest',
      'type': 'static_library',
      'sources': [
        'gtest/include/gtest/gtest-death-test.h',
        'gtest/include/gtest/gtest-message.h',
        'gtest/include/gtest/gtest-param-test.h',
        'gtest/include/gtest/gtest-printers.h',
        'gtest/include/gtest/gtest-spi.h',
        'gtest/include/gtest/gtest-test-part.h',
        'gtest/include/gtest/gtest-typed-test.h',
        'gtest/include/gtest/gtest.h',
        'gtest/include/gtest/gtest_pred_impl.h',
        'gtest/include/gtest/gtest_prod.h',
        'gtest/include/gtest/internal/gtest-death-test-internal.h',
        'gtest/include/gtest/internal/gtest-filepath.h',
        'gtest/include/gtest/internal/gtest-internal.h',
        'gtest/include/gtest/internal/gtest-linked_ptr.h',
        'gtest/include/gtest/internal/gtest-param-util-generated.h',
        'gtest/include/gtest/internal/gtest-param-util.h',
        'gtest/include/gtest/internal/gtest-port.h',
        'gtest/include/gtest/internal/gtest-string.h',
        'gtest/include/gtest/internal/gtest-tuple.h',
        'gtest/include/gtest/internal/gtest-type-util.h',
        'gtest/src/gtest-all.cc',
        'gtest/src/gtest-death-test.cc',
        'gtest/src/gtest-filepath.cc',
        'gtest/src/gtest-internal-inl.h',
        'gtest/src/gtest-port.cc',
        'gtest/src/gtest-printers.cc',
        'gtest/src/gtest-test-part.cc',
        'gtest/src/gtest-typed-test.cc',
        'gtest/src/gtest.cc',
        'multiprocess_func_list.cc',
        'multiprocess_func_list.h',
        'platform_test.h',
      ],
      'sources!': [
        'gtest/src/gtest-all.cc',  # Not needed by our build.
      ],
      'include_dirs': [
        'gtest',
        'gtest/include',
      ],
      'conditions': [
        ['OS == "mac"', {
          'sources': [
            'gtest_mac.h',
            'gtest_mac.mm',
            'platform_test_mac.mm'
          ],
          'link_settings': {
            'libraries': [
              '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
            ],
          },
        }],
      ],
      'direct_dependent_settings': {
        'defines': [
          'UNIT_TEST',
        ],
        'include_dirs': [
          'gtest/include',  # So that gtest headers can find themselves.
        ],
        'target_conditions': [
          ['_type=="executable"', {
            'test': 1,
            'conditions': [
              ['OS=="mac"', {
                'run_as': {
                  'action????': ['${BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}'],
                },
              }],
              ['OS=="win"', {
                'run_as': {
                  'action????': ['$(TargetPath)', '--gtest_print_time'],
                },
              }],
            ],
          }],
        ],
        'msvs_disabled_warnings': [4800],
      },
    },
    {
      'target_name': 'gtest_main',
      'type': 'static_library',
      'dependencies': [
        'gtest',
      ],
      'sources': [
        'gtest/src/gtest_main.cc',
      ],
    },
  ],
}
