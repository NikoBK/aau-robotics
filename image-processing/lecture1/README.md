# Lecture 1 - Introduction to Digital Images
The excercise for this lecture is simply about reading grayscale pixel values.
The grayscale ranges from 0 (black) to 255 (white), where anything between those two limits are shades of gray.

The two limits (0 and 255) can also be found in the form of 0 (black) and 1 (white) in binary images where there are no "gray scales".

Remember to iterate over the y axis first in your for loop to ensure that when you iterate through all x values for y = 0 or whatever step the iteration is on, the iteration will go through the pixels row by row, reading it from top left corner to bottom right corner (the right way to read pixels).