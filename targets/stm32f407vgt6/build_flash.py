# build_flash.py

import subprocess
import sys

#######################################
# flash
#######################################

def jlink_flash():
    jlink_command = 'JLinkExe -device STM32F407VG -speed 4000 -if SWD -CommanderScript ./jlink-flash-fw-standalone.jlink'
    result = subprocess.call(jlink_command, shell=True)
    return result

openocd_cmd = [
    'openocd',
    '-f', '/usr/share/openocd/scripts/interface/stlink-v2.cfg',
    '-f', '/usr/share/openocd/scripts/target/stm32f4x.cfg',
    '-c', 'init',
    '-c', 'reset halt',
    '-c', 'flash write_image erase ./build/mx3g_stm32f407vgt6.elf',
    '-c', 'reset run',
    '-c', 'exit'
]

def openocd_flash():
        result = subprocess.run(openocd_cmd, check=True)
        return result

def main():
    # 获取命令行传递的参数
    arg1 = sys.argv[1]
    if arg1 == "flash":
        jlink_flash()
    if arg1 == "build":
        subprocess.run(['scons', '-j12'], check=True)
    if arg1 == "rebuild":
        subprocess.run(['scons', '-c'], check=True)
        subprocess.run(['scons', '-j12'], check=True)
    if arg1 == "clean":
        subprocess.run(['scons', '-c'], check=True)
    if arg1 == "rebuild-flash":
        subprocess.run(['scons', '-c'], check=True)
        subprocess.run(['scons', '-j12'], check=True)
        jlink_flash()
    if arg1 == "build-flash":
        subprocess.run(['scons', '-j12'], check=True)
        jlink_flash()

if __name__ == "__main__":
    main()