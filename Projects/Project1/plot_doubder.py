import numpy as np
import matplotlib.pyplot as plt

approx=[];exact=[]
infile=open('doubder.dat','r')
for line in infile:
    numbers=line.split()
    approx.append(float(numbers[0]))
    exact.append(float(numbers[1]))
infile.close()

# For sub exercise d
a=0
for i in range(len(exact)):
    epsilon=np.log10(np.abs((approx[i]-exact[i])/exact[i]))
    if abs(epsilon)>a:
        a=epsilon
print "Maximum error: ",a

x=np.linspace(0,1,len(exact))

plt.plot(x,approx)
plt.plot(x,exact)
plt.xlabel('x value')
plt.ylabel('f(x)')
plt.legend(['Approximation','Exact'],loc='best')
plt.show()
