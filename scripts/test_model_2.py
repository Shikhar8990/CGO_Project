import caffe
from PIL import Image
import numpy as np
import cv2
import sys
#import Image
import matplotlib.pyplot as plt

model = 'examples/siamese/mnist_siamese.prototxt';
weights = 'examples/siamese/mnist_siamese_iter_5000.caffemodel'
net = caffe.Net(model,weights,caffe.TEST);
caffe.set_mode_cpu()
img=np.load('test.jpg.npy')
print "here"
out = net.forward_all(data=np.asarray([img.transpose(2,0,1)]))

print out
#print out['prob'][0]
#print out['prob'][0].argmax()
