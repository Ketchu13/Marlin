#
# sets output_port
#  if target_filename is found then that drive is used
#  else if target_drive is found then that drive is used
#

target_filename = "FIRMWARE.CUR"
target_drive = "REARM"

import os
import platform
current_OS = platform.system()


def detect_error(e):
    print '\nUnable to find destination disk (' + e + ')\n' \
          'Please select it in platformio.ini using the upload_port keyword ' \
          '(https://docs.platformio.org/en/latest/projectconf/section_env_upload.html)\n' \
          'or copy the firmware (.pioenvs/' + env.get('PIOENV') + '/firmware.bin) manually to the appropriate disk\n'

if current_OS == 'Windows':
    #
    # platformio.ini will accept this for a Windows upload port designation: 'upload_port = L:'
    #   Windows - doesn't care about the disk's name, only cares about the drive letter
    #

    #
    # get all drives on this computer
    #
    import subprocess
    # typical result (string): 'Drives: C:\ D:\ E:\ F:\ G:\ H:\ I:\ J:\ K:\ L:\ M:\ Y:\ Z:\'
    driveStr = subprocess.check_output("wmic logicaldisk get deviceid, volumename")
    # typical result (string): 'C:\ D:\ E:\ F:\ G:\ H:\ I:\ J:\ K:\ L:\ M:\ Y:\ Z:\'
    
   
    
    # typical result (array of stings): ['C:\\', 'D:\\', 'E:\\', 'F:\\',
    # 'G:\\', 'H:\\', 'I:\\', 'J:\\', 'K:\\', 'L:\\', 'M:\\', 'Y:\\', 'Z:\\']
    import re
    driveStr =re.sub('[ +]', '', driveStr) #driveStr.strip('\r\r').sub('[\s+]', '', s)

    drives = driveStr.split('\r\r\n')

    upload_disk = 'Disk not found'
    target_file_found = False
    target_drive_found = False
    for drive in drives:
        if ':'in drive:
            final_drive_name = drive.strip().rstrip('\\').split(':')[0] + ':'   # typical result (string): 'C:'
            if len(final_drive_name) > 1:
                volume_info = drive.strip().rstrip('\\').split(':')[1]
                
                if target_drive in volume_info and target_file_found == False:  # set upload if not found target file yet
                    target_drive_found = True
                    upload_disk = final_drive_name
                    print upload_disk
