close all;
clear;
load('logo.mat')
a = 1;
b = 2; 
c = 3;
d = 4;
e = 5;

logo1_train_sam = eohsamples(1:10,1:80);
logo2_train_sam = eohsamples(13:28,1:80);
logo3_train_sam = eohsamples(33:54,1:80);
logo4_train_sam = eohsamples(61:78,1:80);
logo5_train_sam = eohsamples(83:110,1:80);
train_set=[logo1_train_sam; logo2_train_sam; logo3_train_sam; logo4_train_sam; logo5_train_sam];
train_label = [eohlabels(1:10,1); eohlabels(13:28,1); eohlabels(33:54,1); eohlabels(61:78,1); eohlabels(83:110,1)];

logo1_test_sam = eohsamples(11:12,1:80);
logo2_test_sam = eohsamples(29:32,1:80);
logo3_test_sam = eohsamples(55:60,1:80);
logo4_test_sam = eohsamples(79:83,1:80);
logo5_test_sam = eohsamples(110:117,1:80);
test_set = [logo1_test_sam; logo2_test_sam; logo3_test_sam; logo4_test_sam; logo5_test_sam];
test_label = [eohlabels(11:12,1); eohlabels(29:32,1); eohlabels(55:60,1); eohlabels(79:83,1); eohlabels(110:117,1)];

MSE_train=[];
MSE_test=[];
unit_hidden1 = 3;
learning_rate=0.01:0.01:1;
for i=1:length(learning_rate)
    net = newff(train_set', train_label', unit_hidden1, {'logsig','tansig'},'traingdm');
    net.trainParam.epochs=100;
    net.trainParam.lr=learning_rate(i);
    net.trainParam.mc=0.01;
    net = setwb(net,zeros(1,net.numWeightElements));
    net.divideParam.trainRatio = 1;
    net.divideParam.valRatio = 0;
    net.divideParam.testRatio = 0;
    [net,tr,Y] = train(net,train_set', train_label');
    MSE_train(i) = mse(net, train_label', Y);
end

%view(net);
[val, idx_train] = min(MSE_train);
figure;
plot(learning_rate, MSE_train);
title('MSE VS. Learning Rate');
