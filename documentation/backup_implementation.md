# Backup Implementation Documentation

**Authors:** Jayden Navarro, Coy Humphrey

**Purpose:** Describes the implementation of our backup solution.

## Overview

We used rsync to backup all important files on our main disk to a backup disk. We will now periodically run a backup script to perform a diff backup from our primary drive onto our secondary backup drive after important milestones.

## Implementation Steps

### Formatting Backup Drive

We formatted our backup drive (sdb) as a single xfs partition. To do this, we ran `fdisk sdb` to create a new partition table as well as a single partition (sdb1) filling the entire disk.

To format our newly created parition, we ran `mkfs -t xfs /sdb1`.

### Mounting Backup Drive

Before running our backups, we mount the backup drive at /mnt/backup. The command to do this is `mount /dev/sdb1 /mnt/backup`.

### Running Backup

We simply ran `sudo ./backup.sh` on each server to perform the backup. If an initial backup has already taken place, only a copy of changed files will occur.

### Running Repair from Backup

To restore the backup to a live system, run `sudo restore.sh`.

If the system cannot be booted, boot from a live cd containing rsync (an Arch Linux live cd works well for this). Then mount sdb1 as /mnt/backup and sda1 as /mnt/root.

	mkdir /mnt/backup
	mkdir /mnt/root
	mount /dev/sda1 /mnt/root
	mount /dev/sdb1 /mnt/backup

Once these partitions are mounted, run rsync from the backup to the root filesystem.

	rsync -aAXv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/media/*","/lost+found"} /mnt/backup /tn/root

### Scripts

#### Backup Script (backup.sh)
    rsync -aAXv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/media/*","/lost+found"} / /mnt/backup

#### Repair Script (repair.sh)
	rsync -aAXv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/media/*","/lost+found"} /mnt/backup /

## Initial Implementation Notes

We ran into issues mounting the secondary drive, but were able to solve this by partitioning TODO: Coy .

We checked to make sure that the copy was succesful by inspecting the file structure in the mounted backup disk. Everything was intact. We then created a new file in the primary drive and ran the backup script again. We observed that only a partial copy of the drive was made, only copying the changed files (which was what we had expected and wanted). We then insured that the new file was located in the mounted backup disk, which it was. We tested to see if our permissions had remained intact, and we observed that we were not able to enter the home directories of other users on the backup.
