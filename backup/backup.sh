#!/bin/bash
# https://wiki.archlinux.org/index.php/full_system_backup_with_rsync
rsync -aAXv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/media/*","/lost+found"} / /path/to/backup/folder