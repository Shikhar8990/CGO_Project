#perf stat -e branches:u,cache-references:u -I 1000 python test_model.py examples/images/cat_gray.jpg &> ll
#perf stat -e branches:u,cache-references:u -I 1000 ./examples/mnist/train_lenet.sh &> stats_branch_cacherefs
#perf stat -e instructions:u,LLC-loads:u -I 1000 ./examples/mnist/train_lenet.sh &> stats_instructions_LLCloads
#perf stat -e LLC-stores:u,LLC-load-misses:u -I 1000 ./examples/mnist/train_lenet.sh &> stats_LLCStores_LLCloadsmisses
#perf stat -e LLC-store-misses:u,L1-dcache-loads:u -I 1000 ./examples/mnist/train_lenet.sh &> stats_LLCStoremisses_dcacheloads
#perf stat -e L1-dcache-stores:u,L1-dcache-load-misses:u -I 1000 ./examples/mnist/train_lenet.sh &> stats_dcachestores_dcacheloads-misses
#perf stat -e branch-misses:u,L1-icache-load-misses:u -I 1000 ./examples/mnist/train_lenet.sh &> stats_brachmisses_icacheloadmisses


perf stat -e instructions:u,cycles:u 			-I 100 ./examples/cifar10/train_quick.sh &> cifar10_train_stats_ipc
perf stat -e branch-misses:u,branches:u 		-I 100 ./examples/cifar10/train_quick.sh &> cifar10_train_stats_branches
perf stat -e LLC-load-misses:u,LLC-loads:u 		-I 100 ./examples/cifar10/train_quick.sh &> cifar10_train_stats_llc
perf stat -e r02c0:u 					-I 100 ./examples/cifar10/train_quick.sh &> cifar10_train_stats_fp
perf stat -e L1-dcache-load-misses:u,L1-dcache-loads:u 	-I 100 ./examples/cifar10/train_quick.sh &> cifar10_train_stats_l1dcaches
echo "Training session complete. Waiting 5 sec.... "
sleep 5
perf stat -e instructions:u,cycles:u 			-I 100 python test_model.py examples/images/cat.jpg &> cifar10_infer_stats_ipc
perf stat -e branch-misses:u,branches:u 		-I 100 python test_model.py examples/images/cat.jpg &> cifar10_infer_stats_branches
perf stat -e LLC-load-misses:u,LLC-loads:u 		-I 100 python test_model.py examples/images/cat.jpg &> cifar10_infer_stats_llc
perf stat -e r02c0:u 					-I 100 python test_model.py examples/images/cat.jpg &> cifar10_infer_stats_fp
perf stat -e L1-dcache-load-misses:u,L1-dcache-loads:u 	-I 100 python test_model.py examples/images/cat.jpg &> cifar10_infer_stats_l1dcaches
echo "inference complete \m/"
