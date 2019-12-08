#!/bin/bash

set -o errtrace -o errexit -o nounset -o pipefail

./run.sh release test
