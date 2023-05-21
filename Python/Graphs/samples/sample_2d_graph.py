# Check: https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.plot.html
# Check: https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.tick_params.html

from cycler import cycler
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np


x = np.linspace(0, 2, 100)  # Sample data.

graph_dimensions=(10, 5) # in inches

plt.figure(figsize=graph_dimensions, layout='constrained')
plt.rcParams['font.family'] = ['Courier New', 'sans-serif']
# ax = plt.axes() # for normal cartesian plot
ax = plt.axes(xscale='log', yscale='log')  # for logarithmic scale
ax.tick_params(direction='inout', length=6, width=2, colors='black', grid_color='gray', grid_alpha=0.3)
ax.grid();


plt.plot(x, x, label='Linear', color='#679423', linestyle='dashed', linewidth=2, marker='o', markersize=3)  # Plot some data on the (implicit) axes.
plt.plot(x, x**2, label='Quadratic', color='#00539C', linewidth=2)
plt.plot(x, x**3, label='Cubic', color='#990011', linewidth=2)
plt.plot(x, x**4, label='Quartic', color='#E5BF00', linewidth=2)
plt.plot(x, x**5, label='Quintic', color='#FC766A', linewidth=2)
plt.plot(x, x**6, label='Sextic', color='#8A307F', linewidth=2)
plt.plot(x, x**7, label='Septic', color='#6FAEAB', linewidth=2)
plt.plot(x, x**8, label='Octic', color='#783937', linewidth=2)
plt.plot(x, x**9, label='Nonic', color='#EEA47F', linewidth=2)
plt.plot(x, x**10, label='Decic', color='#CBD18F', linewidth=2)
# alternatively you can set the color as words: color='green'

#plt.xticks(np.arange(min(x), max(x)+1, 1.0))  # for user specified ticks
#plt.yticks(np.arange(min(x), max(x)+1, 1.0))  # for user specified ticks
plt.xlabel('x label', fontweight='bold')
plt.ylabel('y label', fontweight='bold')
plt.title('Simple Plot', fontweight='bold')

plt.legend();
plt.show()
#plt.savefig('2d_graph.png', transparent=True)  # save with transparent background useful when doing presentations
#plt.savefig('2d_graph.png')