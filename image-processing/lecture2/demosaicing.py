""" file: demosaicing.py

created on: oct 7 2023
author: nikobk
"""
import cv2 as cv
import numpy as np

# Define the bayer pattern
pattern = np.array([
        [ 100, 10, 110, 11],
        [  9,  50,  8,  49],
        [ 105, 12, 112,  9],
        [  14, 52,  15, 54]
])

# This simply yields: ["b", "g", "b", "g"]
blue_row = ["b", "g"] * 2 
red_row = ["g", "r"] * 2
bayer = np.array([blue_row, red_row] * 2)

# Empty 3d array with an array value of index 3 for each cell.
# This is a empty clone for the image we want to make in RGB.
# Each cell holds a R, G, and B value.
# We will fill it out soon using our bayer pattern equations from the book.
# Keep in mind we use unsigned int (8bit) here because we want to use a range of
# 0 - 255 with unsigned for positive numbers only.
output = np.zeros([3,3,3], dtype=np.uint8)

# Make sure to iterate over the y axis first for correct readorder.
for y, row in enumerate(output):
    for x, pixel in enumerate(row):
        # Equation (3.2) from the book!
        if bayer[y,x] == "b":
            red = pattern[y + 1, x + 1]
            green = pattern[y, x + 1]
            blue = pattern[y, x]
        
        elif bayer[y, x] == 'g' and bayer[y, x + 1] == 'b':
            red = pattern[y + 1, x]
            green = pattern[y, x]
            blue = pattern[y, x - 1]
            
        elif bayer[y, x] == 'g' and bayer[y, x] == 'r':
            red = pattern[y, x + 1]
            green = pattern[y, x]
            blue = pattern[y - 1, x]
            
        elif bayer[y, x] == 'r':
            red = pattern[y, x]
            green = pattern[y, x - 1]
            blue = pattern[y - 1, x - 1]

        output[y, x] = [blue, green, red]

# Show the output.
print(f"Bayer pattern converted to RGB is:\n{output}")