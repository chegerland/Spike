#!/usr/bin/env python3

"""
Here we implement the analytic formulae obtained for the firing rate in the weakly nonlinear case.
"""

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

from modules import LIF

def main():
    print("Calculating stationary rate of LIF")

    lif = LIF.LIF(1.1, 0.001)
    lifadapt = LIF.LIFadapt(1.1, 0.001, 3.0, 0.5)

    t = np.arange(0.0, 15.0, 0.1)
    rate = []
    rateadapt = []
    for i in range(len(t)):
        rate.append( lif.firing_rate_signal(t[i], 0.05, 0.215) )
        rateadapt.append( lifadapt.firing_rate_signal(t[i], 0.05, 0.215) )

    fig, ax = plt.subplots()
    ax.set_xlim(0.0,15.0)
    ax.set_ylim(0.0,0.7)
    ax.set_aspect(7.0)
    ax.plot(t, rate)
    ax.plot(t, rateadapt)
    plt.show()




if __name__ == "__main__":
    main()
