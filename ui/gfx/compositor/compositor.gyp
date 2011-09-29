# Copyright (c) 2011 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {
    'chromium_code': 1,
    'views_compositor': 0,
  },
  'target_defaults': {
    'sources/': [
      ['exclude', '_(gl|win)\\.(cc?)$'],
    ],
    'conditions': [
      ['os_posix == 1 and OS != "mac"', {
        'sources/': [['include', '_(gl)\\.(h|cc)$'],]
      }],
      ['OS == "win"', {
        'sources/': [['include', '_(win)\\.(h|cc)$'],]
      }],
    ],
  },
  'targets': [
    {
      'target_name': 'compositor',
      'type': '<(component)',
      'dependencies': [
        '../../../base/base.gyp:base',
        '../../../base/third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
        '../../../skia/skia.gyp:skia',
        #'../../../ui/gfx/gl/gl.gyp:gl',
        '../../../ui/ui.gyp:ui',
      ],
      'defines': [
        'COMPOSITOR_IMPLEMENTATION',
      ],
      'sources': [
        'compositor.cc',
        'compositor.h',
        'compositor_export.h',
        #'compositor_gl.cc',
        #'compositor_gl.h',
        'compositor_observer.h',
        'compositor_stub.cc',
        #'compositor_win.cc',
        'layer.cc',
        'layer.h',
        'layer_animator.cc',
        'layer_animator.h',
      ],
      'conditions': [
        ['os_posix == 1 and OS != "mac"', {
          'sources!': [
            'compositor_stub.cc',
          ],
        }],
        ['OS == "win" and views_compositor == 1', {
          'sources!': [
            'compositor_stub.cc',
          ],
          # TODO(sky): before we make this real need to remove
          # IDR_BITMAP_BRUSH_IMAGE.
          'dependencies': [
            '<(DEPTH)/ui/ui.gyp:gfx_resources',
          ],
          'link_settings': {
            'libraries': [
              '-ld3d10.lib',
              '-ld3dx10d.lib',
              '-ldxerr.lib',
              '-ldxguid.lib',
            ]
          },
        }],
        ['OS == "win" and views_compositor == 0', {
          'sources/': [
            ['exclude', '^compositor_win.cc'],
          ],
        }],
      ],
    },
  ],
}
