#! /bin/bash
./examples/mnist/train_lenet.sh
/home/shikhar/pin-3.2-81205-gcc-linux/pin -t /home/shikhar/pin-3.2-81205-gcc-linux/source/tools/ManualExamples/obj-intel64/inscount0.so -- pgrep caffe
