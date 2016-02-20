# RDMA Performance Implementation Documentation

## BIOS Changes Steps

1. Use F9 to select System Utilities.
1. Select System Configuration.
1. Select BIOS Platform Configuration.
1. Select System Options.
1. Under "Advanced Options"/"Fan and Thermal Options" we changed "Thermal Configuration" to "Increased Cooling".
1. All other BIOS options that we wanted to look into were either properly set or were not visible.

## Other Changes Made

1. CPU Frequency governors were set to performance.
1. Kernel Idle Loop Tuning was enabled in /etc/modprobe.d/mlnx.conf.
1. Core frequency was verified to be at the maximum.
1. ConnectX Optimized steering was enabled in /etc/modprob.d/mlnx.conf.
