import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as tic

fig = plt.figure()

x = np.arange(100)
y = 3.*np.sin(x*2.*np.pi/100.)

for i in range(3):
    temp = 130 + i
    print(temp)
    ax = plt.subplot(temp+1)
    plt.plot(x,y)
    plt.subplots_adjust(wspace = .001)
    #temp = tic.MaxNLocator(3)
    #ax.yaxis.set_major_locator(temp)
    if i>0:
        ax.set_yticklabels(())
    #ax.title.set_visible(False)

plt.show()
