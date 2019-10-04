# Neurons

With Spike it is possible to simulate several neuron types.
They're all specified in the input file (format `.json`) with the appropriate parameters.


# Perfect integrate-and-fire neuron (PIF)
Obeys the equation
$$ \dot{v} = \mu + \sqrt{2 D} \xi(t), $$
where $\mu$ is the drift coefficient, $D$ is the diffusion coefficient and $\xi(t)$ is Gaussian white noise.
The input file for a PIF looks like
```.json
  "Neuron" :
  {
    "type" : "PIF",
    "mu" : 1.0,
    "D" : 0.2
  }
```

# Leaky integrate-and-fire neuron (LIF)
Obeys the equation
$$ \dot{v} = \mu - v + \sqrt{2 D} \xi(t), $$
where $\mu$ is the drift coefficient, $D$ is the diffusion coefficient and $\xi(t)$ is Gaussian white noise.
The input file for a LIF looks like
```.json
  "Neuron" :
  {
    "type" : "LIF",
    "mu" : 1.0,
    "D" : 0.2
  }
```

# Leaky integrate-and-fire neuron (LIFsig) with signal
Obeys the equation
$$ \dot{v} = \mu - v + \sqrt{2 D} \xi(t) + \varepsilon \left( \alpha \cos(2 \pi f_1 t)  + \beta \cos(2 \pi f_2 t + \phi)\right), $$
where $\mu$ is the drift coefficient, $D$ is the diffusion coefficient, $\xi(t)$ is Gaussian white noise and the other parameters specify the signal.
The input file for a LIFsig looks like
```.json
  "Neuron" :
  {
    "type" : "LIFsig",
    "mu" : 3.0,
    "D" : 0.8,
    "eps" : 0.01,
    "alpha" : 1.0,
    "beta" : 0.75,
    "phi" : 0.0,
    "f1" : 0.215,
    "f2" : 0.235
}
```

# Perfect integrate-and-fire neuron (PIFadapt) with adaption
Obeys the equation
$$
\begin{aligned}
\dot{v} &= \mu - v + \sqrt{2 D} \xi(t), \\
\tau_a \dot{a} &= - a + \Delta \sum_{i} \delta(t - t_i)
\end{aligned}
$$
where $\mu$ is the drift coefficient, $D$ is the diffusion coefficient and $\xi(t)$ is Gaussian white noise.
The adaption variable has a time scale $\tau_a$ and a strength of $\Delta$.
Every time the neuron spikes, the adaption variable make a jump $a \to a + \Delta$.
The input file for a PIFadapt looks like
```.json
  "Neuron" :
  {
    "type" : "PIFadapt",
    "mu" : 3.0,
    "D" : 0.1,
    "Delta": 3,
    "tau_a": 2
  }
```
