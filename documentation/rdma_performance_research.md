# RDMA Performance Research Documentation

## Resources

[Performance Tuning Guide for Mellanox Network Adapters](http://www.mellanox.com/related-docs/prod_software/Performance_Tuning_Guide_for_Mellanox_Network_Adapters.pdf)

[CPU Frequency Governor Scaling](https://wiki.archlinux.org/index.php/CPU_frequency_scaling)

## Commands used

#### Setting CPU Frequency Governor to Performance

     # cpupower frequency-set -g performance

#### Kernel Idle Loop Tuning (better latency)

In file `/etc/modprobe.d/mlnx.conf` set `options mlx4_core enable_sys_tune=1`.

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
