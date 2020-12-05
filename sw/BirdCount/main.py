import cv2
import math
import numpy as np
import matplotlib.image as mpimg 
import matplotlib.pyplot as plt 

# Convert rgb image to grayscale
# Formulation: gray = 0.21R + 0.72G + 0.07B
def rgb2gray(img):
    # Already GreyScale
    if(len(img.shape)<3):
        return img
    # Convert to grayscale
    H,W = img.shape[:2]
    gray = np.zeros((H,W), np.uint8)
    for i in range(H):
        for j in range(W):
            gray[i,j] = np.clip(0.07 * img[i,j,0] + 0.72 * img[i,j,1] + 0.21 * img[i,j,2], 0, 255)    
    return gray

# Converts pixel values according to background decision
# Counts zero(0x00) and one(0xFF) pixels in the image
def findBackground(img):
    zeros = 0
    ones = 0
    H,W = img.shape[:2]
    for i in range(H):
        for j in range(W):
            if(img[i,j] == 0):
                zeros += 1
            else:
                ones += 1

    # Convert foreground and background pixels
    if(ones > zeros):
        for i in range(H):
            for j in range(W):
                if(img[i,j] == 0):
                    img[i,j] = 255
                else:
                    img[i,j] = 0

    return img

def kMeansClustering(img):
    threshold = 0
    newThreshold = 128
    counter = 0
    while(abs(threshold - newThreshold) > 0.1):
        threshold = newThreshold
        foregroundSum = 0
        backgroundSum = 0
        foregroundCount = 0
        backgroundCount = 0
        H,W = img.shape[:2]
        for i in range(H):
            for j in range(W):
                pixel = img[i,j]
                if(pixel >= threshold):
                    foregroundCount += 1
                    foregroundSum += pixel
                else:
                    backgroundCount += 1
                    backgroundSum += pixel
        foregroundMean = foregroundSum / foregroundCount
        backgroundMean = backgroundSum / backgroundCount
        #print('Foreground Count:' + str(foregroundCount) + ' Sum:' + str(foregroundSum) + ' Mean:' + str(foregroundMean))
        #print('Background Count:' + str(backgroundCount) + ' Sum:' + str(backgroundSum) + ' Mean:' + str(backgroundMean))
        newThreshold = (foregroundMean + backgroundMean) / 2
    return newThreshold

def thresholding(img, threshold):
    H,W = img.shape[:2]
    for i in range(H):
        for j in range(W):
            if(img[i,j] >= threshold):
                img[i,j] = 255
            else:
                img[i,j] = 0
    return img


print("Finding number of birds in images")

# Read image
image = plt.imread('bird_1.jpg')
plt.subplot(3, 2, 1), plt.imshow(image, 'gray')
plt.title('Original')
plt.xticks([]), plt.yticks([])

# Convert to grayscale
image = rgb2gray(image)
plt.subplot(3, 2, 2), plt.imshow(image, 'gray')
plt.title('Grayscale')
plt.xticks([]), plt.yticks([])

threshold = kMeansClustering(image)
print('Threshold:' + str(threshold))

# Smooting
#image = cv2.GaussianBlur(image, (5,5), 0)

# Thresholding
#image = cv2.adaptiveThreshold(image, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 99, 20)

#ret, image = cv2.threshold(image, threshold, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
#ret, image = cv2.threshold(image, threshold, 255, cv2.THRESH_BINARY)

image = thresholding(image, threshold)
plt.subplot(3, 2, 3), plt.imshow(image, 'gray')
plt.title('Thresholding')
plt.xticks([]), plt.yticks([])



image = findBackground(image)
plt.subplot(3, 2, 4), plt.imshow(image, 'gray')
plt.title('Background Correction')
plt.xticks([]), plt.yticks([])

# Dilation and Erosian
#kernel = np.ones((5,5), np.uint8)
#image = cv2.dilate(image, kernel, iterations=1)
#image = cv2.erode(image, kernel, iterations=1)


# noise removal
kernel = np.ones((3,3), np.uint8)
image = cv2.morphologyEx(image, cv2.MORPH_OPEN, kernel, iterations = 1)

plt.subplot(3, 2, 5), plt.imshow(image, 'gray')
plt.title('Opening')
plt.xticks([]), plt.yticks([])


# clean all noise after dilatation and erosion
#imgMedian = cv2.medianBlur(image, 7)


ret, labels = cv2.connectedComponents(image)
labelHue = np.uint8(179 * labels / np.max(labels))
blankChannel = 255 * np.ones_like(labelHue)
image = cv2.merge([labelHue, blankChannel, blankChannel])
image = cv2.cvtColor(image, cv2.COLOR_HSV2BGR)
image[labelHue == 0] = 0

plt.subplot(3, 2, 6), plt.imshow(image, 'gray')
plt.title('Result' + str(ret-1))
plt.xticks([]), plt.yticks([])

plt.savefig('result.jpg')
plt.show()
