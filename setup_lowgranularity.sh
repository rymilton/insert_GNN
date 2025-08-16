#!/bin/sh
export DETECTOR=epic_forward_detectors_with_inserts_lowgranularity
export DETECTOR_PATH=/w/hallb-scshelf2102/clas12/rmilton/insert_GNN/epic-25.07.0/install/share/epic
export DETECTOR_CONFIG=${1:-${DETECTOR}}
export DETECTOR_VERSION=v0.0.0-unknown

## Export detector libraries
if [[ "$(uname -s)" = "Darwin" ]] || [[ "$OSTYPE" == "darwin"* ]]; then
        export DYLD_LIBRARY_PATH="/w/hallb-scshelf2102/clas12/rmilton/insert_GNN/epic-25.07.0/install/lib${DYLD_LIBRARY_PATH:+:$DYLD_LIBRARY_PATH}"
else
        export LD_LIBRARY_PATH="/w/hallb-scshelf2102/clas12/rmilton/insert_GNN/epic-25.07.0/install/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
fi

source ./EICrecon-1.26.1/install/bin/eicrecon-this.sh