#!/bin/bash
#SBATCH --job-name=neutron_log10continuous_lowgranularity_oldenergies_oldeta
#SBATCH --output=/volatile/clas12/rmilton/insert_data/neutron_log10continuous_lowgranularity_oldenergies_oldeta/log/reco_%A_%a.out
#SBATCH --error=/volatile/clas12/rmilton/insert_data/neutron_log10continuous_lowgranularity_oldenergies_oldeta/log/reco_%A_%a.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=4000
#SBATCH --array=0-199
#SBATCH -t 02:00:00

# ----------- Setup Variables -----------
job_name="neutron_log10continuous_lowgranularity_oldenergies_oldeta"
EIC_DIR="/w/hallb-scshelf2102/clas12/rmilton/insert_GNN/"
output_dir="/volatile/clas12/rmilton/insert_data/${job_name}/"
reco_dir="${output_dir}reco/"
hepmc_dir="${output_dir}hepmc/"
sim_dir="${output_dir}sim/"
log_dir="${output_dir}log/"
group_dir="${output_dir}grouped/"
setup_script="${EIC_DIR}/setup_lowgranularity.sh"
generation_script="${EIC_DIR}/run_sim_epic.sh"

mkdir -p "$reco_dir" "$hepmc_dir" "$sim_dir" "$log_dir"

particle="neutron"
energy_min=1
energy_max=150
num_events=5000
theta_min=2.3
theta_max=4.25
phi_min=0.
phi_max=360.
distribution="log10continuous"
group_layers=true
if [ "$group_layers" = true ] ; then
    mkdir -p "$group_dir"
fi

job_id=${SLURM_ARRAY_TASK_ID}
info_string="${particle}_${distribution}_${energy_min}GeV-${energy_max}GeV_theta_${theta_min}deg-${theta_max}deg_${job_id}"
base_name="gen_${info_string}"
genscriptname="${EIC_DIR}/${base_name}.sh"

# ----------- Create the Generation Script -----------
cd "$EIC_DIR"

echo "#!/bin/bash" > "$genscriptname"
echo "source $setup_script" >> "$genscriptname"
if [ "$group_layers" = true ] ; then
    echo "source $generation_script --particle ${particle} -n ${num_events} -pmin ${energy_min} -pmax ${energy_max} --theta_min ${theta_min} --theta_max ${theta_max} --phi_min ${phi_min} --phi_max ${phi_max} --distribution ${distribution} --jid ${job_id} --group" >> "$genscriptname"
else
    echo "source $generation_script --particle ${particle} -n ${num_events} -pmin ${energy_min} -pmax ${energy_max} --theta_min ${theta_min} --theta_max ${theta_max} --phi_min ${phi_min} --phi_max ${phi_max} --distribution ${distribution} --jid ${job_id}" >> "$genscriptname"
fi

echo "info_string=${info_string}" >> "$genscriptname"
echo 'hepmcfile="gen_${info_string}.hepmc"' >> "$genscriptname"
echo 'simfile="sim_${info_string}.edm4hep.root"' >> "$genscriptname"
echo 'recofile="reco_${info_string}.edm4hep.root"' >> "$genscriptname"
echo "mv \"\$recofile\" \"${reco_dir}\"" >> "$genscriptname"
echo "mv \"\$hepmcfile\" \"${hepmc_dir}\"" >> "$genscriptname"
echo "mv \"\$simfile\" \"${sim_dir}\"" >> "$genscriptname"
if [ "$group_layers" = true ] ; then
    echo "mv ./grouped/\${recofile} \"${group_dir}\"" >> "$genscriptname"
fi
chmod +x "$genscriptname"

# ----------- Run the Generation Script in eic-shell -----------
${EIC_DIR}/eic-shell -- "$genscriptname"
