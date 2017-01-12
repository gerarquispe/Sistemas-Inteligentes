from __future__ import print_function
import numpy as np
import tflearn

# Cargar archivo CSV, indicando que la primera columna representa los labels
from tflearn.data_utils import load_csv
data, labels = load_csv('car.data', target_column=6, categorical_labels=False, n_classes=4)

# Utilizando diccionarios
def a(x):
    return {
        'vhigh': 0,
        'high': 1,
        'med': 2,
        'low': 3,
        '2': 0,
        '3': 1,
        '4': 2,
        '5more': 3,
        'more': 6,
        'small': 0,
        'med': 1,
        'big': 2,
        'low': 0,
        'med': 1,
        'high': 2
    }[x]

# Funcion de preprocesado
# Preprocessing function
def preprocessLabel(labels):
    data = [[None] * 4] * len(labels)
    for i in range(len(labels)):
        if labels[i] == 'unacc':
            data[i] = [0, 0, 0, 1]
        elif labels[i] == 'acc':
            data[i] = [0, 0, 1, 0]
        elif labels[i] == 'good':
            data[i] = [0, 1, 0, 0]
        else: #vgood
            data[i] = [1, 0, 0, 0]
    return np.array(data, dtype=np.float32)

def preprocess(data):
    for i in range(len(data)):
      #Convirtiendo los datos de cadenas a numeros
      data[i][0] = a(data[i][0])
      data[i][1] = a(data[i][1])
      data[i][2] = a(data[i][2])
      data[i][3] = a(data[i][3])
      data[i][4] = a(data[i][4])
      data[i][5] = a(data[i][5])
    return np.array(data, dtype=np.float32)

# Preprocess data
data = preprocess(data)
labels = preprocessLabel(labels)

# Construyendo la red Neuronal
net = tflearn.input_data(shape=[None, 6])
net = tflearn.fully_connected(net, 120,activation='relu')
net = tflearn.fully_connected(net, 24,activation='sigmoid')
net = tflearn.fully_connected(net, 4, activation='softmax')
net = tflearn.regression(net)

# Definiendo el modelo
model = tflearn.DNN(net)
# Empezando el entrenamiento (Aplicando el algoritmo de gradiente descentente)
model.fit(data, labels, n_epoch=100, batch_size=1000, show_metric=True)

# Segundo test
test2 = [[None] * 6] * 4
test2[0] = ['low','low','4','2','big','high'] # unacc
test2[1] = ['low','low','5more','4','med','med'] #good
test2[2] = ['low','low','5more','more','big','low'] #unacc
test2[3] = ['high','vhigh','3','4','big','med'] #unacc

test2 = preprocess(test2)
pred = model.predict(test2)

for i in range(len(pred)):
    print("unacc " + str(pred[i][3]))
    print("acc " + str(pred[i][2]))
    print("good " + str(pred[i][1]))
    print("vgood " + str(pred[i][0]))
    print("")
