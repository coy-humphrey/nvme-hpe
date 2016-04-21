# Authors: Coy Humphrey, Jayden Navarro
# Project: HPE UCSC Senior Design 2016
# Date: 4-7-2016

import ib_send_bw, fio
from framework import *

# Setup CSV and error directory
setDirectory()

# Run ib_send_bw
ib_send_bw.run_s()

# Run local fio tests
setupLocalRamDisk()

fio.run()

teardownLocalRamDisk()

# Run remote fio tests
setupRemoteRamDisk()

fio.run()

teardownRemoteRamDisk()
