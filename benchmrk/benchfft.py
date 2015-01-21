import sys
import numpy as np
from scipy.fftpack import fft
import random as rd
c=0
for arg in sys.argv:
    if c > 0:
        pw=int(arg)
        N = 2**pw
        x = np.zeros(N)
        for n in range(N):
            x[n] = rd.random()
        X = fft(x)
    c+=1
