import numpy as np
import matplotlib.pyplot as plt

n=0.1
N=1000
exact=1./3
hvalues=np.linspace(0.000001,n,N)

def arctan(x):
    return np.arctan(x)

def derivate1(f,x,h):
    return (f(x+h)-f(x))/float(h)

values1=np.zeros([N,2])
m=0
for h in hvalues:
    k=n-h
    result=derivate1(arctan,np.sqrt(2),k)
    values1[m,0]=k;values1[m,1]=result
    m+=1

epsilon1=np.log10(abs(values1[:,1]-exact)/exact)
plt.plot(values1[:,0],epsilon1)
plt.xlabel('h-value')
plt.ylabel('Epsilon')
plt.show()


def derivate2(f,x,h):
    return (f(x+h)-f(x-h))/float(2*h)

values2=np.zeros([N,2])
m=0
for h in hvalues:
    k=n-h
    result=derivate2(arctan,np.sqrt(2),k)
    values2[m,0]=k;values2[m,1]=result
    m+=1

epsilon2=np.log10(abs(values2[:,1]-exact)/exact)
plt.plot(values2[:,0],epsilon2)
plt.xlabel('h-value')
plt.ylabel('Epsilon')
plt.show()
