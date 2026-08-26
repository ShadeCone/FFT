import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('data.csv')
magnitude = np.sqrt(df["real"] ** 2 + df["imag"] ** 2)

N = len(df)
k = []
for obj in range(N):
    k.append(4*obj/N)

print(k)
plt.scatter(k, magnitude, s=200)
plt.show()