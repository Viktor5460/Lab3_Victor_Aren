import os
import matplotlib.pyplot as plt

# Set the initial iteration number
i = 1

# Loop through the iteration files until no more files are found
while True:
    # Construct the filename
    filename = f'iteration_{i}.txt'
    
    # Check if the file exists
    if not os.path.isfile(filename):
        break  # Exit the loop if the file does not exist

    # Read the data from the file
    c1 = []
    c2 = []
    with open(filename, 'r') as file:
        for line in file.readlines():
            t = line.split()
            c1.append(int(t[0]))  # Read the first column
            c2.append(int(t[1]))  # Read the second column

    # Create a bar chart
    plt.bar(c1, c2)
    plt.xlabel('Index')
    plt.ylabel('Value')
    plt.title(f'Bar chart for {filename}')
    
    # Save the figure as an image
    plt.savefig(f'iteration_{i}.png', dpi=400)
    plt.close()  # Close the figure to free memory

    # Move to the next iteration
    i += 1

print("Graphs have been generated and saved.")
