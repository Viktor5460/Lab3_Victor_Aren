
import os

i = 1

# Open the file_list.txt in write mode
with open('file_list.txt', 'w') as file_list:
    while True:
        # Construct the filename
        filename = f'iteration_{i}.png'

        # Check if the file exists
        if not os.path.isfile(filename):
            break  # Exit the loop if the file does not exist

        # Write the filename to file_list.txt with a new line
        #file_list.write(f'file \'/home/vips/lab3/gitproject/Lab3_Victor_Aren/1_bubble/testik_1/{filename}\'\n')
        file_list.write(f'file \'{filename}\'\nduration 0.05\n')
        
        # Increment i for the next iteration
        i += 1
