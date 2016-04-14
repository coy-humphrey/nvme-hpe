# Authors: Coy Humphrey, Jayden Navarro
# Project: HPE UCSC Senior Design 2016
# Date: 4-7-2016

import ib_send_bw, fio
from framework import *

setDirectory()

ib_send_bw.run_s()

setupLocalRamDisk()

fio.run_s()

teardownLocalRamDisk()
