import matplotlib.pyplot as plt
import csv

with open("particle_position.csv","r",newline="") as file:
    reader = csv.reader(file)
    count = 0
    iteration = 0
    x = []
    y = []
    z = []
    for row in reader:
        count += 1
        x.append(float(row[0]))
        y.append(float(row[1]))
        z.append(float(row[2]))
        if(count % 40 == 0):
            ax = plt.subplot(projection="3d")
            ax.scatter(x,y,z,c="r")
            ax.set_zlabel('Z')
            ax.set_ylabel('Y')
            ax.set_xlabel('X')
            plt.xlim(-5,5)
            plt.ylim(-5,5)
            ax.set_zlim(0,70)
            plt.title('Iteration {}'.format(iteration))
            plt.draw()
            plt.savefig('Iteration {}.jpg'.format(iteration))
            plt.close()
            count = 0
            x = []
            y = []
            z = []
            iteration += 10