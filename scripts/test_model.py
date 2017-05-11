import caffe
from PIL import Image
import numpy as np
import cv2
import sys
#import Image
import matplotlib.pyplot as plt

model = 'examples/mnist/lenet.prototxt';
weights = 'examples/mnist/lenet_iter_50.caffemodel';
#model = 'examples/cifar10/cifar10_quick.prototxt';
#weights = 'examples/cifar10/cifar10_quick_iter_5000.caffemodel.h5';
#model = 'examples/siamese/mnist_siamese.prototxt';
#weights = 'examples/siamese/mnist_siamese_iter_5.caffemodel'
#model   = 'models/bvlc_reference_caffenet/deploy.prototxt';
#weights = 'models/bvlc_reference_caffenet/caffenet_train_iter_27.caffemodel';
#model   = 'models/bvlc_alexnet/deploy.prototxt';
#weights = 'models/bvlc_alexnet/caffe_alexnet_train_iter_10.caffemodel';
#model   = 'models/bvlc_googlenet/deploy.prototxt';
#weights = 'models/bvlc_googlenet/bvlc_googlenet_iter_5.caffemodel';
net = caffe.Net(model,weights,caffe.TEST);
caffe.set_mode_cpu()
#img = caffe.io.load_image(sys.argv[1], color=False)
img = cv2.imread(sys.argv[1],0)
if img.shape != [28,28]:
    img2 = cv2.resize(img,(28,28))
    img = img2.reshape(28,28,-1);
else:
    img = img.reshape(28,28,-1);
#revert the image,and normalize it to 0-1 range
img = 1.0 - img/255.0
out = net.forward_all(data=np.asarray([img.transpose(2,0,1)]))

#print out
#print out['prob'][0]
#print out['prob'][0].argmax()
