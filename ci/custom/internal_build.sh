#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

apt-get -qq -y update
apt-get -qq -y install gcc g++ make cmake > /dev/null
apt-get -qq -y clean

make -e release
