#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

mkdir -p .custom_cache/var/cache/apt
cp -aT .custom_cache/var/cache/apt /var/cache/apt
rm -f /etc/apt/apt.conf.d/docker*

export DEBIAN_FRONTEND=noninteractive
apt-get -qq -y update
apt-get -qq -y install --no-install-recommends apt-utils &> /dev/null
apt-get -qq -y install --no-install-recommends gcc g++ make cmake > /dev/null
apt-get -qq -y install --no-install-recommends wget unzip > /dev/null

mv -n /var/cache/apt/* .custom_cache/var/cache/apt/

mkdir -p .custom_cache/srv/sonar
wget -P .custom_cache/srv/cache -c -nv --no-check-certificate https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
unzip -d .custom_cache/srv/sonar -q -n .custom_cache/srv/cache/build-wrapper-linux-x86.zip
wget -P .custom_cache/srv/cache -c -nv --no-check-certificate https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-4.4.0.2170-linux.zip
unzip -d .custom_cache/srv/sonar -q -n .custom_cache/srv/cache/sonar-scanner-cli-4.4.0.2170-linux.zip

make -e debug
make -e clean

.custom_cache/srv/sonar/build-wrapper-linux-x86/build-wrapper-linux-x86-64 --out-dir bw-output make -e debug



./run.sh debug test

mkdir -p gcov
cd gcov
for F in `find ../build/debug/CMakeFiles -name '*.cpp.o'`;
do
  gcov -p "${F}" > /dev/null;
done
cd ..


export SONAR_TOKEN
export SONAR_USER_HOME=.custom_cache/srv/cache/sonar
.custom_cache/srv/sonar/sonar-scanner-4.4.0.2170-linux/bin/sonar-scanner \
    -Dsonar.host.url=https://sonarcloud.io \
    -Dsonar.organization=${SONAR_ORGANIZATION} \
    -Dsonar.projectKey=${SONAR_PROJECT} \
    -Dsonar.scm.provider=git \
    -Dsonar.sources=src \
    -Dsonar.sourceEncoding=UTF-8 \
    -Dsonar.working.directory=.scannerwork \
    -Dsonar.cfamily.threads=1 \
    -Dsonar.cfamily.gcov.reportsPath=gcov \
    -Dsonar.cfamily.build-wrapper-output=bw-output \
    -Dsonar.cfamily.cache.enabled=false

rm -rf bw-output gcov .scannerwork
make distclean
