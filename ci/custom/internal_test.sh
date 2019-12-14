#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

./run.sh release test
