#!/bin/bash

set -o errtrace -o errexit -o nounset -o pipefail

apt-get -q update
apt-get -q -y install gcc g++ make cmake
apt-get clean
make -e release
