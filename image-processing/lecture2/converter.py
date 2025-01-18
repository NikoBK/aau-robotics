""" file: converter.py

created on: oct 7 2023
author: nikobk
"""
import numpy as np
import cv2 as cv

input = cv.imread("res/cat.jpg")
output = np.zeros(input.shape, dtype=input.dtype)
cv_hsv_img = cv.cvtColor(input, cv.COLOR_BGR2HSV)

for y, row in enumerate(input):
    for x, pixel in enumerate(row):
        hue = 0
        saturation = 0
        value = np.max(pixel)
        if value is not 0:
            saturation = (value - np.min(pixel)) / value
        h_demoniator = value - np.min(pixel)

        # blue, green, red = int(blue), int(green), int(red)
        bgr = [int(a) for a in pixel]
        blue, green, red = bgr

        factor = 60
        if h_demoniator is not 0:
            if value == red and green >= blue:
                hue = (green - blue) / h_demoniator * factor
            elif value == green:
                hue = ((blue - red) / h_demoniator + 2) * factor
            elif value == blue:
                hue = ((red - green) / h_demoniator + 4) * factor
            elif value == red and green < blue:
                hue = ((red - blue) / h_demoniator + 5) * factor
        hue /= 2
        output[y, x] = [hue, saturation, value]

cv.imshow("image | hsv img (custom) | hsv img (opencv)", np.hstack([input, output, cv_hsv_img]))
cv.imshow("hue (custom hsv image)", output[:,:,0])
cv.waitKey(0)
cv.destroyAllWindows()
        