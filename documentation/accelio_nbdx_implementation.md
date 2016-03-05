# Accelio/nbdX Implementation Document

## Installing Accelio (adpated from [Mellanox Documentation](https://community.mellanox.com/docs/DOC-2113))

### Both Client and Server Side

1. `yum install numactl numactl-devel libaio-devel libevent-devel libaio`
2. `wget http://freecode.com/urls/3aa21b8c106cab742bf1f20d60629e3f`
3. `cd fio-2.1.10`
4. `./configure`
5. `make`
6. `sudo make install`
7. `git clone https://github.com/accelio/accelio.git`
8. `cd accelio`
9. `git checkout -b nbdx_branch nbdx-v1.1`

### Client Side

10. `./autogen.sh`
11. `./configure --enable-stat-counters=no --enable-extra-checks=no --enable-kernel-module`
12. `make`
13. `make install`
14. `modprobe xio_rdma; modprobe xio_tcp`

### Server Side

10. `./autogen.sh`
11. `./configure --enable-stat-counters=no --enable-extra-checks=no`
12. `make`
13. `make install`

### Notes

#### If you need to reload the xio modules use the following command.

1. Unload modules: `modprobe -r xio_tcp; modprobe -r xio_rdma; modprobe -r xio_core`
2. Load modules: `modprobe xio_rdma; modprobe xio_tcp` 

#### If you need to reinstall make sure to first do the following:

1. `make distclean`

## Quick Accelio Tests

1. Create two IP interfaces for both server and client hosts.
2. Server side: `rping -sv -p 1234 -a <SERVER_IP>`
3. Client side: `rping -cv -p 1234 -a <SERVER_IP>`

## Testing nbdX

We followed the [Mellanox Documentation](https://community.mellanox.com/docs/DOC-1528) and did not run into any issues.
