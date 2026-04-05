import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
import math
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from sklearn.preprocessing import MinMaxScaler

dados = pd.read_csv('previsaoClima.csv')

dadosPlot = dados.iloc[:31]
mapa = {'Sol': 0, 'Chuva': 1}
dadosPlot['estado_num'] = dadosPlot['estado'].map(mapa)

x = range(len(dadosPlot))
y = dadosPlot['estado_num']

plt.figure()

# Optional: thin line (no vertical jumps)
plt.plot(x, y, linewidth=1, alpha=0.3)

# Bigger, clearer dots with edge
plt.scatter(
    x, y,
    c=['red' if v == 0 else 'blue' for v in y],
    s=50,              # bigger dots
     edgecolors='black'
   
)

plt.yticks([0, 1], ['Sol', 'Chuva'])
plt.xlabel('Tempo (dias)')
plt.ylabel('Estado')
plt.title('Evolução do Estado do Clima')

plt.grid(True)
plt.show()