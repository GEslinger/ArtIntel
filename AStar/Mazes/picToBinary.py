import cv2
import numpy as np
import sys

if __name__ == "__main__":
	img = cv2.imread("small.png")[...,1] / 255

	for row in img:
		for px in row:
			sys.stdout.write('%d' % px)
		sys.stdout.write('\n')
