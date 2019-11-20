#!/bin/bash

apt-get -q update
apt-get -q -y install gcc g++ make cmake
make -e release
