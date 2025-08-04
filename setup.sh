#!/bin/sh
export DETECTOR=epic_forward_detectors_with_inserts
export DETECTOR_PATH=/opt/software/linux-debian13-x86_64_v2/gcc-14.2.0/epic-25.07.0-35b5fmffr7volijz45o4gyavvlmm2n7l/share/epic
export DETECTOR_CONFIG=${1:-epic_forward_detectors_with_inserts}
export DETECTOR_VERSION=v0.0.0-unknown

## Warn is not the right name (this script is sourced, hence $1)
if [[ "$(basename ${BASH_SOURCE[0]})" != "thisepic.sh" ]]; then
        echo "Warning: This script will cease to exist at '$(realpath --no-symlinks ${BASH_SOURCE[0]})'."
        echo "         Please use the version at '$(realpath --no-symlinks $(dirname ${BASH_SOURCE[0]})/bin/thisepic.sh)'."
fi

## Export detector libraries
if [[ "$(uname -s)" = "Darwin" ]] || [[ "$OSTYPE" == "darwin"* ]]; then
        export DYLD_LIBRARY_PATH="/opt/software/linux-debian13-x86_64_v2/gcc-14.2.0/epic-25.07.0-35b5fmffr7volijz45o4gyavvlmm2n7l/lib${DYLD_LIBRARY_PATH:+:$DYLD_LIBRARY_PATH}"
else
        export LD_LIBRARY_PATH="/opt/software/linux-debian13-x86_64_v2/gcc-14.2.0/epic-25.07.0-35b5fmffr7volijz45o4gyavvlmm2n7l/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
fi

source ./EICrecon-1.26.1/install/bin/eicrecon-this.sh