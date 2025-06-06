import os
import sys
import rtconfig

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = os.path.normpath(os.getcwd() + './rt-thread')

# set RTT_ROOT
if not os.getenv("RTT_ROOT"):
    RTT_ROOT="rt-thread"

sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
from building import *

TARGET = 'rtthread.' + rtconfig.TARGET_EXT

AddOption('--run',
        dest = 'run',
        type='string',
        nargs=1,
        action = 'store',
        default = "",
        help = 'Upload or debug application using openocd')

DefaultEnvironment(tools=[])
env = Environment(tools = ['mingw'],
    AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
    CC = rtconfig.CC, CCFLAGS = rtconfig.CFLAGS,
    AR = rtconfig.AR, ARFLAGS = '-rc',
    LINK = rtconfig.LINK, LINKFLAGS = rtconfig.LFLAGS,
    CXX = rtconfig.CXX, CXXFLAGS = rtconfig.CXXFLAGS)

env.PrependENVPath('PATH', rtconfig.EXEC_PATH)
env['ASCOM'] = env['ASPPCOM']

Export('RTT_ROOT')
Export('rtconfig')

SDK_ROOT = os.path.abspath('./')

if os.path.exists(os.path.join(SDK_ROOT, 'libraries')):
    libraries_path_prefix = os.path.join(SDK_ROOT, 'libraries')
else:
    libraries_path_prefix = os.path.join(os.path.dirname(SDK_ROOT), 'libraries')

SDK_LIB = libraries_path_prefix
Export('SDK_LIB')


GDB = rtconfig.GDB

# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT, has_libcpu=False)

hpm_library = 'hpm_sdk'
rtconfig.BSP_LIBRARY_TYPE = hpm_library

# include soc
objs.extend(SConscript(os.path.join(libraries_path_prefix, hpm_library,'soc', rtconfig.SOC_FAMILY, rtconfig.CHIP_NAME, 'SConscript')))

# include libraries
objs.extend(SConscript(os.path.join(libraries_path_prefix, hpm_library, 'SConscript')))

# include components
objs.extend(SConscript(os.path.join(libraries_path_prefix, hpm_library, 'components', 'SConscript')))


# includes rtt drivers
objs.extend(SConscript(os.path.join(libraries_path_prefix, 'drivers',  'SConscript')))

# includes misc
objs.extend(SConscript(os.path.join(libraries_path_prefix, 'misc',  'SConscript')))

# env.Tool('compilation_db')
# env.CompilationDatabase()

# make a building
DoBuilding(TARGET, objs)
