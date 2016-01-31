# RDMA Performance Research Documentation

## Resources

[Performance Tuning Guide for Mellanox Network Adapters](http://www.mellanox.com/related-docs/prod_software/Performance_Tuning_Guide_for_Mellanox_Network_Adapters.pdf)

[CPU Frequency Governor Scaling](https://wiki.archlinux.org/index.php/CPU_frequency_scaling)

## Settings/Commands used

#### BIOS Settings for Haswell Processors

| Type | BIOS Option | Values |
| ---- | ----------- | ------ |
| General | Operating Mode /Power profile | Maximum Performance |
| Processor | C-States | Disabled |
|           | Turbo mode | Enabled |
|           | Hyper-Threading | HPC: disabled |
|           |                 | Data Centers: enabled |
|           | IO non posted prefetching | Enabled |
|           | | (If the BIOS option does not exists, |
|           | | please contact your BIOS vendor) |
|           | CPU frequency select | Max performance |
| Memory | Memory speed | Max performance |
|        | Memory channel mode | Independent |
|        | Node Interleaving | Disabled / NUMA |
|        | Channel Interleaving | Enabled |
|        | Thermal Mode | Performance |

#### Setting CPU Frequency Governor to Performance

     # cpupower frequency-set -g performance

#### Kernel Idle Loop Tuning (better latency)

In file `/etc/modprobe.d/mlnx.conf` set `options mlx4_core enable_sys_tune=1`.

#### Low Latency Request from Interfaces

     # ethtool -–set-priv-flags <interface> pm_qos_request_low_latency on (default off)

Where `<interface>` would be `ens3` and `ens3d1` for both snvme and tnvme.

Only works on drivers MLNX_OFED-2.2-x.x.x or higher.

#### Check Core Frequency is at maximum

Check the supported maximum:

      # cat /sys/devices/system/cpu/cpu*/cpufreq/cpuinfo_max_freq

Check the core frequencies:

      # cat /proc/cpuinfo | grep "cpu MHz"

Check if current CPU frequency is configured to maximum limit:

      # cat /sys/devices/system/cpu/cpu*/cpufreq/cpuinfo_cur_freq

#### RSS Hash Tuning

Good for smaller connections. Run:

     # ethtool --set-priv-flags <interface> mlx4_rss_xor_hash_function on

Where `<interface>` would be `ens3` and `ens3d1` for both snvme and tnvme.

#### ConnectX Optimized Steering

For MLNX_OFED-2.3-1.0.0 ConnectX-3/ConnectX-3 Pro adapter cards.

In file `/etc/modprobe.d/mlnx.conf` edit `options mlx4_core log_num_mgm_entry_size=-7` and restart the Mellanox drivers.

#### Single Thread Applications Environment Variables

For ConnextX-3 adapters:

    MLX4_SINGLE_THREADED=1

For Connect-IB adapters:

    MLX5_SINGLE_THREADED=1

#### Performance Tuning for iSER (important!)

1. Set SCSI scheduler to noop:

      # echo noop > /sys/block/<block_dev>/queue/scheduler

1. Disable the SCSI add_random:

      # echo 0 > /sys/block/<block_dev>/queue/add_random

1. Disable IO merges:

      # echo 2 > /sys/block/<block_dev>/queue/nomerges

1. Disable the hyper-threading in BIOS configuration.

1. Set the CPU scaling governor to performance.

1. Increase the number of persistent huge pages in the kernel's huge page pool for user_space targets such as TGT.

      # echo 3000 > /proc/sys/vm/nr_hugepages

      For kernel space targets such as LIO/SCST, decrease the number of persistent huge pages or set to zero.

      # echo 0 > /proc/sys/vm/nr_hugepages

1. Set the IRQ Affinity hints (see IRQ Affinity Hints (on page 14)).
