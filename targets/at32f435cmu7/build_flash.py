# build_flash.py

import subprocess
import sys

def jlink_flash():
    jlink_command = 'JLinkExe -device -AT32F435CMU7 -speed 4000 -if SWD -CommanderScript ./jlink-flash-fw-standalone.jlink'
    result = subprocess.call(jlink_command, shell=True)
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

astyle_cmd = [
    'bash', '../../tools/astyle/check_code_style_all.sh',
    '--fix'
]
def astyle_format():
        result = subprocess.run(astyle_cmd, check=True)
        return result


astyle_check_cmd = [
    'bash', '../../tools/astyle/check_code_style_all.sh',
    'git diff', '--check'
]

def astyle_check():
        result = subprocess.run(astyle_check_cmd, check=True)
        return result