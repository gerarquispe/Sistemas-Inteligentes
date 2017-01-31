# CNN en TensorFlow para procesar la base de datos Cifar10 - Sistemas Inteligentes

## Descripción
Esta red convolucional utiliza pesos pre calculados producto de varias iteraciones, inicialmente corridas en 
CPU y posteriormente cambiadas a GPU como se muestra en output´s.txt, una vez procesado 100 iteraciones guarda
el resultado para cargarlo de nuevo en siguientes iteraciones.

como se puede ver en el output5.txt se llego a 82.6% (8256 / 10000) de acertacion producto al hacer el testing.
el resultado es producto de hacer varias iteraciones.

## Instalación
Se utilizo:
```ruby
Pycharm 
Cuda 8.0
tensorflow
NVIDIA cuDNN 

## Información 
Se utilizo la base de datos Cifar10.
http://www.cs.utoronto.ca/~kriz/cifar.html
