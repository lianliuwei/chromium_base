{ 
  'variables': {
    'variables': {
      'variables': {
        # Compute the architecture that we're building on.
        'conditions': [
          [ 'OS=="win" or OS=="mac"', {
            'host_arch%': 'ia32',
          }, {
            # This handles the Unix platforms for which there is some support.
            # Anything else gets passed through, which probably won't work very
            # well; such hosts should pass an explicit target_arch to gyp.
            'host_arch%':
              '<!(uname -m | sed -e "s/i.86/ia32/;s/x86_64/x64/;s/amd64/x64/;s/arm.*/arm/;s/i86pc/ia32/")',
          }],
        ],
      },
      'host_arch%': '<(host_arch)',

      # We used to provide a variable for changing how libraries were built.
      # This variable remains until we can clean up all the users.
      # This needs to be one nested variables dict in so that dependent
      # gyp files can make use of it in their outer variables.  (Yikes!)
      # http://code.google.com/p/chromium/issues/detail?id=83308
      'library%': 'static_library',
      # Default architecture we're building for is the architecture we're
      # building on.
      'target_arch%': '<(host_arch)',
	    'conditions': [

        # A flag for POSIX platforms
        ['OS=="win"', {
          'os_posix%': 0,
        }, {
          'os_posix%': 1,
        }],

        # Flags to use X11 on non-Mac POSIX platforms
        ['OS=="win" or OS=="mac" or OS=="android"', {
          'use_glib%': 0,
          'toolkit_uses_gtk%': 0,
          'use_x11%': 0,
        }, {
          # TODO(dnicoara) Wayland build should have these disabled, but
          # currently GTK and X is too spread and it's hard to completely
          # remove every dependency.
          'use_glib%': 1,
          'toolkit_uses_gtk%': 1,
          'use_x11%': 1,
        }],
      ],
      # Set ARM-v7 compilation flags
      'armv7%': 0,
    },
    # Copy conditionally-set variables out one scope.
    'library%': '<(library)',
    # Variable 'component' is for cases where we would like to build some
    # components as dynamic shared libraries but still need variable
    # 'library' for static libraries.
    # By default, component is set to whatever library is set to and
    # it can be overriden by the GYP command line or by ~/.gyp/include.gypi.
    'component%': '<(library)',
    'target_arch%': '<(target_arch)',
    'os_posix%': '<(os_posix)',
    'use_glib%': '<(use_glib)',
    'toolkit_uses_gtk%': '<(toolkit_uses_gtk)',
    'use_x11%': '<(use_x11)',
    'armv7%': '<(armv7)',
  },

  'target_defaults': {
    'variables': {
      # See http://msdn.microsoft.com/en-us/library/aa652360(VS.71).aspx
      'win_release_Optimization%': '2', # 2 = /Os
      'win_debug_Optimization%': '0',   # 0 = /Od
      # See http://msdn.microsoft.com/en-us/library/8wtf2dfz(VS.71).aspx
      'win_debug_RuntimeChecks%': '3',    # 3 = all checks enabled, 0 = off
      # See http://msdn.microsoft.com/en-us/library/47238hez(VS.71).aspx
      'win_debug_InlineFunctionExpansion%': '',    # empty = default, 0 = off,
      'win_release_InlineFunctionExpansion%': '2', # 1 = only __inline, 2 = max
      # VS inserts quite a lot of extra checks to algorithms like
      # std::partial_sort in Debug build which make them O(N^2)
      # instead of O(N*logN). This is particularly slow under memory
      # tools like ThreadSanitizer so we want it to be disablable.
      # See http://msdn.microsoft.com/en-us/library/aa985982(v=VS.80).aspx
      'win_debug_disable_iterator_debugging%': '0',
      
      'msvs_debug_link_incremental%': '2',
      
      # Needed for some of the largest modules.
      'msvs_debug_link_nonincremental%': '1',
      
      'conditions': [
        ['component=="shared_library"', {
          # See http://msdn.microsoft.com/en-us/library/aa652367.aspx
          'win_release_RuntimeLibrary%': '2', # 2 = /MD (nondebug DLL)
          'win_debug_RuntimeLibrary%': '3',   # 3 = /MDd (debug DLL)
        }, {
          # See http://msdn.microsoft.com/en-us/library/aa652367.aspx
          'win_release_RuntimeLibrary%': '2', 
          'win_debug_RuntimeLibrary%': '3', 
        }],
        ['component=="shared_library"', {
          'win_use_allocator_shim%': 0,
        }],
        ['MSVS_VERSION=="2005"', {
          'msvs_multi_core_compile%': 0,
        },{
          'msvs_multi_core_compile%': 1,
        }],
        # Don't do incremental linking for large modules on 32-bit.
        ['MSVS_OS_BITS==32', {
          'msvs_large_module_debug_link_mode%': '1',  # No
        },{
          'msvs_large_module_debug_link_mode%': '2',  # Yes
        }],
        ['MSVS_VERSION=="2010e" or MSVS_VERSION=="2008e" or MSVS_VERSION=="2005e"', {
          'msvs_express%': 1,
          'secure_atl%': 0,
        },{
          'msvs_express%': 0,
          'secure_atl%': 1,
        }],
      ],
    },#variables
    
    'defines': [
      '_WIN32_WINNT=0x0600',
      'WINVER=0x0600',
      'WIN32',
      '_WINDOWS',
      'NOMINMAX',
      '_CRT_RAND_S',
      'CERT_CHAIN_PARA_HAS_EXTRA_FIELDS',
      'WIN32_LEAN_AND_MEAN',
      '_ATL_NO_OPENGL',
      '_HAS_TR1=0',
      '__STD_C',
      '_CRT_SECURE_NO_DEPRECATE',
      '_SCL_SECURE_NO_DEPRECATE',
    ],
    'conditions': [
      ['component=="static_library"', {
        'defines': [
          '_HAS_EXCEPTIONS=0',
          #using with /MD and /MDd
          '_STATIC_CPPLIB',
		  '_DISABLE_DEPRECATE_STATIC_CPPLIB',
        ],
      }],
      ['secure_atl', {
        'defines': [
          '_SECURE_ATL',
        ],
      }],
    ],
    # no using cygwin method in chromium
    'msvs_cygwin_shell': 0,

    'msvs_system_include_dirs': [
      '$(VSInstallDir)/VC/atlmfc/include',
    ],
    'msvs_disabled_warnings': [4351, 4396, 4503, 4819,
      # TODO(maruel): These warnings are level 4. They will be slowly
      # removed as code is fixed.
      4100, 4121, 4125, 4127, 4130, 4131, 4189, 4201, 4238, 4244, 4245,
      4310, 4355, 4428, 4481, 4505, 4510, 4512, 4530, 4610, 4611, 4701,
      4702, 4706,
    ],
    'msvs_settings': {
      'VCCLCompilerTool': {
        'MinimalRebuild': 'false',
        'BufferSecurityCheck': 'true',
        'EnableFunctionLevelLinking': 'true',
        'RuntimeTypeInfo': 'false',
        'WarningLevel': '4',
        'WarnAsError': 'false',
        'DebugInformationFormat': '3',
        'conditions': [
          ['msvs_multi_core_compile', {
            'AdditionalOptions': ['/MP'],
          }],
          ['component=="shared_library"', {
            'ExceptionHandling': '1',  # /EHsc
          }, {
            'ExceptionHandling': '0',
          }],
        ],
      },
      'VCLibrarianTool': {
        'AdditionalOptions': ['/ignore:4221'],
        'AdditionalLibraryDirectories': [
        ],
      },
      'VCLinkerTool': {
        'AdditionalDependencies': [
          'version.lib',
          'msimg32.lib',
          'usp10.lib',
          'psapi.lib',
          'dbghelp.lib',
          'winmm.lib',
          'shlwapi.lib',
        ],

        'AdditionalLibraryDirectories': [
        ],
        'GenerateDebugInformation': 'true',
        'MapFileName': '$(OutDir)\\$(TargetName).map',
        'ImportLibrary': '$(OutDir)\\lib\\$(TargetName).lib',
        'FixedBaseAddress': '1',
        # SubSystem values:
        #   0 == not set
        #   1 == /SUBSYSTEM:CONSOLE
        #   2 == /SUBSYSTEM:WINDOWS
        # Most of the executables we'll ever create are tests
        # and utilities with console output.
        'SubSystem': '1',
      },
      'VCMIDLTool': {
        'GenerateStublessProxies': 'true',
        'TypeLibraryName': '$(InputName).tlb',
        'OutputDirectory': '$(IntDir)',
        'HeaderFileName': '$(InputName).h',
        'DLLDataFileName': 'dlldata.c',
        'InterfaceIdentifierFileName': '$(InputName)_i.c',
        'ProxyFileName': '$(InputName)_p.c',
      },
      'VCResourceCompilerTool': {
        'Culture' : '1033',
        'AdditionalIncludeDirectories': [
          '<(DEPTH)',
          '<(SHARED_INTERMEDIATE_DIR)',
        ],
      },
    },
            
    'default_configuration': 'Debug_win32',
    
    'configurations': {
	  'Common_Base': {
        'abstract': 1,
        'msvs_configuration_attributes': {
          'OutputDirectory': '$(SolutionDir)$(ConfigurationName)',
          'IntermediateDirectory': '$(OutDir)\\obj\\$(ProjectName)',
          'CharacterSet': '1',
        },
      },
      'x86_Base': {
        'abstract': 1,
        'msvs_configuration_platform': 'win32',
        'msvs_settings': {
          'VCLinkerTool': {
            'TargetMachine': '1',
            'AdditionalOptions': [
              '/safeseh',
              '/dynamicbase',
              '/ignore:4199',
              '/ignore:4221',
              '/nxcompat',
              ],
          },
        },
      },
      'x64_Base': {
        'abstract': 1,
        'msvs_configuration_platform': 'x64',
        'msvs_settings': {
          'VCLinkerTool': {
            'TargetMachine': '17', # x86 - 64
            'AdditionalOptions': [
              # safeseh is not compatible with x64
              '/dynamicbase',
              '/ignore:4199',
              '/ignore:4221',
              '/nxcompat',
            ],
          },
          'VCLibrarianTool': {
          },
        },
      },
      'Debug_Base': {
        'abstract': 1,
        'defines': [
          'DYNAMIC_ANNOTATIONS_ENABLED=1',
          'WTF_USE_DYNAMIC_ANNOTATIONS=1',
        ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'Optimization': '<(win_debug_Optimization)',
            'PreprocessorDefinitions': ['_DEBUG'],
            'BasicRuntimeChecks': '<(win_debug_RuntimeChecks)',
            'RuntimeLibrary': '<(win_debug_RuntimeLibrary)',
            'conditions': [
              # According to MSVS, InlineFunctionExpansion=0 means
              # "default inlining", not "/Ob0".
              # Thus, we have to handle InlineFunctionExpansion==0 separately.
              ['win_debug_InlineFunctionExpansion==0', {
                'AdditionalOptions': ['/Ob0'],
              }],
              ['win_debug_InlineFunctionExpansion!=""', {
                'InlineFunctionExpansion':
                  '<(win_debug_InlineFunctionExpansion)',
              }],
              ['win_debug_disable_iterator_debugging==1', {
                'PreprocessorDefinitions': ['_HAS_ITERATOR_DEBUGGING=0'],
              }],
            ],
          },
          'VCLinkerTool': {
            'LinkIncremental': '<(msvs_debug_link_incremental)',
          },
          'VCResourceCompilerTool': {
            'PreprocessorDefinitions': ['_DEBUG'],
          },
        },
      },
      'Release_Base': {
        'abstract': 1,
        'defines': [
          'NDEBUG',
        ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'Optimization': '<(win_release_Optimization)',
            'RuntimeLibrary': '<(win_release_RuntimeLibrary)',
            'conditions': [
              # According to MSVS, InlineFunctionExpansion=0 means
              # "default inlining", not "/Ob0".
              # Thus, we have to handle InlineFunctionExpansion==0 separately.
              ['win_release_InlineFunctionExpansion==0', {
                'AdditionalOptions': ['/Ob0'],
              }],
              ['win_release_InlineFunctionExpansion!=""', {
                'InlineFunctionExpansion':
                  '<(win_release_InlineFunctionExpansion)',
              }],
            ],
          },
          'VCLinkerTool': {
            'LinkIncremental': '1',
          },
        },
      },
      'Purify_Base': {
        'abstract': 1,
        'defines': [
          'PURIFY',
        ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'Optimization': '0',
            'RuntimeLibrary': '0',
            'BufferSecurityCheck': 'false',
          },
          'VCLinkerTool': {
            'EnableCOMDATFolding': '1',
            'LinkIncremental': '1',
          },
        },
      },
      #
      # Concrete configurations
      #
      'Debug_win32': {
        'inherit_from': ['Common_Base', 'x86_Base', 'Debug_Base'],
      },
      'Release_win32': {
        'inherit_from': ['Common_Base', 'x86_Base', 'Release_Base'],
      },
      'Purify_win32': {
        'inherit_from': ['Common_Base', 'x86_Base', 'Release_Base', 'Purify_Base'],
      },
      'Debug_x64': {
        'inherit_from': ['Common_Base', 'x64_Base', 'Debug_Base'],
      },
      'Release_x64': {
        'inherit_from': ['Common_Base', 'x64_Base', 'Release_Base'],
      },
      'Purify_x64': {
        'inherit_from': ['Common_Base', 'x64_Base', 'Release_Base', 'Purify_Base'],
      },
    },#configurations   
  },#target_defaults
}