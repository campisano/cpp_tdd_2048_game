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

wget -P .custom_cache/sonar/pkg -c -nv --no-check-certificate https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
mkdir -p .custom_cache/sonar/wrapper
unzip -d .custom_cache/sonar/wrapper -q -n .custom_cache/sonar/pkg/build-wrapper-linux-x86.zip

make -e debug
make -e clean

.custom_cache/sonar/wrapper/build-wrapper-linux-x86/build-wrapper-linux-x86-64 --out-dir .bw-output make -e debug

./run.sh debug test

mkdir -p .gcov
cd .gcov
for F in `find ../build/debug/CMakeFiles -name '*.cpp.o'`;
do
  gcov -p "${F}" > /dev/null;
done
cd ..

SONARSCAN_VER="4.6.2.2472"
SONARSCAN_URL="https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-${SONARSCAN_VER}-linux.zip"
mkdir -p .custom_cache/sonar/pkg
wget -P .custom_cache/sonar/pkg -c -nv --no-check-certificate "${SONARSCAN_URL}"
mkdir -p .custom_cache/sonar/scanner
unzip -d .custom_cache/sonar/scanner -q -n ".custom_cache/sonar/pkg/sonar-scanner-cli-${SONARSCAN_VER}-linux.zip"

mkdir -p .custom_cache/sonar/home
export SONAR_USER_HOME=.custom_cache/sonar/home
.custom_cache/sonar/scanner/sonar-scanner-${SONARSCAN_VER}-linux/bin/sonar-scanner \
    -Dsonar.host.url=https://sonarcloud.io \
    -Dsonar.organization=${SONAR_ORGANIZATION} \
    -Dsonar.projectKey=${SONAR_PROJECT} \
    -Dsonar.scm.provider=git \
    -Dsonar.working.directory=.scannerwork \
    -Dsonar.sources=src \
    -Dsonar.sourceEncoding=UTF-8 \
    -Dsonar.coverage.exclusions=src/test/** \
    -Dsonar.cfamily.threads=1 \
    -Dsonar.cfamily.gcov.reportsPath=.gcov \
    -Dsonar.cfamily.build-wrapper-output=.bw-output \
    -Dsonar.cfamily.cache.enabled=false

rm -rf .bw-output .gcov .scannerwork
make distclean
