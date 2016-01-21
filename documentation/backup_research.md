# Server Backup Research and Implementation Plan
#### **Author:** Jayden Navarro
#### **Purpose:** Describe what has been researched in regards to backing up the servers.

## Overview
We have researched two primary options for backing up the server. One is called rsync, and the other is called CloneZilla.

We have found that rsync will most likely be more suitable for our needs. The 
primary reason being that backing up requires no down-time with rsync.

## Pros and Cons
### CloneZilla
#### Pros
1. Easy to use GUI.
2. Allows for full backup including MBR.

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
