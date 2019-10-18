# Signals

There are several input signals available.
They're all specified in the input file (format `.json`) with the appropriate parameters.
The default behaviour is no signal.

# Two cosines
Obeys the equation
$$ s(t) = \varepsilon(\alpha \cos(2 \pi f_1 t) + \beta \cos(2 \pi f_2 t)) $$
The input file for a two cosines signal looks like
```.json
    "Signal" :
    {
        "type": "TwoCosine",
        "eps" : 0.05,
        "alpha" : 1.0,
        "beta" : 0.0,
        "phi" : 0.0,
        "f1" : 0.215,
        "f2" : 0.0
    }
```
