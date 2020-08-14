#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

TOKEN="$1"

export DEBIAN_FRONTEND=noninteractive

rm -f /etc/apt/apt.conf.d/docker*
apt-get -qq -y update
apt-get -qq -y install --no-install-recommends apt-utils > /dev/null
apt-get -qq -y install --no-install-recommends gcc g++ make cmake > /dev/null
apt-get -qq -y install --no-install-recommends wget unzip > /dev/null

mkdir -p /srv/sonar
wget -P /srv/cache -c -nv --no-check-certificate https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
unzip -d /srv/sonar -q -n /srv/cache/build-wrapper-linux-x86.zip
wget -P /srv/cache -c -nv --no-check-certificate https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-4.4.0.2170-linux.zip
unzip -d /srv/sonar -q -n /srv/cache/sonar-scanner-cli-4.4.0.2170-linux.zip

make -e debug
make -e clean

/srv/sonar/build-wrapper-linux-x86/build-wrapper-linux-x86-64 --out-dir bw-output make -e debug



./run.sh debug test

mkdir -p gcov
cd gcov
for F in `find ../build/debug/CMakeFiles -name '*.cpp.o'`;
do
  gcov -p "${F}" > /dev/null;
done
cd ..



export SONAR_TOKEN=${TOKEN}
export SONAR_USER_HOME=/srv/cache/sonar
/srv/sonar/sonar-scanner-4.4.0.2170-linux/bin/sonar-scanner \
    -Dsonar.host.url=https://sonarcloud.io \
    -Dsonar.organization=campisano \
    -Dsonar.projectKey=campisano_cpp_tdd_2048_game \
    -Dsonar.sources=src \
    -Dsonar.sourceEncoding=UTF-8 \
    -Dsonar.cfamily.threads=1 \
    -Dsonar.cfamily.gcov.reportsPath=gcov \
    -Dsonar.cfamily.build-wrapper-output=bw-output \
    -Dsonar.cfamily.cache.enabled=false

rm -rf gcov bw-output .scannerwork
make distclean
