import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib as mpl
from matplotlib.ticker import LinearLocator, FormatStrFormatter
name = "Result.txt"
f = open("Result.txt")
data = f.readlines()
n = len(data)
clicksize = np.zeros(n)
nmbrofclicks = np.zeros(n)
nmbroflinks = int(data[0])
times = np.zeros(n)

for i in range(1,n):
#    print(i)
    split = data[i].split()
    clicksize[i] = split[0]
    nmbrofclicks[i] = split[1]
    #nmbroflinks[i] = split[1]
    times[i] = split[2]


#mintime = times.min()
#maxtime = times.max()
#maxclicksize = clicksize.max()
#maxnbrofclicks = nmbrofclicks.max()
#maxnbroflinks = nmbroflinks.max()

x = clicksize
y = nmbrofclicks
z = times

#intervales
#XX, YY = np.meshgrid(clicksize, nmbrofclicks)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x,y,z,c = 'black', marker ='o')

b = str(nmbroflinks) if (nmbroflinks > 0) else 'random' 
fake2Dline = mpl.lines.Line2D([0],[0], linestyle="none", c='b', marker = 'o')
ax.legend([fake2Dline], ['louvain\'time exec  with '+ b + 'link between clicks '], numpoints = 1)

ax.set_xlabel('click size n')
ax.set_ylabel('number of clicks K')
ax.set_zlabel('time to execute')

plt.show()
