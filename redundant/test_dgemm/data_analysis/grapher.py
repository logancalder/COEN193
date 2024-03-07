import matplotlib.pyplot as plt

# Reading first file
with open('data/Dgemm_Sq_Data_32Gmem.txt', 'r') as file:
    file_1 = file.readlines()

# Reading second file
with open('data/Dgemm_Sq_Data_GPU.txt', 'r') as file:
    file_2 = file.readlines()

# Processing first file data
labels_file_1 = [item.split("x")[0] for item in file_1]
coordinates_file_1 = [item.split("x")[1].split(",") for item in file_1]
x_values_file_1 = [float(coord[0]) for coord in coordinates_file_1]
y_values_file_1 = [float(coord[1]) for coord in coordinates_file_1]

# Processing second file data
labels_file_2 = [item.split("x")[0] for item in file_2]
coordinates_file_2 = [item.split("x")[1].split(",") for item in file_2]
x_values_file_2 = [float(coord[0]) for coord in coordinates_file_2]
y_values_file_2 = [float(coord[1]) for coord in coordinates_file_2]

# Plotting points
plt.scatter(x_values_file_2, y_values_file_2, label='6x8GB GPU', color='red', marker='o')
plt.scatter(x_values_file_1, y_values_file_1, label='4x8GB CPU', color='blue', marker='o')

# Customize the plot
plt.title('Dgemm Runtime Data of 4x8GB CPU vs 6x8GB GPU')
plt.xlabel('Sq Matrix Size')
plt.ylabel('Runtime (ms)')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()
