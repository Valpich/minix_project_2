#!/bin/sh

cd /usr/src/servers/pm
make
cd /usr/src/releasetools
make install
sync
reboot