# Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`class `[`IF`](#class-IF) | A generic integrate and fire model.
`class `[`LIF`](#class-LIF) | Leaky integrate and fire model.
`class `[`LIFsig`](#class-LIFsig) | Leaky integrate and fire model with input signal.
`class `[`Neuron`](#class-Neuron) | A generic neuron model.
`class `[`NeuronFactory`](#class-NeuronFactory) | [Neuron](#classNeuron) Factory.
`class `[`PIF`](#class-PIF) | Perfect integrate and fire model.
`class `[`ProgressBar`](#class-ProgressBar) |
`class `[`Simulation`](#class-Simulation) | The simulation class.
`struct `[`Options`](#struct-Options) | Struct for command line options.

# class `IF`

```
class IF
  : public Neuron
```

A generic integrate and fire model.

Implements a generic integrate and fire ([IF](#classIF)) neuron, which per default is an perfect integrate and fire model. This is the superclass of the family of [IF](#classIF) neurons, therefore the drift term can be changed by its subclasses. Through a simulation we obtain the spike times or voltage curve from this class. We can also check the analytic result for the firing rate.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public double `[`drift`](#classIF_1aa8a7a38f8fa3aa013df026734d02784c)`(double v,double t) const` | Returns the drift of a generic [IF](#classIF) model. Is implemented by specific [IF](#classIF) model
`public double `[`diffusion`](#classIF_1a68c88f77df14c886e6f5c47c58c726cb)`(double v,double t) const` | Returns the diffusion of the [IF](#classIF) models which is the same for all of them.
`public virtual void `[`spike_times`](#classIF_1a02d3ef29834a6544096065b0064cfb3a)`(std::vector< double > & spikes,`[`Simulation`](#classSimulation)` * simulation) const` | Returns the times at which the [IF](#classIF) neuron has spiked and puts them into a vector.
`protected double `[`mu`](#classIF_1a9f690c993d7b7cd0095e26607503db72) | Mobility
`protected double `[`D`](#classIF_1a7e0fdbf32975dba0acf8096524885639) | Diffusion coefficient

## Members

#### `public double `[`drift`](#classIF_1aa8a7a38f8fa3aa013df026734d02784c)`(double v,double t) const`

Returns the drift of a generic [IF](#classIF) model. Is implemented by specific [IF](#classIF) model
#### Parameters
* `v` Voltage

* `t` Time

#### `public double `[`diffusion`](#classIF_1a68c88f77df14c886e6f5c47c58c726cb)`(double v,double t) const`

Returns the diffusion of the [IF](#classIF) models which is the same for all of them.
#### Parameters
* `v` Voltage

* `t` Time

#### `public virtual void `[`spike_times`](#classIF_1a02d3ef29834a6544096065b0064cfb3a)`(std::vector< double > & spikes,`[`Simulation`](#classSimulation)` * simulation) const`

Returns the times at which the [IF](#classIF) neuron has spiked and puts them into a vector.
#### Parameters
* `spikes` Vector to put the spike times into

* `simulation` simulation class containing information on the time frame etc.

#### `protected double `[`mu`](#classIF_1a9f690c993d7b7cd0095e26607503db72)

Mobility

#### `protected double `[`D`](#classIF_1a7e0fdbf32975dba0acf8096524885639)

Diffusion coefficient

# class `LIF`

```
class LIF
  : public IF
```

Leaky integrate and fire model.

Implements a leaky integrate and fire ([IF](#classIF)) model. This is a subclass of the generic [IF](#classIF) model, see that page for more documentation.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public  `[`LIF`](#classLIF_1ac496179e78a204e01844cb94c6e0bbfc)`(double a,double b)` | Constructor of a leaky integrate and fire model
`public  `[`LIF`](#classLIF_1aff78a6f7fd61ff29f00d13fa571eba39)`(std::string input_file)` | Constructor of a leaky integrate and fire model from .json file
`public virtual double `[`drift`](#classLIF_1a9b298ddf01f78240748137c3328fb1b7)`(double v,double t) const` | Returns drift of a leaky [IF](#classIF) neuron.
`public double `[`rate_analytic`](#classLIF_1a0acc2bfbc1ea2571d272af23254c171f)`() const` | Returns analytically calculated firing rate of a leaky [IF](#classIF) neuron.
`public virtual void `[`print_parameters`](#classLIF_1ab9977065b155f443b8f99e7e17b11643)`()` | Print parameters of the [PIF](#classPIF) neuron

## Members

#### `public  `[`LIF`](#classLIF_1ac496179e78a204e01844cb94c6e0bbfc)`(double a,double b)`

Constructor of a leaky integrate and fire model
#### Parameters
* `a` mu

* `b` D

#### `public  `[`LIF`](#classLIF_1aff78a6f7fd61ff29f00d13fa571eba39)`(std::string input_file)`

Constructor of a leaky integrate and fire model from .json file
#### Parameters
* `input_file` .json file with parameters

#### `public virtual double `[`drift`](#classLIF_1a9b298ddf01f78240748137c3328fb1b7)`(double v,double t) const`

Returns drift of a leaky [IF](#classIF) neuron.
#### Parameters
* `v` Voltage

* `t` Time

#### `public double `[`rate_analytic`](#classLIF_1a0acc2bfbc1ea2571d272af23254c171f)`() const`

Returns analytically calculated firing rate of a leaky [IF](#classIF) neuron.

#### `public virtual void `[`print_parameters`](#classLIF_1ab9977065b155f443b8f99e7e17b11643)`()`

Print parameters of the [PIF](#classPIF) neuron

# class `LIFsig`

```
class LIFsig
  : public IF
```

Leaky integrate and fire model with input signal.

Implements a leaky integrate and fire ([IF](#classIF)) model with input signal of the form $ s(t) = \varepsilon(\alpha \cos(2 \pi f_1 t) + \beta \cos(2 \pi f_2 t))$. This is a subclass of the generic [IF](#classIF) model, see that page for more documentation.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public  `[`LIFsig`](#classLIFsig_1a317a800d15d150cfeed5b5b6a44e7060)`(std::string input_file)` | Constructs a leaky integrate and fire neuron with input signal from .json file
`public virtual double `[`drift`](#classLIFsig_1afcbd545ef12e48ab849fb446fbb738f7)`(double v,double t) const` | Returns drift of a leaky [IF](#classIF) neuron with two cosine signals.
`public virtual void `[`print_parameters`](#classLIFsig_1a2a944801166183a10a82b9d7cd2ce1b4)`()` | Prints the parameters.

## Members

#### `public  `[`LIFsig`](#classLIFsig_1a317a800d15d150cfeed5b5b6a44e7060)`(std::string input_file)`

Constructs a leaky integrate and fire neuron with input signal from .json file
#### Parameters
* `input_file` .json file with parameters

#### `public virtual double `[`drift`](#classLIFsig_1afcbd545ef12e48ab849fb446fbb738f7)`(double v,double t) const`

Returns drift of a leaky [IF](#classIF) neuron with two cosine signals.
#### Parameters
* `v` Voltage

* `t` Time

#### `public virtual void `[`print_parameters`](#classLIFsig_1a2a944801166183a10a82b9d7cd2ce1b4)`()`

Prints the parameters.

# class `Neuron`

A generic neuron model.

Implements a generic neuron model, i.e. a system which takes a time frame [t_0, t_end] with time steps dt and returns a spike train. We however only record the spike times, since it is easier to derive statistics from it.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public void `[`spike_times`](#classNeuron_1ac85a67df2ebed4d4dc4e940f28b3053c)`(std::vector< double > & spikes,`[`Simulation`](#classSimulation)` * simulation) const` | Simulates the neuron and puts the spike times into the vector spikes
`public void `[`print_parameters`](#classNeuron_1a207c2d342ad6ee03379ffde5987f117d)`()` | Prints all the parameters of the neuron. Every specific neuron type should have an implementation of this.

## Members

#### `public void `[`spike_times`](#classNeuron_1ac85a67df2ebed4d4dc4e940f28b3053c)`(std::vector< double > & spikes,`[`Simulation`](#classSimulation)` * simulation) const`

Simulates the neuron and puts the spike times into the vector spikes
#### Parameters
* `spikes` vector filled with the spike times

* `simulation` simulation object containing t_0, t_end and so on

#### `public void `[`print_parameters`](#classNeuron_1a207c2d342ad6ee03379ffde5987f117d)`()`

Prints all the parameters of the neuron. Every specific neuron type should have an implementation of this.

# class `NeuronFactory`

[Neuron](#classNeuron) Factory.

Class that implements the factory design pattern for neurons.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------

## Members

# class `PIF`

```
class PIF
  : public IF
```

Perfect integrate and fire model.

Implements a perfect integrate and fire ([IF](#classIF)) model. This is a subclass of the generic [IF](#classIF) model, see that page for more documentation.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public  `[`PIF`](#classPIF_1a4c374252456523c0c51bfcc755aeafe8)`(double a,double b)` | Constructor of a perfect integrate and fire neurons
`public  `[`PIF`](#classPIF_1ada1ec3593811f3aa5a4969432d9bdc91)`(std::string input_file)` | Constructor of a perfect integrate and fire neurons from .json file
`public virtual double `[`drift`](#classPIF_1a12aaacff008d1366ddb6fc3ca0e3ed51)`(double v,double t) const` | Returns drift of a perfect [IF](#classIF) neuron.
`public double `[`rate_analytic`](#classPIF_1af25384b6c40708043ba5ac08017e0094)`() const` | Returns analytically calculated firing rate of a perfect [IF](#classIF) neuron.
`public virtual void `[`print_parameters`](#classPIF_1ad41df40096a9a5ab811bd2d8869079b4)`()` | Print parameters of the [PIF](#classPIF) neuron

## Members

#### `public  `[`PIF`](#classPIF_1a4c374252456523c0c51bfcc755aeafe8)`(double a,double b)`

Constructor of a perfect integrate and fire neurons
#### Parameters
* `a` mu

* `b` D

#### `public  `[`PIF`](#classPIF_1ada1ec3593811f3aa5a4969432d9bdc91)`(std::string input_file)`

Constructor of a perfect integrate and fire neurons from .json file
#### Parameters
* `input_file` .json file with parameters

#### `public virtual double `[`drift`](#classPIF_1a12aaacff008d1366ddb6fc3ca0e3ed51)`(double v,double t) const`

Returns drift of a perfect [IF](#classIF) neuron.
#### Parameters
* `v` Voltage

* `t` Time

#### `public double `[`rate_analytic`](#classPIF_1af25384b6c40708043ba5ac08017e0094)`() const`

Returns analytically calculated firing rate of a perfect [IF](#classIF) neuron.

#### `public virtual void `[`print_parameters`](#classPIF_1ad41df40096a9a5ab811bd2d8869079b4)`()`

Print parameters of the [PIF](#classPIF) neuron

# class `ProgressBar`

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public inline  `[`ProgressBar`](#classProgressBar_1a5bf8312df61b462416ae1e034513621f)`(unsigned int total,unsigned int width,char complete,char incomplete)` |
`public inline  `[`ProgressBar`](#classProgressBar_1ac986efc4cc49be7277d880dc2426849c)`(unsigned int total,unsigned int width)` |
`public inline unsigned int `[`operator++`](#classProgressBar_1ad0ad956a659502b816c0e4332ec1e0dc)`()` |
`public inline void `[`display`](#classProgressBar_1a909892ad623435dc7d446abea0b1435c)`() const` |
`public inline void `[`done`](#classProgressBar_1a9f2e824efdf35ad18a991e6000a4cabf)`() const` |

## Members

#### `public inline  `[`ProgressBar`](#classProgressBar_1a5bf8312df61b462416ae1e034513621f)`(unsigned int total,unsigned int width,char complete,char incomplete)`

#### `public inline  `[`ProgressBar`](#classProgressBar_1ac986efc4cc49be7277d880dc2426849c)`(unsigned int total,unsigned int width)`

#### `public inline unsigned int `[`operator++`](#classProgressBar_1ad0ad956a659502b816c0e4332ec1e0dc)`()`

#### `public inline void `[`display`](#classProgressBar_1a909892ad623435dc7d446abea0b1435c)`() const`

#### `public inline void `[`done`](#classProgressBar_1a9f2e824efdf35ad18a991e6000a4cabf)`() const`

# class `Simulation`

The simulation class.

Sets up a simulation. Defines the input and output files, the time window and its discretization as well as the number of times the neuron shall be simulated.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public double `[`t_0`](#classSimulation_1a0aa17d743d8e2468a5288acc520caa09) | start time
`public double `[`t_end`](#classSimulation_1af6d9bd17e49c7a3d30670c91b80c45f9) | end time
`public double `[`dt`](#classSimulation_1af43e498bfc83c777db5f5ac4025ff923) | time step
`public int `[`N`](#classSimulation_1acf2d8cdd78ffc7875e68f92c0e7da823) | simulation count
`public std::string `[`parameters_file`](#classSimulation_1a8c301bdb9716a2e20abfc05a136f38bd) | input file containing parameters
`public std::string `[`spike_times_file`](#classSimulation_1abc6e6e54b1be77e90f03f1db8a99655b) | output file containing the spike times
`public std::vector< std::vector< double > > `[`spike_trains`](#classSimulation_1ae4d2f57e24369e8e38c854165ddefa00) | vector of vectors containing the spike trains of all N neurons
`public inline  `[`Simulation`](#classSimulation_1a5b224cc5b36bcc8eb29689aff223de41)`()` |
`public inline  `[`~Simulation`](#classSimulation_1a80fad3f57dfaf195a36f7bc49bc88279)`()` |
`public  `[`Simulation`](#classSimulation_1a3e07948e7c5c31159647e2acc94a6dda)`(double a,double b,double c)` | Constructor of simulation
`public  `[`Simulation`](#classSimulation_1a3cfff8e90b9095e7a160ec8ea72e52d9)`(double a,double b,double c,int d)` | Constructor of simulation
`public  `[`Simulation`](#classSimulation_1a4b706f606430503b42d890dad0d38bb0)`(std::string parameters_file)` | Constructor of simulation
`public void `[`print_parameters`](#classSimulation_1a717a610d2ad5a37d614a70245372354e)`()` | Print parameters to standard output

## Members

#### `public double `[`t_0`](#classSimulation_1a0aa17d743d8e2468a5288acc520caa09)

start time

#### `public double `[`t_end`](#classSimulation_1af6d9bd17e49c7a3d30670c91b80c45f9)

end time

#### `public double `[`dt`](#classSimulation_1af43e498bfc83c777db5f5ac4025ff923)

time step

#### `public int `[`N`](#classSimulation_1acf2d8cdd78ffc7875e68f92c0e7da823)

simulation count

#### `public std::string `[`parameters_file`](#classSimulation_1a8c301bdb9716a2e20abfc05a136f38bd)

input file containing parameters

#### `public std::string `[`spike_times_file`](#classSimulation_1abc6e6e54b1be77e90f03f1db8a99655b)

output file containing the spike times

#### `public std::vector< std::vector< double > > `[`spike_trains`](#classSimulation_1ae4d2f57e24369e8e38c854165ddefa00)

vector of vectors containing the spike trains of all N neurons

#### `public inline  `[`Simulation`](#classSimulation_1a5b224cc5b36bcc8eb29689aff223de41)`()`

#### `public inline  `[`~Simulation`](#classSimulation_1a80fad3f57dfaf195a36f7bc49bc88279)`()`

#### `public  `[`Simulation`](#classSimulation_1a3e07948e7c5c31159647e2acc94a6dda)`(double a,double b,double c)`

Constructor of simulation
#### Parameters
* `a` t_0

* `b` t_end

* `c` dt

#### `public  `[`Simulation`](#classSimulation_1a3cfff8e90b9095e7a160ec8ea72e52d9)`(double a,double b,double c,int d)`

Constructor of simulation
#### Parameters
* `a` t_0

* `b` t_end

* `c` dt

* `d` N

#### `public  `[`Simulation`](#classSimulation_1a4b706f606430503b42d890dad0d38bb0)`(std::string parameters_file)`

Constructor of simulation
#### Parameters
* `input_file` Input .json file containing parameters

#### `public void `[`print_parameters`](#classSimulation_1a717a610d2ad5a37d614a70245372354e)`()`

Print parameters to standard output

# struct `Options`

Struct for command line options.

Defines a struct to store the command line options.

## Summary

 Members                        | Descriptions
--------------------------------|---------------------------------------------
`public int `[`mode`](#structOptions_1a9f282cb61f771a90fe250293d9cf56dd) | Mode (0 = [Simulation](#classSimulation), 1 = Evaluation, others = unknown)
`public std::string `[`parameters`](#structOptions_1ab36caf7cebe620f98ec7184864d80727) | path to input file containing parameters
`public bool `[`rate`](#structOptions_1ace72f5941f32a7afd6066667c1727d23) | firing rate flag and time bin
`public double `[`dt`](#structOptions_1aaca943ab329c1fa195329314a5e79040) |
`public bool `[`isi`](#structOptions_1a03c17ebd7064fd6671f8d878239c3dd1) | isi flag

## Members

#### `public int `[`mode`](#structOptions_1a9f282cb61f771a90fe250293d9cf56dd)

Mode (0 = [Simulation](#classSimulation), 1 = Evaluation, others = unknown)

#### `public std::string `[`parameters`](#structOptions_1ab36caf7cebe620f98ec7184864d80727)

path to input file containing parameters

#### `public bool `[`rate`](#structOptions_1ace72f5941f32a7afd6066667c1727d23)

firing rate flag and time bin

#### `public double `[`dt`](#structOptions_1aaca943ab329c1fa195329314a5e79040)

#### `public bool `[`isi`](#structOptions_1a03c17ebd7064fd6671f8d878239c3dd1)

isi flag

Generated by [Moxygen](https://sourcey.com/moxygen)
