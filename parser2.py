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
clicksize = np.zeros((10,n))
nmbrofclicks = np.zeros((10,n))
nmbroflinks = []
times = np.zeros((10,n))
colors = ['b','r','g','m','c','k','y','aqua','azure','purple']
j = -1
for i in range(n):
    split = data[i].split()
    if (len(split) > 2):
        clicksize[j][i] = split[0]
        nmbrofclicks[j][i] = split[1]
        times[j][i] = split[2]
    else:
        nmbroflinks.append(split[0])
        j = j + 1

#mintime = times.min()
#maxtime = times.max()
#maxclicksize = clicksize.max()
#maxnbrofclicks = nmbrofclicks.max()
#maxnbroflinks = nmbroflinks.max()

x = clicksize
y = nmbrofclicks
z = times
links = ['link '+str(i + 1) for i in range(10)]
#intervales
#XX, YY = np.meshgrid(clicksize, nmbrofclicks)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
scatters = []
for i in range(10):
    ax.scatter(x[i],y[i],z[i],c = colors[i], marker ='o')
    scatters.append( mpl.lines.Line2D([0],[0], linestyle="none", c=colors[i], marker = 'o'))
            #blue_proxy = plt.Rectangle((0, 0), 1, 1, fc="b")
#ax.legend([scatters], [colors], numpoints = 1)
#red_proxy = plt.Rectangle((0, 0), 1, 1, fc="r")
#ax.legend([blue_proxy,red_proxy],['cars','bikes'])
#b = str(nmbroflinks) if (nmbroflinks > 0) else 'random' 
fake2Dline = mpl.lines.Line2D([0],[0], linestyle="none", c='b', marker = 'o')
ax.legend(scatters, links,loc=1, bbox_to_anchor=(0, 1), numpoints = 1)
ax.set_xlabel('click size n')
ax.set_ylabel('number of clicks K')
ax.set_zlabel('time to execute')

plt.show()
