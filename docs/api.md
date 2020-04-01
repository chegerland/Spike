# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`CosineSignal`](#classCosineSignal) | Implements a cosine get_value, i.e. alpha*cos(2*pi*f*t)
`class `[`FiringRate`](#classFiringRate) | 
`class `[`FiringRateBox`](#classFiringRateBox) | 
`class `[`FiringRateExp`](#classFiringRateExp) | 
`class `[`FiringRateFactory`](#classFiringRateFactory) | 
`class `[`FiringRateSimulation`](#classFiringRateSimulation) | 
`class `[`IF`](#classIF) | An abstract base class for integrate-and-fire neurons.
`class `[`IFAC`](#classIFAC) | An abstract base class for integrate-and-fire neurons with an adaptation current.
`class `[`LIF`](#classLIF) | Implements a leaky integrate-and-fire ([LIF](#classLIF)) neuron.
`class `[`LIFAC`](#classLIFAC) | Implements a leaky integrate-and-fire ([LIFAC](#classLIFAC)) neuron.
`class `[`Neuron`](#classNeuron) | 
`class `[`NeuronFactory`](#classNeuronFactory) | 
`class `[`Options`](#classOptions) | Implements a class that handles command line options.
`class `[`PIF`](#classPIF) | Implement a perfect integrate-and-fire ([PIF](#classPIF)) neuron.
`class `[`PIFAC`](#classPIFAC) | Implement a perfect integrate-and-fire ([PIFAC](#classPIFAC)) neuron.
`class `[`Signal`](#classSignal) | An abstract base class for signals.
`class `[`SignalFactory`](#classSignalFactory) | Implements the factory design pattern for [Signal](#classSignal).
`class `[`Simulation`](#classSimulation) | 
`class `[`SpikeTrain`](#classSpikeTrain) | 
`class `[`StepSignal`](#classStepSignal) | Implement a step get_value, i.e. alpha*Theta(t - t_0)
`class `[`TimeFrame`](#classTimeFrame) | A time frame class.
`class `[`TwoCosineSignal`](#classTwoCosineSignal) | Implements a get_value consisting of two cosine, i.e. alpha*cos(2*pi*f1*t)
`class `[`WhiteNoiseSignal`](#classWhiteNoiseSignal) | Implements a band limited white gaussian noise get_value.

# class `CosineSignal` 

```
class CosineSignal
  : public Signal
```  

Implements a cosine get_value, i.e. alpha*cos(2*pi*f*t)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CosineSignal`](#classCosineSignal_1ab4df140ccdbbf7eb1138647eb53a5100)`(double alpha,double f,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [CosineSignal](#classCosineSignal) from parameters.
`public  `[`CosineSignal`](#classCosineSignal_1ad69d9fa507d81bbb3db79bc1d3e4fc34)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [CosineSignal](#classCosineSignal) from input file.
`public void `[`calculate_signal`](#classCosineSignal_1a117f1ddb1b7cbdacbf179891ff440229)`()` | Calculates the cosine get_value.
`public double `[`signal`](#classCosineSignal_1a541f39de155f6a92162882ce102480bd)`(double t) const` | Returns get_value, i.e. alpha*cos(2*pi*f*t)
`public inline double `[`get_f`](#classCosineSignal_1ae4d286b605aa34aca31619f121fe0b41)`() const` | Getter function for the frequency.

## Members

#### `public  `[`CosineSignal`](#classCosineSignal_1ab4df140ccdbbf7eb1138647eb53a5100)`(double alpha,double f,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [CosineSignal](#classCosineSignal) from parameters.

#### Parameters
* `alpha` Amplitude 

* `f` Frequency 

* `time_frame` [TimeFrame](#classTimeFrame)

#### `public  `[`CosineSignal`](#classCosineSignal_1ad69d9fa507d81bbb3db79bc1d3e4fc34)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [CosineSignal](#classCosineSignal) from input file.

#### Parameters
* `input_file` Input file in .json format 

* `time_frame` [TimeFrame](#classTimeFrame)

#### `public void `[`calculate_signal`](#classCosineSignal_1a117f1ddb1b7cbdacbf179891ff440229)`()` 

Calculates the cosine get_value.

#### `public double `[`signal`](#classCosineSignal_1a541f39de155f6a92162882ce102480bd)`(double t) const` 

Returns get_value, i.e. alpha*cos(2*pi*f*t)

#### Parameters
* `t` Time 

#### Returns
[Signal](#classSignal), i.e. alpha*cos(2*pi*f*t)

#### `public inline double `[`get_f`](#classCosineSignal_1ae4d286b605aa34aca31619f121fe0b41)`() const` 

Getter function for the frequency.

#### Returns
The frequency of the get_value f

# class `FiringRate` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FiringRate`](#classFiringRate_1ac506774b7c0bf454c4af8dfcf497c480)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | 
`public virtual  `[`~FiringRate`](#classFiringRate_1a1d4aa6b0c5a4a5dddfb321766e31a98a)`()` | 
`public void `[`add_spike_train`](#classFiringRate_1a8eea33955d3dee79f3bf887d299e3d13)`(const `[`SpikeTrain`](#classSpikeTrain)` & spike_train)` | 
`public void `[`clear`](#classFiringRate_1ab5691e0625054ea68ea17edb204403c2)`()` | 
`public void `[`calculate`](#classFiringRate_1a77db23d6ed7e1eee4b5116a88b09be3a)`()` | 
`public inline double * `[`get_values`](#classFiringRate_1a139e28e94b4eab0733df80b47dbfc4d2)`() const` | 
`protected unsigned int `[`N_Neurons`](#classFiringRate_1af40b4c9d25bdb83b9bce4c32c4956850) | 
`protected `[`TimeFrame`](#classTimeFrame)` `[`time_frame`](#classFiringRate_1a3e07145cd2e4ed8054eabc02cde84f49) | 
`protected int * `[`spike_histogram`](#classFiringRate_1aca350475eed8a7d06a8b68dc1b436e95) | 
`protected double * `[`values`](#classFiringRate_1ad270ec833090d6dd3f2f231c5788fb02) | 

## Members

#### `public  explicit `[`FiringRate`](#classFiringRate_1ac506774b7c0bf454c4af8dfcf497c480)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

#### `public virtual  `[`~FiringRate`](#classFiringRate_1a1d4aa6b0c5a4a5dddfb321766e31a98a)`()` 

#### `public void `[`add_spike_train`](#classFiringRate_1a8eea33955d3dee79f3bf887d299e3d13)`(const `[`SpikeTrain`](#classSpikeTrain)` & spike_train)` 

#### `public void `[`clear`](#classFiringRate_1ab5691e0625054ea68ea17edb204403c2)`()` 

#### `public void `[`calculate`](#classFiringRate_1a77db23d6ed7e1eee4b5116a88b09be3a)`()` 

#### `public inline double * `[`get_values`](#classFiringRate_1a139e28e94b4eab0733df80b47dbfc4d2)`() const` 

#### `protected unsigned int `[`N_Neurons`](#classFiringRate_1af40b4c9d25bdb83b9bce4c32c4956850) 

#### `protected `[`TimeFrame`](#classTimeFrame)` `[`time_frame`](#classFiringRate_1a3e07145cd2e4ed8054eabc02cde84f49) 

#### `protected int * `[`spike_histogram`](#classFiringRate_1aca350475eed8a7d06a8b68dc1b436e95) 

#### `protected double * `[`values`](#classFiringRate_1ad270ec833090d6dd3f2f231c5788fb02) 

# class `FiringRateBox` 

```
class FiringRateBox
  : public FiringRate
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`FiringRateBox`](#classFiringRateBox_1a418c5f3d1a16eb490eb4641e189fcf5e)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | 
`public  explicit `[`FiringRateBox`](#classFiringRateBox_1a2bee840d086d1a23a2536d91975cb446)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | 
`public virtual void `[`calculate`](#classFiringRateBox_1a71165c477dbe3663d37420e7fe23bd22)`()` | 

## Members

#### `public  `[`FiringRateBox`](#classFiringRateBox_1a418c5f3d1a16eb490eb4641e189fcf5e)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

#### `public  explicit `[`FiringRateBox`](#classFiringRateBox_1a2bee840d086d1a23a2536d91975cb446)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

#### `public virtual void `[`calculate`](#classFiringRateBox_1a71165c477dbe3663d37420e7fe23bd22)`()` 

# class `FiringRateExp` 

```
class FiringRateExp
  : public FiringRate
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`FiringRateExp`](#classFiringRateExp_1a63b8ff7c35ae0352c8a168d6de50c07d)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | 
`public  `[`FiringRateExp`](#classFiringRateExp_1a135d0b116b468fe3b4bde4fad808343c)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame,double res)` | 
`public virtual void `[`calculate`](#classFiringRateExp_1afb913f924cd539ec7ba7e73e85d674fe)`()` | 

## Members

#### `public  `[`FiringRateExp`](#classFiringRateExp_1a63b8ff7c35ae0352c8a168d6de50c07d)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

#### `public  `[`FiringRateExp`](#classFiringRateExp_1a135d0b116b468fe3b4bde4fad808343c)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame,double res)` 

#### `public virtual void `[`calculate`](#classFiringRateExp_1afb913f924cd539ec7ba7e73e85d674fe)`()` 

# class `FiringRateFactory` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `FiringRateSimulation` 

```
class FiringRateSimulation
  : public Simulation
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`FiringRateSimulation`](#classFiringRateSimulation_1a7446f0c4fc0bdb388a839b286b6e3657)`(const `[`Options`](#classOptions)` & opts)` | 
`public  `[`~FiringRateSimulation`](#classFiringRateSimulation_1a54bbfc7f55b46db138e4886af3a3ce5f)`()` | 
`public virtual void `[`run`](#classFiringRateSimulation_1afe2d8195f173da15c601f33de4a09998)`()` | 

## Members

#### `public  explicit `[`FiringRateSimulation`](#classFiringRateSimulation_1a7446f0c4fc0bdb388a839b286b6e3657)`(const `[`Options`](#classOptions)` & opts)` 

#### `public  `[`~FiringRateSimulation`](#classFiringRateSimulation_1a54bbfc7f55b46db138e4886af3a3ce5f)`()` 

#### `public virtual void `[`run`](#classFiringRateSimulation_1afe2d8195f173da15c601f33de4a09998)`()` 

# class `IF` 

```
class IF
  : public Neuron
```  

An abstract base class for integrate-and-fire neurons.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`IF`](#classIF_1a2db11718c548d0c8afabdd1dc96c3b7e)`(const std::string & input_file)` | Construct [IF](#classIF) from input file.
`public  `[`IF`](#classIF_1a965019357edab5848988178828ceaa40)`(double mu,double D)` | Construct [IF](#classIF) from parameters.
`public double `[`drift`](#classIF_1a97d6b474e5aa8b21c9495b44c85407d9)`(double v) const` | Returns the drift of the [IF](#classIF) neuron.
`public double `[`diffusion`](#classIF_1a37f5085087483968fe31a69589c3dd66)`() const` | Returns the diffusion of the [IF](#classIF) neuron, i.e. in general sqrt(2 * D)
`public virtual void `[`get_spike_train`](#classIF_1a44fd042a776ae3b2cc1452ad6a7b8a51)`(const `[`TimeFrame`](#classTimeFrame)` & time,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` | Returns a spike train, i.e. an array with as many steps as the time frame, that contains a zero if the neuron has not spiked and a 1 if it has spiked in the corresponding time bin. We use the Euler-Maruyama-Scheme to solve the SDE for the [IF](#classIF) neuron an simply put a 1 into the spike train array, whenever the neuron spikes. 
`public void `[`get_spike_train`](#classIF_1a74603ee6bf2f9c8aa95b6850cd7b537b)`(const `[`TimeFrame`](#classTimeFrame)` & time,const `[`Signal`](#classSignal)` & signal,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` | Returns a spike train, where [IF](#classIF) is subject to a get_value.
`public void `[`get_voltage_curve`](#classIF_1a94b82eab86ab74e9213be11e438f2bad)`(const `[`TimeFrame`](#classTimeFrame)` & time,double * v) const` | Returns a trajectory, i.e. v(t).
`public inline void `[`set_mu`](#classIF_1a6801b689c8e56d71e6327d66fbaed2a7)`(double mu_new)` | Setter method for mean input current.
`public inline void `[`set_D`](#classIF_1a33e485c7b8b6028872c4daf49b18238c)`(double D_new)` | Setter method for diffusion coefficient.
`public virtual void `[`print_info`](#classIF_1ad208485b323c374be75082d6ad1412f7)`(std::ofstream & file)` | 
`protected double `[`mu`](#classIF_1a9f690c993d7b7cd0095e26607503db72) | mean input current
`protected double `[`D`](#classIF_1a7e0fdbf32975dba0acf8096524885639) | diffusion coefficient

## Members

#### `public  explicit `[`IF`](#classIF_1a2db11718c548d0c8afabdd1dc96c3b7e)`(const std::string & input_file)` 

Construct [IF](#classIF) from input file.

#### Parameters
* `input_file` Input file in .json format.

#### `public  `[`IF`](#classIF_1a965019357edab5848988178828ceaa40)`(double mu,double D)` 

Construct [IF](#classIF) from parameters.

#### Parameters
* `mu` Mean input current 

* `D` Diffusion coefficient

#### `public double `[`drift`](#classIF_1a97d6b474e5aa8b21c9495b44c85407d9)`(double v) const` 

Returns the drift of the [IF](#classIF) neuron.

#### Parameters
* `v` Voltage 

* `t` Time 

#### Returns
Drift

#### `public double `[`diffusion`](#classIF_1a37f5085087483968fe31a69589c3dd66)`() const` 

Returns the diffusion of the [IF](#classIF) neuron, i.e. in general sqrt(2 * D)

#### Returns
Diffusion of [IF](#classIF) neuron, i.e. sqrt(2*D)

#### `public virtual void `[`get_spike_train`](#classIF_1a44fd042a776ae3b2cc1452ad6a7b8a51)`(const `[`TimeFrame`](#classTimeFrame)` & time,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` 

Returns a spike train, i.e. an array with as many steps as the time frame, that contains a zero if the neuron has not spiked and a 1 if it has spiked in the corresponding time bin. We use the Euler-Maruyama-Scheme to solve the SDE for the [IF](#classIF) neuron an simply put a 1 into the spike train array, whenever the neuron spikes. 
#### Parameters
* `time` [TimeFrame](#classTimeFrame)

* `spike_train` Spike train

#### `public void `[`get_spike_train`](#classIF_1a74603ee6bf2f9c8aa95b6850cd7b537b)`(const `[`TimeFrame`](#classTimeFrame)` & time,const `[`Signal`](#classSignal)` & signal,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` 

Returns a spike train, where [IF](#classIF) is subject to a get_value.

Produces a spike train, i.e. an array with as many steps as the time frame, that contains a zero if the neuron has not spiked and a 1 if it has spiked in the corresponding time bin. We use the Euler-Maruyama-Scheme to solve the SDE for the [IF](#classIF) neuron an simply put a 1 into the spike train array, whenever the neuron spikes. 
#### Parameters
* `time` [TimeFrame](#classTimeFrame)

* `signal` [Signal](#classSignal)

#### Returns
A spike train

#### `public void `[`get_voltage_curve`](#classIF_1a94b82eab86ab74e9213be11e438f2bad)`(const `[`TimeFrame`](#classTimeFrame)` & time,double * v) const` 

Returns a trajectory, i.e. v(t).

#### Parameters
* `time` [TimeFrame](#classTimeFrame)

* `v` Array of voltages at times given by time frame

#### `public inline void `[`set_mu`](#classIF_1a6801b689c8e56d71e6327d66fbaed2a7)`(double mu_new)` 

Setter method for mean input current.

#### Parameters
* `mu_new` Mean input current

#### `public inline void `[`set_D`](#classIF_1a33e485c7b8b6028872c4daf49b18238c)`(double D_new)` 

Setter method for diffusion coefficient.

#### Parameters
* `D_new`

#### `public virtual void `[`print_info`](#classIF_1ad208485b323c374be75082d6ad1412f7)`(std::ofstream & file)` 

#### `protected double `[`mu`](#classIF_1a9f690c993d7b7cd0095e26607503db72) 

mean input current

#### `protected double `[`D`](#classIF_1a7e0fdbf32975dba0acf8096524885639) 

diffusion coefficient

# class `IFAC` 

```
class IFAC
  : public Neuron
```  

An abstract base class for integrate-and-fire neurons with an adaptation current.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`IFAC`](#classIFAC_1a1a706c88d8c0a4517078d9a740bcbcd7)`(const std::string & input_file)` | Construct [IFAC](#classIFAC) from input file.
`public  `[`IFAC`](#classIFAC_1acdc9984b9056cac672b624d1292b7b34)`(double mu,double D,double tau_a,double Delta)` | Construct [IFAC](#classIFAC) from parameters.
`public double `[`drift`](#classIFAC_1a565e9d720f140f8a1137d12418a600b5)`(double v) const` | Returns the drift of the [IFAC](#classIFAC) neuron.
`public double `[`diffusion`](#classIFAC_1ad0dd54fd39745d6b705ecbd9cea9e7ce)`() const` | Returns the diffusion of the [IFAC](#classIFAC) neuron, i.e. in general sqrt(2 * D)
`public virtual void `[`get_spike_train`](#classIFAC_1a131853e12e12d8ffdda546250eced232)`(const `[`TimeFrame`](#classTimeFrame)` & time,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` | Returns a spike train.
`public void `[`get_spike_train`](#classIFAC_1a11d47dd9059793e93a2bded7e5ae4084)`(const `[`TimeFrame`](#classTimeFrame)` & time,const `[`Signal`](#classSignal)` & signal,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` | Returns a spike train, where [IFAC](#classIFAC) is subject to a get_value.
`public void `[`get_voltage_curve`](#classIFAC_1a97ae1af56783107dcdc858e0eebc3c5d)`(const `[`TimeFrame`](#classTimeFrame)` & time,double * v,double * a) const` | Returns a trajectory, i.e. v(t).
`public inline void `[`set_mu`](#classIFAC_1ae0f31b08edffcdcc991d91771f4e3c24)`(double mu_new)` | Setter method for mean input current.
`public inline void `[`set_D`](#classIFAC_1af0b9ce68ad82904064dada5f9aad80dd)`(double D_new)` | Setter method for diffusion coefficient.
`public virtual void `[`print_info`](#classIFAC_1a08aab052f585ab8d2b25d56ddca6bccf)`(std::ofstream & file)` | 
`protected double `[`mu`](#classIFAC_1a8b51cf88cb3779d1334d62228fccdff8) | mean input current
`protected double `[`D`](#classIFAC_1abaf183ee9171f088b3edcd0c7869c10f) | diffusion coefficient
`protected double `[`tau_a`](#classIFAC_1a6ee33625195b34b3303b87cb49fc91ae) | adaptation time constant
`protected double `[`Delta`](#classIFAC_1a43439b9dcf6f4fceebd02fad269645b6) | kick size of the adaptation

## Members

#### `public  explicit `[`IFAC`](#classIFAC_1a1a706c88d8c0a4517078d9a740bcbcd7)`(const std::string & input_file)` 

Construct [IFAC](#classIFAC) from input file.

#### Parameters
* `input_file` Input file in .json format.

#### `public  `[`IFAC`](#classIFAC_1acdc9984b9056cac672b624d1292b7b34)`(double mu,double D,double tau_a,double Delta)` 

Construct [IFAC](#classIFAC) from parameters.

#### Parameters
* `mu` Mean input current 

* `D` Diffusion coefficient

#### `public double `[`drift`](#classIFAC_1a565e9d720f140f8a1137d12418a600b5)`(double v) const` 

Returns the drift of the [IFAC](#classIFAC) neuron.

#### Parameters
* `v` Voltage 

* `t` Time 

#### Returns
Drift

#### `public double `[`diffusion`](#classIFAC_1ad0dd54fd39745d6b705ecbd9cea9e7ce)`() const` 

Returns the diffusion of the [IFAC](#classIFAC) neuron, i.e. in general sqrt(2 * D)

#### Returns
Diffusion of [IFAC](#classIFAC) neuron, i.e. sqrt(2*D)

#### `public virtual void `[`get_spike_train`](#classIFAC_1a131853e12e12d8ffdda546250eced232)`(const `[`TimeFrame`](#classTimeFrame)` & time,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` 

Returns a spike train.

Returns a spike train, i.e. an array with as many steps as the time frame, that contains a zero if the neuron has not spiked and a 1 if it has spiked in the corresponding time bin. We use the Euler-Maruyama-Scheme to solve the SDE for the [IFAC](#classIFAC) neuron an simply put a 1 into the spike train array, whenever the neuron spikes. 
#### Parameters
* `time` [TimeFrame](#classTimeFrame)

#### `public void `[`get_spike_train`](#classIFAC_1a11d47dd9059793e93a2bded7e5ae4084)`(const `[`TimeFrame`](#classTimeFrame)` & time,const `[`Signal`](#classSignal)` & signal,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` 

Returns a spike train, where [IFAC](#classIFAC) is subject to a get_value.

Produces a spike train, i.e. an array with as many steps as the time frame, that contains a zero if the neuron has not spiked and a 1 if it has spiked in the corresponding time bin. We use the Euler-Maruyama-Scheme to solve the SDE for the [IFAC](#classIFAC) neuron an simply put a 1 into the spike train array, whenever the neuron spikes. 
#### Parameters
* `time` [TimeFrame](#classTimeFrame)

* `signal` [Signal](#classSignal)

#### Returns
A spike train

#### `public void `[`get_voltage_curve`](#classIFAC_1a97ae1af56783107dcdc858e0eebc3c5d)`(const `[`TimeFrame`](#classTimeFrame)` & time,double * v,double * a) const` 

Returns a trajectory, i.e. v(t).

#### Parameters
* `v` Array of voltages at times given by time frame 

* `time` [TimeFrame](#classTimeFrame)

#### `public inline void `[`set_mu`](#classIFAC_1ae0f31b08edffcdcc991d91771f4e3c24)`(double mu_new)` 

Setter method for mean input current.

#### Parameters
* `mu_new` Mean input current

#### `public inline void `[`set_D`](#classIFAC_1af0b9ce68ad82904064dada5f9aad80dd)`(double D_new)` 

Setter method for diffusion coefficient.

#### Parameters
* `D_new`

#### `public virtual void `[`print_info`](#classIFAC_1a08aab052f585ab8d2b25d56ddca6bccf)`(std::ofstream & file)` 

#### `protected double `[`mu`](#classIFAC_1a8b51cf88cb3779d1334d62228fccdff8) 

mean input current

#### `protected double `[`D`](#classIFAC_1abaf183ee9171f088b3edcd0c7869c10f) 

diffusion coefficient

#### `protected double `[`tau_a`](#classIFAC_1a6ee33625195b34b3303b87cb49fc91ae) 

adaptation time constant

#### `protected double `[`Delta`](#classIFAC_1a43439b9dcf6f4fceebd02fad269645b6) 

kick size of the adaptation

# class `LIF` 

```
class LIF
  : public IF
```  

Implements a leaky integrate-and-fire ([LIF](#classLIF)) neuron.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`LIF`](#classLIF_1a368895a753990fa32eb317fde0e9eac5)`(double mu,double D)` | Construct [LIF](#classLIF) from parameters.
`public  explicit `[`LIF`](#classLIF_1a1fcddc7f8aa88974ef0143af4469b547)`(const std::string & input_file)` | Construct [LIF](#classLIF) from input file.
`public virtual double `[`drift`](#classLIF_1a766c537126f272f3efafc168f7564ad1)`(double v) const` | Returns the drift of the [LIF](#classLIF) neuron, i.e. mu - v.

## Members

#### `public  `[`LIF`](#classLIF_1a368895a753990fa32eb317fde0e9eac5)`(double mu,double D)` 

Construct [LIF](#classLIF) from parameters.

#### Parameters
* `mu` Mean input current 

* `D` Diffusion coefficient

#### `public  explicit `[`LIF`](#classLIF_1a1fcddc7f8aa88974ef0143af4469b547)`(const std::string & input_file)` 

Construct [LIF](#classLIF) from input file.

#### Parameters
* `input_file` input file in .json format.

#### `public virtual double `[`drift`](#classLIF_1a766c537126f272f3efafc168f7564ad1)`(double v) const` 

Returns the drift of the [LIF](#classLIF) neuron, i.e. mu - v.

#### Parameters
* `v` Voltage 

* `t` Time 

#### Returns
Drift of [LIF](#classLIF), i.e. mu - v

# class `LIFAC` 

```
class LIFAC
  : public IFAC
```  

Implements a leaky integrate-and-fire ([LIFAC](#classLIFAC)) neuron.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`LIFAC`](#classLIFAC_1aa9bfde55f8fdcc29c888cd76df467ecb)`(double mu,double D,double tau_a,double Delta)` | Construct [LIFAC](#classLIFAC) from parameters.
`public  explicit `[`LIFAC`](#classLIFAC_1a704c5c7e2805b5111baef462850146a9)`(const std::string & input_file)` | Construct [LIFAC](#classLIFAC) from input file.
`public virtual double `[`drift`](#classLIFAC_1a5abccba21a0503101d789ae4132d07d3)`(double v) const` | Returns the drift of the [LIFAC](#classLIFAC) neuron, i.e. mu - v.

## Members

#### `public  `[`LIFAC`](#classLIFAC_1aa9bfde55f8fdcc29c888cd76df467ecb)`(double mu,double D,double tau_a,double Delta)` 

Construct [LIFAC](#classLIFAC) from parameters.

#### Parameters
* `mu` Mean input current 

* `D` Diffusion coefficient

#### `public  explicit `[`LIFAC`](#classLIFAC_1a704c5c7e2805b5111baef462850146a9)`(const std::string & input_file)` 

Construct [LIFAC](#classLIFAC) from input file.

#### Parameters
* `input_file` input file in .json format.

#### `public virtual double `[`drift`](#classLIFAC_1a5abccba21a0503101d789ae4132d07d3)`(double v) const` 

Returns the drift of the [LIFAC](#classLIFAC) neuron, i.e. mu - v.

#### Parameters
* `v` Voltage 

* `t` Time 

#### Returns
Drift of [LIFAC](#classLIFAC), i.e. mu - v

# class `Neuron` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`get_spike_train`](#classNeuron_1abffccc1f233e497aa62dcadaf6308fec)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` | 
`public inline virtual  `[`~Neuron`](#classNeuron_1aecd41febe74ef417230cd74af0c8b801)`()` | 
`public void `[`print_info`](#classNeuron_1a0ff407ba67eb050e535395ff462bb57e)`(std::ofstream & file)` | 

## Members

#### `public void `[`get_spike_train`](#classNeuron_1abffccc1f233e497aa62dcadaf6308fec)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame,`[`SpikeTrain`](#classSpikeTrain)` & spike_train) const` 

#### `public inline virtual  `[`~Neuron`](#classNeuron_1aecd41febe74ef417230cd74af0c8b801)`()` 

#### `public void `[`print_info`](#classNeuron_1a0ff407ba67eb050e535395ff462bb57e)`(std::ofstream & file)` 

# class `NeuronFactory` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Options` 

Implements a class that handles command line options.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Options`](#classOptions_1aa1e7b11260c48cbc4d4c52266c74abf2)`(std::string input_file)` | Construct [Options](#classOptions) from input file.
`public  `[`Options`](#classOptions_1ab3a4819d972a234777923d85122bcf37)`(int argc,char * argv)` | Construct [Options](#classOptions) from command line arguments.
`public void `[`check`](#classOptions_1ab8ca4093f5561de9be0405380044c2ea)`()` | Checks the given input file.
`public inline std::string `[`get_input_file`](#classOptions_1a76a7d420bed6ba601f1a222e8b81c9f9)`() const` | Getter method for input file.
`public inline std::string `[`get_output_file`](#classOptions_1a568c9513fefaf32d3834137506aacbcb)`() const` | Getter method for output file.

## Members

#### `public  explicit `[`Options`](#classOptions_1aa1e7b11260c48cbc4d4c52266c74abf2)`(std::string input_file)` 

Construct [Options](#classOptions) from input file.

#### Parameters
* `input_file` Input file in .json format

#### `public  `[`Options`](#classOptions_1ab3a4819d972a234777923d85122bcf37)`(int argc,char * argv)` 

Construct [Options](#classOptions) from command line arguments.

#### Parameters
* `argc` Number of arguments 

* `argv` Array containing command line arguments.

#### `public void `[`check`](#classOptions_1ab8ca4093f5561de9be0405380044c2ea)`()` 

Checks the given input file.

Checks whether input file has right format (JSON) and whether output file already exists.

#### `public inline std::string `[`get_input_file`](#classOptions_1a76a7d420bed6ba601f1a222e8b81c9f9)`() const` 

Getter method for input file.

#### Returns
Input file

#### `public inline std::string `[`get_output_file`](#classOptions_1a568c9513fefaf32d3834137506aacbcb)`() const` 

Getter method for output file.

#### Returns
Output file

# class `PIF` 

```
class PIF
  : public IF
```  

Implement a perfect integrate-and-fire ([PIF](#classPIF)) neuron.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`PIF`](#classPIF_1ac3aaa22c006e70efc91de66078b2dbd2)`(double mu,double D)` | Construct [PIF](#classPIF) from parameters.
`public  explicit `[`PIF`](#classPIF_1ad1a5859ea76a5ebd90d638ddea2bae90)`(const std::string & input_file)` | Construct [PIF](#classPIF) from input file.
`public virtual double `[`drift`](#classPIF_1af0b72df7578d6e17a6098ba97b300971)`(double v) const` | Returns drift of the [PIF](#classPIF) neuron, i.e. mu.

## Members

#### `public  `[`PIF`](#classPIF_1ac3aaa22c006e70efc91de66078b2dbd2)`(double mu,double D)` 

Construct [PIF](#classPIF) from parameters.

#### Parameters
* `mu` Mean input current 

* `D` Diffusion coefficient

#### `public  explicit `[`PIF`](#classPIF_1ad1a5859ea76a5ebd90d638ddea2bae90)`(const std::string & input_file)` 

Construct [PIF](#classPIF) from input file.

#### Parameters
* `input_file` Input file in .json format.

#### `public virtual double `[`drift`](#classPIF_1af0b72df7578d6e17a6098ba97b300971)`(double v) const` 

Returns drift of the [PIF](#classPIF) neuron, i.e. mu.

#### Parameters
* `v` Voltage 

* `t` time 

#### Returns
Drift of [PIF](#classPIF), i.e. mu

# class `PIFAC` 

```
class PIFAC
  : public IFAC
```  

Implement a perfect integrate-and-fire ([PIFAC](#classPIFAC)) neuron.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`PIFAC`](#classPIFAC_1ab3e4e5afd581c30445ef87f0f744f922)`(double mu,double D,double tau_a,double Delta)` | Construct [PIFAC](#classPIFAC) from parameters.
`public  explicit `[`PIFAC`](#classPIFAC_1ab10c86250e427757d3d073d0e1b5be61)`(const std::string & input_file)` | Construct [PIFAC](#classPIFAC) from input file.
`public virtual double `[`drift`](#classPIFAC_1a8d0a92bfe74f964ba61be0fe30b1d8c6)`(double v) const` | Returns drift of the [PIFAC](#classPIFAC) neuron, i.e. mu.

## Members

#### `public  `[`PIFAC`](#classPIFAC_1ab3e4e5afd581c30445ef87f0f744f922)`(double mu,double D,double tau_a,double Delta)` 

Construct [PIFAC](#classPIFAC) from parameters.

#### Parameters
* `mu` Mean input current 

* `D` Diffusion coefficient

#### `public  explicit `[`PIFAC`](#classPIFAC_1ab10c86250e427757d3d073d0e1b5be61)`(const std::string & input_file)` 

Construct [PIFAC](#classPIFAC) from input file.

#### Parameters
* `input_file` Input file in .json format.

#### `public virtual double `[`drift`](#classPIFAC_1a8d0a92bfe74f964ba61be0fe30b1d8c6)`(double v) const` 

Returns drift of the [PIFAC](#classPIFAC) neuron, i.e. mu.

#### Parameters
* `v` Voltage 

* `t` time 

#### Returns
Drift of [PIFAC](#classPIFAC), i.e. mu

# class `Signal` 

An abstract base class for signals.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Signal`](#classSignal_1a66ba81bb6944492a7beba3b7069f6860)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | 
`public virtual  `[`~Signal`](#classSignal_1ae7a1d116cda63e790bf9aab549d57d3a)`()` | 
`public double `[`get_value`](#classSignal_1ac3e9b35d16b3fdd4e98169b55c75ff72)`(unsigned int i) const` | 
`protected `[`TimeFrame`](#classTimeFrame)` `[`time_frame`](#classSignal_1a47f018d11758cab322d1187b9392c1f9) | time frame for get_value
`protected double * `[`signal_values`](#classSignal_1a4c5bbc9cf67b4d98dc917fcda5e8a569) | array containing the get_value values

## Members

#### `public  explicit `[`Signal`](#classSignal_1a66ba81bb6944492a7beba3b7069f6860)`(const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

#### `public virtual  `[`~Signal`](#classSignal_1ae7a1d116cda63e790bf9aab549d57d3a)`()` 

#### `public double `[`get_value`](#classSignal_1ac3e9b35d16b3fdd4e98169b55c75ff72)`(unsigned int i) const` 

#### `protected `[`TimeFrame`](#classTimeFrame)` `[`time_frame`](#classSignal_1a47f018d11758cab322d1187b9392c1f9) 

time frame for get_value

#### `protected double * `[`signal_values`](#classSignal_1a4c5bbc9cf67b4d98dc917fcda5e8a569) 

array containing the get_value values

# class `SignalFactory` 

Implements the factory design pattern for [Signal](#classSignal).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Simulation` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Simulation`](#classSimulation_1a08bea61f1104e2eb498976e457e9f6b2)`(const `[`Options`](#classOptions)` & opts)` | 
`public void `[`run`](#classSimulation_1ab754c23fba87f6a3ff77ca14bb84bcad)`()` | 
`protected `[`Options`](#classOptions)` `[`opts`](#classSimulation_1a9c9607839493a7d44a6c91c48e1b61c1) | 
`protected `[`TimeFrame`](#classTimeFrame)` `[`time_frame`](#classSimulation_1a44d538783237debcd0e69b40b9dfebb8) | 

## Members

#### `public  explicit `[`Simulation`](#classSimulation_1a08bea61f1104e2eb498976e457e9f6b2)`(const `[`Options`](#classOptions)` & opts)` 

#### `public void `[`run`](#classSimulation_1ab754c23fba87f6a3ff77ca14bb84bcad)`()` 

#### `protected `[`Options`](#classOptions)` `[`opts`](#classSimulation_1a9c9607839493a7d44a6c91c48e1b61c1) 

#### `protected `[`TimeFrame`](#classTimeFrame)` `[`time_frame`](#classSimulation_1a44d538783237debcd0e69b40b9dfebb8) 

# class `SpikeTrain` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`SpikeTrain`](#classSpikeTrain_1a89234131093fe028204b883f69c12144)`(unsigned int length)` | 
`public  `[`~SpikeTrain`](#classSpikeTrain_1a9ddd058c55873128700a1c25b1d8519e)`()` | 
`public int `[`spike_count`](#classSpikeTrain_1ae9ffc7ad159494a8e746e919e6d01f98)`()` | 
`public void `[`clear`](#classSpikeTrain_1a69be10de2f956f2a427c58fe24957604)`()` | 
`public void `[`set_spike`](#classSpikeTrain_1ac1fda7916f2f1b6a097e966b28495e24)`(unsigned int i)` | 
`public inline unsigned int `[`get_length`](#classSpikeTrain_1abf58eb51959f9c33949a62e4aa1d6ea0)`() const` | 
`public inline bool `[`get_spike`](#classSpikeTrain_1a4512492632a359fbb895fba2c0c69d8d)`(unsigned int i) const` | 

## Members

#### `public  explicit `[`SpikeTrain`](#classSpikeTrain_1a89234131093fe028204b883f69c12144)`(unsigned int length)` 

#### `public  `[`~SpikeTrain`](#classSpikeTrain_1a9ddd058c55873128700a1c25b1d8519e)`()` 

#### `public int `[`spike_count`](#classSpikeTrain_1ae9ffc7ad159494a8e746e919e6d01f98)`()` 

#### `public void `[`clear`](#classSpikeTrain_1a69be10de2f956f2a427c58fe24957604)`()` 

#### `public void `[`set_spike`](#classSpikeTrain_1ac1fda7916f2f1b6a097e966b28495e24)`(unsigned int i)` 

#### `public inline unsigned int `[`get_length`](#classSpikeTrain_1abf58eb51959f9c33949a62e4aa1d6ea0)`() const` 

#### `public inline bool `[`get_spike`](#classSpikeTrain_1a4512492632a359fbb895fba2c0c69d8d)`(unsigned int i) const` 

# class `StepSignal` 

```
class StepSignal
  : public Signal
```  

Implement a step get_value, i.e. alpha*Theta(t - t_0)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`StepSignal`](#classStepSignal_1ae38da6dae4c1cb5d6df9ac1ccf173859)`(double alpha,double t_0,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [StepSignal](#classStepSignal) from parameters.
`public  `[`StepSignal`](#classStepSignal_1a1903f8153f0fbe302a5995604d04a627)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [StepSignal](#classStepSignal) from input file.
`public void `[`calculate_signal`](#classStepSignal_1a8530665f83564c427c361b5900af82a7)`()` | Calculates the step get_value.
`public double `[`signal`](#classStepSignal_1a04b7f029bb2b53c9b63003b0d6b4360a)`(double t) const` | Returns get_value, i.e. alpha*Theta(t - t_0)

## Members

#### `public  `[`StepSignal`](#classStepSignal_1ae38da6dae4c1cb5d6df9ac1ccf173859)`(double alpha,double t_0,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [StepSignal](#classStepSignal) from parameters.

#### Parameters
* `alpha` Amplitude 

* `t_0` Start time 

* `time_frame` [TimeFrame](#classTimeFrame)

#### `public  `[`StepSignal`](#classStepSignal_1a1903f8153f0fbe302a5995604d04a627)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [StepSignal](#classStepSignal) from input file.

#### Parameters
* `input_file` Input file in .json format 

* `time_frame` [TimeFrame](#classTimeFrame)

#### `public void `[`calculate_signal`](#classStepSignal_1a8530665f83564c427c361b5900af82a7)`()` 

Calculates the step get_value.

#### `public double `[`signal`](#classStepSignal_1a04b7f029bb2b53c9b63003b0d6b4360a)`(double t) const` 

Returns get_value, i.e. alpha*Theta(t - t_0)

#### Parameters
* `t` Time 

#### Returns
[Signal](#classSignal), i.e. alpha*Theta(t - t_0)

# class `TimeFrame` 

A time frame class.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`TimeFrame`](#classTimeFrame_1a34479cb4acf9c7ecc327a6cccfbad8c6)`(const std::string & input_file)` | 
`public  `[`TimeFrame`](#classTimeFrame_1a3e6f3dbcfd7c6daa9c806f0b3f81e7b0)`(double t_0,double t_end,double dt)` | 
`public  `[`~TimeFrame`](#classTimeFrame_1a4537313dd16bc9b59b3fd6887c8b3f17)`()` | 
`public  `[`TimeFrame`](#classTimeFrame_1a4e5717528804707167a130496ca165fa)`(const `[`TimeFrame`](#classTimeFrame)` & frame)` | 
`public void `[`calculate_times`](#classTimeFrame_1a27f15914ed3dbd7b00563d3ed58ecad9)`()` | 
`public inline double `[`get_t_0`](#classTimeFrame_1a2dcc116c5b93708a430660e5387b5aea)`() const` | 
`public inline double `[`get_t_end`](#classTimeFrame_1a607c3393e155e18b95adb96d39c08d2f)`() const` | 
`public inline double `[`get_dt`](#classTimeFrame_1a52fa106c46cbfc82e0fc943d6ce16ee1)`() const` | 
`public inline unsigned int `[`get_steps`](#classTimeFrame_1adc09abd583b017c028e05fdc8c400b00)`() const` | 
`public inline double `[`get_time`](#classTimeFrame_1adf2a505dd44c19ad21d6654b5a124de2)`(unsigned int i) const` | 
`public void `[`print_info`](#classTimeFrame_1aee1f664385ef179f294c766be92a2576)`(std::ofstream & file)` | 

## Members

#### `public  explicit `[`TimeFrame`](#classTimeFrame_1a34479cb4acf9c7ecc327a6cccfbad8c6)`(const std::string & input_file)` 

#### `public  `[`TimeFrame`](#classTimeFrame_1a3e6f3dbcfd7c6daa9c806f0b3f81e7b0)`(double t_0,double t_end,double dt)` 

#### `public  `[`~TimeFrame`](#classTimeFrame_1a4537313dd16bc9b59b3fd6887c8b3f17)`()` 

#### `public  `[`TimeFrame`](#classTimeFrame_1a4e5717528804707167a130496ca165fa)`(const `[`TimeFrame`](#classTimeFrame)` & frame)` 

#### `public void `[`calculate_times`](#classTimeFrame_1a27f15914ed3dbd7b00563d3ed58ecad9)`()` 

#### `public inline double `[`get_t_0`](#classTimeFrame_1a2dcc116c5b93708a430660e5387b5aea)`() const` 

#### `public inline double `[`get_t_end`](#classTimeFrame_1a607c3393e155e18b95adb96d39c08d2f)`() const` 

#### `public inline double `[`get_dt`](#classTimeFrame_1a52fa106c46cbfc82e0fc943d6ce16ee1)`() const` 

#### `public inline unsigned int `[`get_steps`](#classTimeFrame_1adc09abd583b017c028e05fdc8c400b00)`() const` 

#### `public inline double `[`get_time`](#classTimeFrame_1adf2a505dd44c19ad21d6654b5a124de2)`(unsigned int i) const` 

#### `public void `[`print_info`](#classTimeFrame_1aee1f664385ef179f294c766be92a2576)`(std::ofstream & file)` 

# class `TwoCosineSignal` 

```
class TwoCosineSignal
  : public Signal
```  

Implements a get_value consisting of two cosine, i.e. alpha*cos(2*pi*f1*t)

* beta*cos(2*pi*f2*t + phi)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`TwoCosineSignal`](#classTwoCosineSignal_1ac47a3e349961b454fad0ea1bb63c2072)`(double alpha,double f1,double beta,double f2,double phi,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [TwoCosineSignal](#classTwoCosineSignal) from parameters.
`public  `[`TwoCosineSignal`](#classTwoCosineSignal_1a08b380384e62839d5d78b4e5a82ab867)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [TwoCosineSignal](#classTwoCosineSignal) from input file.
`public void `[`calculate_signal`](#classTwoCosineSignal_1a80ca0aa45fde00e67b0cb86912f10e98)`()` | Calculates the cosine get_value.
`public double `[`signal`](#classTwoCosineSignal_1a1129875198d637d80db6f083a207a3ba)`(double t) const` | Returns get_value, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)

## Members

#### `public  `[`TwoCosineSignal`](#classTwoCosineSignal_1ac47a3e349961b454fad0ea1bb63c2072)`(double alpha,double f1,double beta,double f2,double phi,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [TwoCosineSignal](#classTwoCosineSignal) from parameters.

#### Parameters
* `alpha` Amplitude first get_value 

* `f1` Frequency first get_value 

* `beta` amplitude second get_value 

* `f2` Frequency second get_value 

* `phi` Phase shift 

* `time_frame` [TimeFrame](#classTimeFrame)

#### `public  `[`TwoCosineSignal`](#classTwoCosineSignal_1a08b380384e62839d5d78b4e5a82ab867)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [TwoCosineSignal](#classTwoCosineSignal) from input file.

#### Parameters
* `input_file` Input file in .json format

#### `public void `[`calculate_signal`](#classTwoCosineSignal_1a80ca0aa45fde00e67b0cb86912f10e98)`()` 

Calculates the cosine get_value.

#### `public double `[`signal`](#classTwoCosineSignal_1a1129875198d637d80db6f083a207a3ba)`(double t) const` 

Returns get_value, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)

#### Parameters
* `t` Time 

#### Returns
[Signal](#classSignal), i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)

# class `WhiteNoiseSignal` 

```
class WhiteNoiseSignal
  : public Signal
```  

Implements a band limited white gaussian noise get_value.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`WhiteNoiseSignal`](#classWhiteNoiseSignal_1a0a5e415b97399ab6f184cab9d4f431fe)`(double alpha,double f_low,double f_high,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [WhiteNoiseSignal](#classWhiteNoiseSignal) from parameters.
`public  `[`WhiteNoiseSignal`](#classWhiteNoiseSignal_1a64e89c2d08d0a4f3a2c3c28d25feca7a)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` | Construct [WhiteNoiseSignal](#classWhiteNoiseSignal) from input file.
`public void `[`calculate_signal`](#classWhiteNoiseSignal_1a054ec5c3b3da0da98be405ea9323d175)`()` | Generate the white noise, i.e. fill the signal_values.
`public double `[`signal`](#classWhiteNoiseSignal_1a99ec1e0c59f5ded7623ffbcaa5318238)`(double t) const` | Return get_value, i.e. white noise at time t.
`public inline double * `[`get_values`](#classWhiteNoiseSignal_1a493f704916ce0c91cf28dbb4ddc3ba27)`()` | 

## Members

#### `public  `[`WhiteNoiseSignal`](#classWhiteNoiseSignal_1a0a5e415b97399ab6f184cab9d4f431fe)`(double alpha,double f_low,double f_high,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [WhiteNoiseSignal](#classWhiteNoiseSignal) from parameters.

#### Parameters
* `alpha` Amplitude 

* `f_low` Lower cut-off frequency 

* `f_high` Higher cut-off frequency 

* `time` Time frame

#### `public  `[`WhiteNoiseSignal`](#classWhiteNoiseSignal_1a64e89c2d08d0a4f3a2c3c28d25feca7a)`(const std::string & input_file,const `[`TimeFrame`](#classTimeFrame)` & time_frame)` 

Construct [WhiteNoiseSignal](#classWhiteNoiseSignal) from input file.

#### Parameters
* `input_file` Input file in .json format

#### `public void `[`calculate_signal`](#classWhiteNoiseSignal_1a054ec5c3b3da0da98be405ea9323d175)`()` 

Generate the white noise, i.e. fill the signal_values.

#### `public double `[`signal`](#classWhiteNoiseSignal_1a99ec1e0c59f5ded7623ffbcaa5318238)`(double t) const` 

Return get_value, i.e. white noise at time t.

#### Parameters
* `t` Time 

#### Returns
[Signal](#classSignal), i.e. white noise at time t

#### `public inline double * `[`get_values`](#classWhiteNoiseSignal_1a493f704916ce0c91cf28dbb4ddc3ba27)`()` 

Generated by [Moxygen](https://sourcey.com/moxygen)