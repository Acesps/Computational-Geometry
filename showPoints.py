import matplotlib.pyplot as plt
import pylab
#enabling interactive mode in pylab
pylab.ion()									
# #function to display and keep the image on screen till refreshing
pylab.show()


filename = "./allPoints.txt"
X=[]
Y=[]
with open(filename, "r") as file:
	for line in file:
		x,y = map(int,line.split())
		X.append(x)
		Y.append(y)
plt.scatter(X,Y)
# plt.plot(X,Y,'-o')s
plt.show()

filename = "./Grahams.txt"
X=[]
Y=[]
with open(filename, "r") as file:
	for line in file:
		x,y = map(int,line.split())
		X.append(x)
		Y.append(y)
plt.plot(X,Y,"-o")
plt.show()

filename = "./Jarvis.txt"
X=[]
Y=[]
with open(filename, "r") as file:
	for line in file:
		x,y = map(int,line.split())
		X.append(x)
		Y.append(y)
plt.plot(X,Y,"-o")
plt.show()

filename = "./kirkpatrick-seidal.txt"
X=[]
Y=[]
with open(filename, "r") as file:
	for line in file:
		x,y = map(int,line.split())
		X.append(x)
		Y.append(y)
plt.plot(X,Y,"-o")
plt.show()

plt.pause(100)