#include <vector>
void group_layers(TString directory, TString file_name)
{
    TString output_directory = directory + "grouped/";
    gSystem->Exec("mkdir -p " + output_directory);

    TFile* input_file = TFile::Open(directory + file_name);
    if (!input_file || input_file->IsZombie()) {
            std::cerr << "Failed to open " << file_name << std::endl;
        }
    TTree* events_tree = (TTree*) input_file->Get("events");


    TTreeReader tree_reader(events_tree);
    TTreeReaderArray<float> insert_energy(tree_reader, "HcalEndcapPInsertRecHits.energy");
    TTreeReaderArray<float> insert_x(tree_reader, "HcalEndcapPInsertRecHits.position.x");
    TTreeReaderArray<float> insert_y(tree_reader, "HcalEndcapPInsertRecHits.position.y");
    TTreeReaderArray<float> insert_z(tree_reader, "HcalEndcapPInsertRecHits.position.z");
    TTreeReaderArray<float> insert_time(tree_reader, "HcalEndcapPInsertRecHits.time");
    TTreeReaderArray<int> insert_layer(tree_reader, "HcalEndcapPInsertRecHits.layer");
    TTreeReaderArray<float> ecal_insert_energy(tree_reader, "EcalEndcapPInsertRecHits.energy");
    TTreeReaderArray<float> ecal_insert_x(tree_reader, "EcalEndcapPInsertRecHits.position.x");
    TTreeReaderArray<float> ecal_insert_y(tree_reader, "EcalEndcapPInsertRecHits.position.y");
    TTreeReaderArray<float> ecal_insert_z(tree_reader, "EcalEndcapPInsertRecHits.position.z");
    TTreeReaderArray<float> ecal_insert_time(tree_reader, "EcalEndcapPInsertRecHits.time");
    TTreeReaderArray<int> ecal_insert_layer(tree_reader, "EcalEndcapPInsertRecHits.layer");
    TTreeReaderArray<float> ecal_energy(tree_reader, "EcalEndcapPRecHits.energy");
    TTreeReaderArray<float> ecal_x(tree_reader, "EcalEndcapPRecHits.position.x");
    TTreeReaderArray<float> ecal_y(tree_reader, "EcalEndcapPRecHits.position.y");
    TTreeReaderArray<float> ecal_z(tree_reader, "EcalEndcapPRecHits.position.z");
    TTreeReaderArray<float> ecal_time(tree_reader, "EcalEndcapPRecHits.time");
    TTreeReaderArray<int> ecal_layer(tree_reader, "EcalEndcapPRecHits.layer");
    TTreeReaderArray<float> lfhcal_energy(tree_reader, "LFHCALRecHits.energy");
    TTreeReaderArray<float> lfhcal_x(tree_reader, "LFHCALRecHits.position.x");
    TTreeReaderArray<float> lfhcal_y(tree_reader, "LFHCALRecHits.position.y");
    TTreeReaderArray<float> lfhcal_z(tree_reader, "LFHCALRecHits.position.z");
    TTreeReaderArray<float> lfhcal_time(tree_reader, "LFHCALRecHits.time");
    TTreeReaderArray<int> lfhcal_layer(tree_reader, "LFHCALRecHits.layer");

    TTreeReaderArray<int> mcparticles_pdg(tree_reader, "MCParticles.PDG");
    TTreeReaderArray<int> mcparticles_generatorStatus(tree_reader, "MCParticles.generatorStatus");
    TTreeReaderArray<int> mcparticles_simulatorStatus(tree_reader, "MCParticles.simulatorStatus");
    TTreeReaderArray<float> mcparticles_charge(tree_reader, "MCParticles.charge");
    TTreeReaderArray<float> mcparticles_time(tree_reader, "MCParticles.time");
    TTreeReaderArray<double> mcparticles_mass(tree_reader, "MCParticles.mass");
    TTreeReaderArray<double> mcparticles_vertex_x(tree_reader, "MCParticles.vertex.x");
    TTreeReaderArray<double> mcparticles_vertex_y(tree_reader, "MCParticles.vertex.y");
    TTreeReaderArray<double> mcparticles_vertex_z(tree_reader, "MCParticles.vertex.z");
    TTreeReaderArray<double> mcparticles_endpoint_x(tree_reader, "MCParticles.endpoint.x");
    TTreeReaderArray<double> mcparticles_endpoint_y(tree_reader, "MCParticles.endpoint.y");
    TTreeReaderArray<double> mcparticles_endpoint_z(tree_reader, "MCParticles.endpoint.z");
    TTreeReaderArray<double> mcparticles_momentum_x(tree_reader, "MCParticles.momentum.x");
    TTreeReaderArray<double> mcparticles_momentum_y(tree_reader, "MCParticles.momentum.y");
    TTreeReaderArray<double> mcparticles_momentum_z(tree_reader, "MCParticles.momentum.z");
    TTreeReaderArray<double> mcparticles_momentumAtEndpoint_x(tree_reader, "MCParticles.momentumAtEndpoint.x");
    TTreeReaderArray<double> mcparticles_momentumAtEndpoint_y(tree_reader, "MCParticles.momentumAtEndpoint.y");
    TTreeReaderArray<double> mcparticles_momentumAtEndpoint_z(tree_reader, "MCParticles.momentumAtEndpoint.z");
    TTreeReaderArray<float> mcparticles_spin_x(tree_reader, "MCParticles.spin.x");
    TTreeReaderArray<float> mcparticles_spin_y(tree_reader, "MCParticles.spin.y");
    TTreeReaderArray<float> mcparticles_spin_z(tree_reader, "MCParticles.spin.z");
    TTreeReaderArray<int> mcparticles_colorflow_a(tree_reader, "MCParticles.colorFlow.a");
    TTreeReaderArray<int> mcparticles_colorflow_b(tree_reader, "MCParticles.colorFlow.b");
    TTreeReaderArray<UInt_t> mcparticles_parents_begin(tree_reader, "MCParticles.parents_begin");
    TTreeReaderArray<UInt_t> mcparticles_parents_end(tree_reader, "MCParticles.parents_end");
    TTreeReaderArray<UInt_t> mcparticles_daughters_begin(tree_reader, "MCParticles.daughters_begin");
    TTreeReaderArray<UInt_t> mcparticles_daughters_end(tree_reader, "MCParticles.daughters_end");


    // To store: map of (ix, iy, layer_group_index) → total energy
    std::map<std::tuple<int, int, int>, float> grouped_energy;
    
    // There are 60 layers in the insert, starting with layer 1.
    const int num_layer_sections = 7;
    std::vector<std::tuple<int, int>> layer_groups = {{1,12}, {13,20}, {21,28}, {29,36}, {37,44}, {45,52}, {53,60}};
    // The z positions to be assigned for each layer group. 
    // These are the median values of the z positions for the layers in each group
    std::vector<float> group_z_positions = {3722.6, 3927.6, 4091.6, 4255.6, 4419.6, 4583.6, 4747.6};
    
    std::vector<int> cell_x_positions = {-400, -350, -300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200};
    std::vector<int> cell_y_positions = {-300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200, 250, 300};
    std::map<std::pair<int, int>, int> cell_indices_xy = {};
    std::vector<std::pair<int, int>> index_to_xy;
    int index = 0;
    for (auto& x_pos: cell_x_positions)
    {
        for(auto& y_pos:cell_y_positions)
        {   
            std::pair<int, int> xy = {x_pos, y_pos};
            cell_indices_xy[xy] = index;
            index_to_xy.push_back(xy);
            index++;
        }
    }
    const int num_xy_pairs = index;

    

    std::vector<float> combined_x;
    std::vector<float> combined_y;
    std::vector<float> combined_z;
    std::vector<float> combined_E;
    std::vector<float> combined_time;
    std::vector<int> combined_layer;
    TFile* output_file = TFile::Open(output_directory + file_name, "RECREATE");
    TTree* outTree = new TTree("events", "events");
    outTree->Branch("HcalEndcapPInsertRecHits.energy", &combined_E);
    outTree->Branch("HcalEndcapPInsertRecHits.position.x", &combined_x);
    outTree->Branch("HcalEndcapPInsertRecHits.position.y", &combined_y);
    outTree->Branch("HcalEndcapPInsertRecHits.position.z", &combined_z);
    outTree->Branch("HcalEndcapPInsertRecHits.time", &combined_time);
    outTree->Branch("HcalEndcapPInsertRecHits.layer", &combined_layer);

    std::vector<float> out_ecal_insert_x;
    std::vector<float> out_ecal_insert_y;
    std::vector<float> out_ecal_insert_z;
    std::vector<float> out_ecal_insert_E;
    std::vector<float> out_ecal_insert_time;
    std::vector<int> out_ecal_insert_layer;
    outTree->Branch("EcalEndcapPInsertRecHits.energy", &out_ecal_insert_E);
    outTree->Branch("EcalEndcapPInsertRecHits.position.x", &out_ecal_insert_x);
    outTree->Branch("EcalEndcapPInsertRecHits.position.y", &out_ecal_insert_y);
    outTree->Branch("EcalEndcapPInsertRecHits.position.z", &out_ecal_insert_z);
    outTree->Branch("EcalEndcapPInsertRecHits.time", &out_ecal_insert_time);
    outTree->Branch("EcalEndcapPInsertRecHits.layer", &out_ecal_insert_layer);

    std::vector<float> out_ecal_x;
    std::vector<float> out_ecal_y;
    std::vector<float> out_ecal_z;
    std::vector<float> out_ecal_E;
    std::vector<float> out_ecal_time;
    std::vector<int> out_ecal_layer;
    outTree->Branch("EcalEndcapPRecHits.energy", &out_ecal_E);
    outTree->Branch("EcalEndcapPRecHits.position.x", &out_ecal_x);
    outTree->Branch("EcalEndcapPRecHits.position.y", &out_ecal_y);
    outTree->Branch("EcalEndcapPRecHits.position.z", &out_ecal_z);
    outTree->Branch("EcalEndcapPRecHits.time", &out_ecal_time);
    outTree->Branch("EcalEndcapPRecHits.layer", &out_ecal_layer);

    std::vector<float> out_lfhcal_x;
    std::vector<float> out_lfhcal_y;
    std::vector<float> out_lfhcal_z;
    std::vector<float> out_lfhcal_E;
    std::vector<float> out_lfhcal_time;
    std::vector<int> out_lfhcal_layer;
    outTree->Branch("LFHCALRecHits.energy", &out_lfhcal_E);
    outTree->Branch("LFHCALRecHits.position.x", &out_lfhcal_x);
    outTree->Branch("LFHCALRecHits.position.y", &out_lfhcal_y);
    outTree->Branch("LFHCALRecHits.position.z", &out_lfhcal_z);
    outTree->Branch("LFHCALRecHits.time", &out_lfhcal_time);
    outTree->Branch("LFHCALRecHits.layer", &out_lfhcal_layer);

    std::vector<int> out_mc_pdg;
    std::vector<int> out_mc_generatorStatus;
    std::vector<int> out_mc_simulatorStatus;
    std::vector<float> out_mc_charge;
    std::vector<float> out_mc_time;
    std::vector<double> out_mc_mass;

    std::vector<double> out_mc_vertex_x;
    std::vector<double> out_mc_vertex_y;
    std::vector<double> out_mc_vertex_z;

    std::vector<double> out_mc_endpoint_x;
    std::vector<double> out_mc_endpoint_y;
    std::vector<double> out_mc_endpoint_z;

    std::vector<double> out_mc_momentum_x;
    std::vector<double> out_mc_momentum_y;
    std::vector<double> out_mc_momentum_z;

    std::vector<double> out_mc_momentumAtEndpoint_x;
    std::vector<double> out_mc_momentumAtEndpoint_y;
    std::vector<double> out_mc_momentumAtEndpoint_z;

    std::vector<float> out_mc_spin_x;
    std::vector<float> out_mc_spin_y;
    std::vector<float> out_mc_spin_z;

    std::vector<int> out_mc_colorflow_a;
    std::vector<int> out_mc_colorflow_b;

    std::vector<UInt_t> out_mc_parents_begin;
    std::vector<UInt_t> out_mc_parents_end;
    std::vector<UInt_t> out_mc_daughters_begin;
    std::vector<UInt_t> out_mc_daughters_end;

    outTree->Branch("MCParticles.PDG", &out_mc_pdg);
    outTree->Branch("MCParticles.generatorStatus", &out_mc_generatorStatus);
    outTree->Branch("MCParticles.simulatorStatus", &out_mc_simulatorStatus);
    outTree->Branch("MCParticles.charge", &out_mc_charge);
    outTree->Branch("MCParticles.time", &out_mc_time);
    outTree->Branch("MCParticles.mass", &out_mc_mass);

    outTree->Branch("MCParticles.vertex.x", &out_mc_vertex_x);
    outTree->Branch("MCParticles.vertex.y", &out_mc_vertex_y);
    outTree->Branch("MCParticles.vertex.z", &out_mc_vertex_z);

    outTree->Branch("MCParticles.endpoint.x", &out_mc_endpoint_x);
    outTree->Branch("MCParticles.endpoint.y", &out_mc_endpoint_y);
    outTree->Branch("MCParticles.endpoint.z", &out_mc_endpoint_z);

    outTree->Branch("MCParticles.momentum.x", &out_mc_momentum_x);
    outTree->Branch("MCParticles.momentum.y", &out_mc_momentum_y);
    outTree->Branch("MCParticles.momentum.z", &out_mc_momentum_z);

    outTree->Branch("MCParticles.momentumAtEndpoint.x", &out_mc_momentumAtEndpoint_x);
    outTree->Branch("MCParticles.momentumAtEndpoint.y", &out_mc_momentumAtEndpoint_y);
    outTree->Branch("MCParticles.momentumAtEndpoint.z", &out_mc_momentumAtEndpoint_z);

    outTree->Branch("MCParticles.spin.x", &out_mc_spin_x);
    outTree->Branch("MCParticles.spin.y", &out_mc_spin_y);
    outTree->Branch("MCParticles.spin.z", &out_mc_spin_z);

    outTree->Branch("MCParticles.colorFlow.a", &out_mc_colorflow_a);
    outTree->Branch("MCParticles.colorFlow.b", &out_mc_colorflow_b);

    outTree->Branch("MCParticles.parents_begin", &out_mc_parents_begin);
    outTree->Branch("MCParticles.parents_end", &out_mc_parents_end);
    outTree->Branch("MCParticles.daughters_begin", &out_mc_daughters_begin);
    outTree->Branch("MCParticles.daughters_end", &out_mc_daughters_end);
    
    int counter=0;
    while (tree_reader.Next())
    {   
        // counter += 1;
        // if (counter > 1000) break;
        // input: xy index, layer index. output energy, 
        std::map<std::pair<int, int>, float> xyz_to_energy_map = {};
        std::map<std::pair<int, int>, float> xyz_to_time_map = {};
        
        for (unsigned int i = 0; i < lfhcal_x.GetSize(); i++)
        {  
            out_lfhcal_E.push_back(lfhcal_energy[i]);
            out_lfhcal_x.push_back(lfhcal_x[i]);
            out_lfhcal_y.push_back(lfhcal_y[i]);
            out_lfhcal_z.push_back(lfhcal_z[i]);
            out_lfhcal_time.push_back(lfhcal_time[i]);
            out_lfhcal_layer.push_back(lfhcal_layer[i]);
        }
        for (unsigned int i = 0; i < ecal_insert_x.GetSize(); i++)
        {  
            out_ecal_insert_E.push_back(ecal_insert_energy[i]);
            out_ecal_insert_x.push_back(ecal_insert_x[i]);
            out_ecal_insert_y.push_back(ecal_insert_y[i]);
            out_ecal_insert_z.push_back(ecal_insert_z[i]);
            out_ecal_insert_time.push_back(ecal_insert_time[i]);
            out_ecal_insert_layer.push_back(ecal_insert_layer[i]);
        }
        for (unsigned int i = 0; i < ecal_x.GetSize(); i++)
        {  
            out_ecal_E.push_back(ecal_energy[i]);
            out_ecal_x.push_back(ecal_x[i]);
            out_ecal_y.push_back(ecal_y[i]);
            out_ecal_z.push_back(ecal_z[i]);
            out_ecal_time.push_back(ecal_time[i]);
            out_ecal_layer.push_back(ecal_layer[i]);
        }
        for (unsigned int i = 0; i < mcparticles_pdg.GetSize(); i++)
        {
            out_mc_pdg.push_back(mcparticles_pdg[i]);
            out_mc_generatorStatus.push_back(mcparticles_generatorStatus[i]);
            out_mc_simulatorStatus.push_back(mcparticles_simulatorStatus[i]);
            out_mc_charge.push_back(mcparticles_charge[i]);
            out_mc_time.push_back(mcparticles_time[i]);
            out_mc_mass.push_back(mcparticles_mass[i]);

            out_mc_vertex_x.push_back(mcparticles_vertex_x[i]);
            out_mc_vertex_y.push_back(mcparticles_vertex_y[i]);
            out_mc_vertex_z.push_back(mcparticles_vertex_z[i]);

            out_mc_endpoint_x.push_back(mcparticles_endpoint_x[i]);
            out_mc_endpoint_y.push_back(mcparticles_endpoint_y[i]);
            out_mc_endpoint_z.push_back(mcparticles_endpoint_z[i]);

            out_mc_momentum_x.push_back(mcparticles_momentum_x[i]);
            out_mc_momentum_y.push_back(mcparticles_momentum_y[i]);
            out_mc_momentum_z.push_back(mcparticles_momentum_z[i]);

            out_mc_momentumAtEndpoint_x.push_back(mcparticles_momentumAtEndpoint_x[i]);
            out_mc_momentumAtEndpoint_y.push_back(mcparticles_momentumAtEndpoint_y[i]);
            out_mc_momentumAtEndpoint_z.push_back(mcparticles_momentumAtEndpoint_z[i]);

            out_mc_spin_x.push_back(mcparticles_spin_x[i]);
            out_mc_spin_y.push_back(mcparticles_spin_y[i]);
            out_mc_spin_z.push_back(mcparticles_spin_z[i]);

            out_mc_colorflow_a.push_back(mcparticles_colorflow_a[i]);
            out_mc_colorflow_b.push_back(mcparticles_colorflow_b[i]);

            out_mc_parents_begin.push_back(mcparticles_parents_begin[i]);
            out_mc_parents_end.push_back(mcparticles_parents_end[i]);
            out_mc_daughters_begin.push_back(mcparticles_daughters_begin[i]);
            out_mc_daughters_end.push_back(mcparticles_daughters_end[i]);
        }
        for (unsigned int i = 0; i < insert_energy.GetSize(); i++)
        {   
            int layer_number = insert_layer[i];
            int layer_index = -1;

            if (!cell_indices_xy.count({insert_x[i], insert_y[i]}))
            {
                std::cout<<"XY key not found for "<<insert_x[i]<<" "<<insert_y[i]<<std::endl;
            }
            int xy_index = cell_indices_xy[{insert_x[i], insert_y[i]}];
            
            for (int i_layer = 0; i_layer<num_layer_sections; i_layer++)
            {
                int min_layer = std::get<0>(layer_groups[i_layer]);
                int max_layer = std::get<1>(layer_groups[i_layer]);
                if (layer_number >= min_layer && layer_number <= max_layer)
                {
                    layer_index = i_layer;
                    break;
                }
            }
            std::pair<int,int> xyz_index = {xy_index, layer_index};
            xyz_to_energy_map[xyz_index] += insert_energy[i];
            if (!xyz_to_energy_map.count({xy_index, layer_index}))
            {
                std::cout<<"XYZ energy key not found for "<<insert_x[i]<<" "<<insert_y[i]<<" "<<layer_index<<std::endl;
            }
            if (xyz_to_time_map[xyz_index] == 0) xyz_to_time_map[xyz_index] = insert_time[i];
            else if (insert_time[i] < xyz_to_time_map[xyz_index]) xyz_to_time_map[xyz_index] = insert_time[i];
            if (!xyz_to_time_map.count({xy_index, layer_index}))
            {
                std::cout<<"XYZ time key not found for "<<insert_x[i]<<" "<<insert_y[i]<<" "<<layer_index<<std::endl;
            }
        }
        for (int i_layer = 0; i_layer < num_layer_sections; i_layer++)
        {
            for (int i_xy = 0; i_xy < num_xy_pairs; i_xy++)
            {
                std::pair<int, int> xyz_index = {i_xy, i_layer};
                float cell_energy = xyz_to_energy_map[xyz_index];
                if (cell_energy == 0) continue;
                float cell_time = xyz_to_time_map[xyz_index];
                std::pair<int, int> xy = index_to_xy[i_xy];
                float x = std::get<0>(xy);
                float y = std::get<1>(xy);
                float z = group_z_positions[i_layer];
                combined_x.push_back(x);
                combined_y.push_back(y);
                combined_z.push_back(z);
                combined_E.push_back(cell_energy);
                combined_time.push_back(cell_time);
                combined_layer.push_back(i_layer+1);
            }
        }
        
        outTree->Fill();
        combined_E.clear();
        combined_x.clear();
        combined_y.clear();
        combined_z.clear();
        combined_time.clear();
        combined_layer.clear();
        out_lfhcal_x.clear();
        out_lfhcal_y.clear();
        out_lfhcal_z.clear();
        out_lfhcal_E.clear();
        out_lfhcal_time.clear();
        out_lfhcal_layer.clear();
        out_ecal_insert_x.clear();
        out_ecal_insert_y.clear();
        out_ecal_insert_z.clear();
        out_ecal_insert_E.clear();
        out_ecal_insert_time.clear();
        out_ecal_insert_layer.clear();
        out_ecal_x.clear();
        out_ecal_y.clear();
        out_ecal_z.clear();
        out_ecal_E.clear();
        out_ecal_time.clear();
        out_ecal_layer.clear();
        out_mc_pdg.clear();
        out_mc_generatorStatus.clear();
        out_mc_simulatorStatus.clear();
        out_mc_charge.clear();
        out_mc_time.clear();
        out_mc_mass.clear();

        out_mc_vertex_x.clear();
        out_mc_vertex_y.clear();
        out_mc_vertex_z.clear();

        out_mc_endpoint_x.clear();
        out_mc_endpoint_y.clear();
        out_mc_endpoint_z.clear();

        out_mc_momentum_x.clear();
        out_mc_momentum_y.clear();
        out_mc_momentum_z.clear();

        out_mc_momentumAtEndpoint_x.clear();
        out_mc_momentumAtEndpoint_y.clear();
        out_mc_momentumAtEndpoint_z.clear();

        out_mc_spin_x.clear();
        out_mc_spin_y.clear();
        out_mc_spin_z.clear();

        out_mc_colorflow_a.clear();
        out_mc_colorflow_b.clear();

        out_mc_parents_begin.clear();
        out_mc_parents_end.clear();
        out_mc_daughters_begin.clear();
        out_mc_daughters_end.clear();
    }
        
    outTree->Write();


    output_file->Close();
    input_file->Close();
}