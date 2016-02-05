# Server Backup Research and Implementation Plan

**Authors:** Jayden Navarro, Coy Humphrey

**Purpose:** Describe what has been researched in regards to backing up the servers, and how we plan to implement it.

## Overview
We have researched two primary options for backing up the server. One is called rsync, and the other is called CloneZilla.

We have found that rsync will most likely be more suitable for our needs. The primary reason being that backing up requires no down-time with rsync.

## Pros and Cons
### CloneZilla
#### Pros
1. Easy to use GUI.
2. Allows for full backup including Master Boot Record (MBR).

#### Cons
1. Requires the server to be down to perform backup.
2. Requires separate ISO that isn't part of standard Linux.

### rsync
#### Pros
1. Backup without downtime.
2. Easily configurable.

#### Cons
1. Does not copy over MBR.
2. Requires seperate ISO to boot from to repair corrupted disk.

## Implementation Plan
We plan to make a copy of the tnvme server OS file-tree from logical disk A (sda) onto logical disk B (sdb) using rsync. Then we hope to check sdb for the contents, to ensure that the copy was made successfully.

We may attempt to remove test files from sda, and try to perform a copy over from sdb to test the repair functionality.

In the event of a failure that breaks the MBR, we can reinstall CentOS (thus creating a new MBR) and then restore the rest of our data with rsync.

### Restoring a Broken System

For a system with a working MBR that will not boot (perhaps from a broken kernel), an external .ISO will need to be used. An Arch Linux dvd makes a good choice for this, as it allows booting into a live environment and includes rsync.

After booting into the live system, we will need to mount both the primary and backup drives. Our scripts assume that the backup drive is mounted to /mnt/backup. Assuming the backup partition is sdb1, this can be accomplished with the following command:

	mkdir /mnt/backup
	mount /dev/sdb1 /mnt/backup

### Scripts

	backup.sh
	rsync -aAXv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/media/*","/lost+found"} / /path/to/backup/folder

This script is pulled from the [Arch Linux documentation for full system backups](https://wiki.archlinux.org/index.php/full_system_backup_with_rsync).

The -aAX options ensure that ownership info, timestamps, and other important attributes are preserved.

We exclude the contents of several directories whose contents are either automatically generated (dev, proc,...) or whose contents contain attached devices (mnt, media).

After the system backup, we unmount the backup drive to avoid accidentally breaking it using `umount /mnt/backup/`.
