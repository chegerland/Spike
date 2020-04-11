#!/usr/bin/env python3

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import LogNorm

data = np.genfromtxt("lif_suscept_nonlin.csv", dtype=complex, delimiter=',')

abs_mat = np.abs(data)

matplotlib.rcParams["text.usetex"] = True
matplotlib.rcParams["font.size"] = 20
fig, ax = plt.subplots()

pos = ax.matshow(abs_mat, norm=LogNorm(vmin=1e-5, vmax=1e-3))

fig.colorbar(pos, ax=ax)

plt.show()
