############################################################# 
# Firing Performance Measurement for                        #
# Remote Controlled Machine Gun Platform                    #
#                                                           #
# BLG 513E Image Processing Project                         #
#                                                           #
# Copyright (C)  Mehmet AKTAS 0504181576                    #
#                                                           #
#############################################################
from skimage.metrics import structural_similarity
import cv2
import math
import numpy as np
import matplotlib.image as mpimg 
import matplotlib.pyplot as plt 

print("Firing Performance Measurement for Remote Controlled Machine Gun Platform")

fileName = 'DataSet/Fire0.png'
imageBackground = plt.imread(fileName)
grayBackground = cv2.cvtColor(imageBackground, cv2.COLOR_BGR2GRAY)

fileName = 'DataSet/Fire1.png'
imageFire = plt.imread(fileName)
grayFire = cv2.cvtColor(imageFire, cv2.COLOR_BGR2GRAY)

(score, diff) = structural_similarity(grayBackground, grayFire, gaussian_weights=True, full=True, sigma=1)
print("Image similarity:", score)

# The diff image contains the actual image differences between the two images
# and is represented as a floating point data type in the range [0,1] 
# so we must convert the array to 8-bit unsigned integers in the range
# [0,255] before we can use it with OpenCV
diff = (diff * 255).astype("uint8")

#diff = cv2.medianBlur(diff, 7)

# Threshold the difference image, followed by finding contours to
# obtain the regions of the two input images that differ
thresh = cv2.threshold(diff, 20, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
#thresh = cv2.adaptiveThreshold(diff, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 111, 3)

# To filling circles
kernel = np.ones((3,3), np.uint8)
closing = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel)

#erosion = cv2.erode(thresh, kernel, iterations = 2)
#dilation = cv2.dilate(thresh, kernel, iterations = 2)

#cv2.imshow('diff', diff)
#cv2.imshow('thresh', thresh)
#cv2.imshow('closing', closing)
#cv2.imshow('erosion', erosion)
#cv2.imshow('dilation', dilation)


# Apply Hough transform on the blurred image. 
detected_circles = cv2.HoughCircles(closing, cv2.HOUGH_GRADIENT, 1, 6, param1 = 30, param2 = 7, minRadius = 0, maxRadius = 8) 
print("detected_circles:", detected_circles)

# Draw circles that are detected. 
if detected_circles is not None: 
  
    # Convert the circle parameters a, b and r to integers. 
    detected_circles = np.uint16(np.around(detected_circles)) 
  
    for pt in detected_circles[0, :]: 
        a, b, r = pt[0], pt[1], pt[2] 
  
        # Draw the circumference of the circle. 
        cv2.circle(imageFire, (a, b), r, (0, 255, 0), 2) 
  
        # Draw a small circle (of radius 1) to show the center. 
        cv2.circle(imageFire, (a, b), 1, (0, 0, 255), 3) 

cv2.imshow("Detected Circle", imageFire) 
cv2.waitKey(0) 


contours = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
contours = contours[0] if len(contours) == 2 else contours[1]

mask = np.zeros(imageBackground.shape, dtype='uint8')
filled_after = imageFire.copy()

for c in contours:
    area = cv2.contourArea(c)
    if area > 40:
        x,y,w,h = cv2.boundingRect(c)
        cv2.rectangle(imageBackground, (x, y), (x + w, y + h), (36,255,12), 2)
        cv2.rectangle(imageFire, (x, y), (x + w, y + h), (36,255,12), 2)
        cv2.drawContours(mask, [c], 0, (0,255,0), -1)
        cv2.drawContours(filled_after, [c], 0, (0,255,0), -1)

cv2.imwrite('DataSet/Result.png', diff) 
#cv2.imshow('mask', mask)

#cv2.imshow('before', imageBackground)
#cv2.imshow('after', imageFire)
#cv2.imshow('diff', diff)
#cv2.imshow('mask', mask)
#cv2.imshow('filled after', filled_after)
cv2.waitKey(0)

# Displays image
plt.subplot(2, 2, 1), plt.imshow(imageFire, 'gray'), plt.title('Original'), plt.xticks([]), plt.yticks([])


# Displays image
plt.subplot(2, 2, 2), plt.imshow(grayFire, 'gray'), plt.title('Gray'), plt.xticks([]), plt.yticks([])

rows,cols = grayFire.shape

pointsSource = np.float32([[197,60],[1586,82],[1403, 992],[379,996]])
pointsDestination = np.float32([[197,60],[1586,60],[1586, 1450],[197,1450]])

M = cv2.getPerspectiveTransform(pointsSource, pointsDestination)

transformed = np.zeros((1600,1600), np.uint8)
dst = cv2.warpPerspective(grayFire, M, transformed.shape)

# Displays image
plt.subplot(2, 2, 3), plt.imshow(dst, 'gray'), plt.title('Dest'), plt.xticks([]), plt.yticks([])


# Displays subplotted images
# plt.show()
