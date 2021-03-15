// ini parser
#include <boost/optional/optional.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "Spike/Neuron/NeuronFactory.h"
#include "Spike/Signal/SignalFactory.h"
#include "Spike/Simulation/FiringRateSimulation.h"

namespace Spike {

FiringRateSimulation::FiringRateSimulation(const std::string &input_file)
    : time_frame(input_file),
      spike_train(time_frame),
      firing_rate(time_frame.get_size(), 0) {
    // create neuron
    neuron = NeuronFactory::create(input_file);

    // read parameter
    pt::ptree root;
    pt::read_ini(input_file, root);
    N_neurons = root.get<size_t>("Simulation.N_neurons");

    // check if signal is defined
    boost::optional<pt::ptree &> signal_given =
        root.get_child_optional("Signal");
    if (!signal_given) {
        signal = nullptr;
    } else {
        signal = SignalFactory::create(input_file, time_frame);
    }
}

void FiringRateSimulation::calculate(int trials) {
    // get spike train, this will add spike over and over again
    if (signal == nullptr) {
        for (int i = 0; i < trials; i++) {
            neuron->get_spikes(spike_train);
        }
    } else {
        for (int i = 0; i < trials; i++) {
            neuron->get_spikes(*signal, spike_train);
        }
    }

    const std::vector<double> spike_train_values = spike_train.get_values();

    for (size_t i = 0; i < firing_rate.size(); i++) {
        firing_rate[i] = 1.0 / N_neurons * spike_train_values[i];
    }
}

void FiringRateSimulation::add_to_firing_rate(
    const std::vector<double> &tmp_firing_rate) {
    for (size_t i = 0; i < tmp_firing_rate.size(); i++) {
        firing_rate[i] += tmp_firing_rate[i];
    }
}

RasterPlot::RasterPlot(const std::string &input_file)
    : FiringRateSimulation(input_file), spike_trains(N_neurons) {
        // fix the number of neurons to 100, since this is enough for the raster plot
        N_neurons = 100;
    }

void RasterPlot::calculate() {
    // for every trial...
    for (size_t j = 0; j < N_neurons; j++) {
        // get spike train
        if (signal == nullptr) {
            neuron->get_spikes(spike_train);
        } else {
            neuron->get_spikes(*signal, spike_train);
        }

        const std::vector<double> spike_train_values = spike_train.get_values();

        // add to spike train array
        for (size_t i = 0; i < spike_train_values.size(); i++) {
            if (spike_train_values[i] != 0) {
                spike_trains[j].push_back(time_frame.get_time(i));
            } else {
                spike_trains[j].push_back(0);
            }
        }

        // clear the spike train
        spike_train.clear();
    }
}

}  // namespace Spike