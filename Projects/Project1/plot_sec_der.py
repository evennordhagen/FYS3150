import numpy as np
import matplotlib.pyplot as plt
from os import system

Nlist = [1,2,3,4,5]
hlist=[np.log(10**n) for n in Nlist]
epslist=[]

for n in Nlist:
	N=10**n
	#Calling the cpp program, which writing a file "doubder.dat"
	systemStr = "./project1 %d" % N #Angir mappe og fil
	system(systemStr)

	#Reading "doubder.dat"
	approx=[];exact=[]
	infile=open('second_der.dat','r')
	for line in infile:
		numbers=line.split()
		approx.append(float(numbers[0]))
		exact.append(float(numbers[1]))
	infile.close()

	#Calculating the error
	a=-10**2
	for j in range(len(exact)-2):
		i=j+1
		epsilon=np.log10(np.abs((approx[i]-exact[i])/exact[i]))
		if epsilon>a:
		    a=epsilon
	epslist.append(a)
	print "Maximum error: ",a

x=np.linspace(0,1,len(exact))

#--Plot--
#Error
SZ={'size':'14'}
plt.plot(Nlist,epslist)
plt.title('Relative error as function of step size',**SZ)
plt.xlabel('$log(h)$',**SZ)
plt.ylabel('Relative error',**SZ)
plt.grid()
plt.show()

#Exact vs approx
plt.plot(x,approx)
plt.plot(x,exact)
plt.title('Plotting exact vs. approx second derivated',**SZ)
plt.xlabel('x value',**SZ)
plt.ylabel('u(x)',**SZ)
plt.legend(['Approximation','Exact'],loc='best')
plt.show()
