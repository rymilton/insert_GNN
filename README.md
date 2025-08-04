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
