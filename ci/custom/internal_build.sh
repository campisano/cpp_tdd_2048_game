#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

mkdir -p .custom_cache/var/cache/apt
cp -aT .custom_cache/var/cache/apt /var/cache/apt
rm -f /etc/apt/apt.conf.d/docker*

export DEBIAN_FRONTEND=noninteractive
apt-get -qq -y update
apt-get -qq -y install --no-install-recommends apt-utils &> /dev/null
apt-get -qq -y install --no-install-recommends gcc g++ make cmake > /dev/null

mv -n /var/cache/apt/* .custom_cache/var/cache/apt/

make -e release
