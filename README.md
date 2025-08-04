# insert_GNN
This repository is for the generation of data for insert GNN studies, the scripts for training the GNN, and the analysis scripts for generating plots.

## Dependencies for running simulations
This repository uses the following to run simulations:
- [eic-shell](https://github.com/eic/eic-shell)
- [EICrecon v1.26.1](https://github.com/eic/EICrecon/releases/tag/v1.26.1)

To set this up, download eic-shell following the instructions on the eic-shell page. Then set up EICrecon with the following:
```
wget https://github.com/eic/EICrecon/archive/refs/tags/v1.26.1.tar.gz
tar -xzvf v1.26.1.tar.gz
```
Then do the following to install EICrecon and get the environment set up:
```
cd EICrecon-1.26.1
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
cmake --build build -j12
cmake --install build
cd ..
source setup.sh
```
Now our environment variables are set and the simulation + reconstruction software is able to run. Note that `source setup.sh` should be used everytime you re-enter eic-shell.

## Configuration for simulation
In this work, we are interested mainly in the insert in forward endcap. Because of this, we use the geometry in the `epic_forward_detectors_with_inserts` configuration. When running this simulation, we will only store the following branches: `EcalEndcapPRecHits`, `EcalEndcapPInsertRecHits`, `LFHCALRecHits`, `HcalEndcapPInsertRecHits`, `MCParticles`. The detectors are all in the forward endcap. An image of the simulation configuration is shown below.

For EICrecon, we are using version 1.26.1 since this is the most recent version that contains reconstruction for the EcalEndcapPInsert. This detector is set to be removed from the simulation, however at the time of this repository's creation (early August 2025), the detector is in the simulation but the output is not stored in EICrecon. Since this detector is directly in front of the insert (our main detector of interest), we revert EICrecon versions to a version with the EcalEndcapPInsert read out.

