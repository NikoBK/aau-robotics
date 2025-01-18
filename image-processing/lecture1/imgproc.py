import cv2 as cv

tinypic = cv.imread("tinypic.png", 0)
colors = []
output = ""

for y in range(3):
    for x in range(3):
        print(f"Pixel at: ({x}, {y}) is: {tinypic[x,y]}.")
        output += str(tinypic[y,x]) + " " # Über scuff by Adrian & Nikolaj.

print(f"Correct output: {output}")
cv.imshow("Our window", tinypic)
cv.waitKey(0)