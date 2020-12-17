############################################################# 
# Firing Performance Measurement for                        #
# Remote Controlled Machine Gun Platform                    #
#                                                           #
# BLG 513E Image Processing Project                         #
#                                                           #
# Copyright (C)  Mehmet AKTAS 0504181576                    #
#                                                           #
#############################################################
import cv2
import math
import numpy as np
import matplotlib.image as mpimg 
import matplotlib.pyplot as plt 

print("Firing Performance Measurement for Remote Controlled Machine Gun Platform")

fileName = 'DataSet/03.png'
image = plt.imread(fileName)

# Displays image
plt.subplot(2, 2, 1), plt.imshow(image, 'gray'), plt.title('Original'), plt.xticks([]), plt.yticks([])

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Displays image
plt.subplot(2, 2, 2), plt.imshow(gray, 'gray'), plt.title('Gray'), plt.xticks([]), plt.yticks([])

rows,cols = gray.shape

pointsSource = np.float32([[197,60],[1586,82],[1403, 992],[379,996]])
pointsDestination = np.float32([[197,60],[1586,60],[1586, 1450],[197,1450]])

M = cv2.getPerspectiveTransform(pointsSource, pointsDestination)

offsetSize = 500
transformed = np.zeros((1600,1600), np.uint8)
dst = cv2.warpPerspective(gray, M, transformed.shape)

# Displays image
plt.subplot(2, 2, 3), plt.imshow(dst, 'gray'), plt.title('Dest'), plt.xticks([]), plt.yticks([])


# Displays subplotted images
plt.show()
