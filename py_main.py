import numpy as np
import matplotlib.pyplot as plt
import csv

def read_file(file):
    with open(file,'r') as f:
        reader = csv.reader(f, delimiter=',')
        header = next(reader)
        data = np.array(list(reader))
    return data

def plot_hash_data():

    data = read_file('hash_data.csv')

    x=[]
    y=[]
    for i in range(len(data)):
        x.append(data[i,:][2:-2])
        y.append(data[i,1:][2:-1])
    
    x = np.array(x).flatten().astype(float)
    y = np.array(y).flatten().astype(float)

    plt.figure(figsize=(5,5))
    plt.scatter(x, y)    
    annotations = [f"      ID: {id}\n      name: {name}" for id,name in zip(data[:,0],data[:,1])]
    
    for xi,yi,text in zip(x,y,annotations):
        plt.annotate(
            text,
            xy=(xi,yi),
            xycoords='data',
            xytext=(1.5,1.5),
            textcoords='offset points'
        )

    plt.show()

def process_spatial_coords(data):
    x=[]    
    y=[]
    z=[]
    for i in range(len(data)):
        x.append(data[i,:][2:-2])
        y.append(data[i,1:][2:-1])
        z.append(data[i,2:][2:])

    x = np.array(x).flatten().astype(float)
    y = np.array(y).flatten().astype(float)
    z = np.array(z).flatten().astype(float)
    
    return x,y,z

def create_spatial_plot(ax,data,x,y,z):
    for i in range(len(data)):
        id = data[i,0]
        name = data[i,1]
        annotation = f"      ID: {id}\n      name: {name}\n      coords: [{x[i]},{y[i]},{z[i]}]"
        ax.text(x[i],y[i],z[i], annotation, size=8, zorder=1, color='k')
    
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    plt.show()


def plot_spatial_hash():
    data = read_file('spatial_data.csv')
    x,y,z = process_spatial_coords(data)

    plt.figure() 
    ax = plt.axes(projection='3d')
    ax.scatter(x, y, z, c=z, cmap='viridis', linewidth=0.5)
    
    create_spatial_plot(ax,data,x,y,z)


def plot_spatial_voxel():
    data = read_file("spatial_data.csv")
    x,y,z = process_spatial_coords(data)

    # determine grid size
    x_shape = int(np.ceil(max(x) + 1))
    y_shape = int(np.ceil(max(y) + 1))
    z_shape = int(np.ceil(max(z) + 1))

    voxel_grid = np.zeros((x_shape,y_shape,z_shape), dtype=bool)

    # add coordinates to grid
    for xi,yi,zi in zip(x,y,z):
        voxel_grid[int(xi),int(yi),int(zi)] = True

    fig = plt.figure()
    ax = fig.add_subplot(projection="3d")
    ax.voxels(voxel_grid, edgecolor="k")

    create_spatial_plot(ax,data,x,y,z)


if __name__ == "__main__":
    plot_hash_data()
    plot_spatial_hash()
    plot_spatial_voxel()


