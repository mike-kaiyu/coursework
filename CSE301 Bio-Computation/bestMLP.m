close all;
clear;
load('logo.mat')
a = 1;
b = 2; 
c = 3;
d = 4;
e = 5;

%set first 80% of data set as training set.
logo1_train_sam = eohsamples(1:10,1:80);
logo2_train_sam = eohsamples(13:28,1:80);
logo3_train_sam = eohsamples(33:54,1:80);
logo4_train_sam = eohsamples(61:78,1:80);
logo5_train_sam = eohsamples(83:110,1:80);
train_set=[logo1_train_sam; logo2_train_sam; logo3_train_sam; logo4_train_sam; logo5_train_sam];
train_label = [eohlabels(1:10,1); eohlabels(13:28,1); eohlabels(33:54,1); eohlabels(61:78,1); eohlabels(83:110,1)];

%set last 20% of data set as training set.
logo1_test_sam = eohsamples(11:12,1:80);
logo2_test_sam = eohsamples(29:32,1:80);
logo3_test_sam = eohsamples(55:60,1:80);
logo4_test_sam = eohsamples(79:83,1:80);
logo5_test_sam = eohsamples(110:117,1:80);
test_set = [logo1_test_sam; logo2_test_sam; logo3_test_sam; logo4_test_sam; logo5_test_sam];
test_label = [eohlabels(11:12,1); eohlabels(29:32,1); eohlabels(55:60,1); eohlabels(79:83,1); eohlabels(110:117,1)];

MSE_train=[];

unit_hidden1 = 3;

net = newff(train_set', train_label', unit_hidden1, {'logsig','tansig'},'traingdm');%build BP nrural network
net.trainParam.epochs=100;
net.trainParam.lr=0.11;%learning rate
net.trainParam.mc=0.116;%momentum
net = setwb(net,zeros(1,net.numWeightElements));%initialize weights and biases to 0.
%display(net.numWeightElements);
net.divideParam.trainRatio = 1;
net.divideParam.valRatio = 0;
net.divideParam.testRatio = 0;
[net,tr,Y] = train(net,train_set', train_label');%train net
MSE_train = mse(net, train_label', Y); %obtain mse

%https://www.mathworks.com/matlabcentral/answers/338244-how-can-i-plot-a-confusion-matrix-for-a-multi-class-or-non-binary-classification-problem
output = sim(net, test_set');
targetsVector = test_label'; % Class for target
outputsVector = output; % Class for prediction
targets = zeros(5,25);
outputs = zeros(5,25);
targetsIdx = sub2ind(size(targets), targetsVector, 1:25);
outputsIdx = sub2ind(size(outputs), round(outputsVector), 1:25);
targets(targetsIdx) = 1;
outputs(outputsIdx) = 1;
% Plot confuse matrix
plotconfusion(targets,outputs);
h = gca;
%labels
h.XTickLabel = {'Logo 1','Logo 2', 'Logo 3','Logo 4', 'Logo 5','Total Accuracy'};
h.YTickLabel = {'Logo 1','Logo 2', 'Logo 3','Logo 4', 'Logo 5','Total Accuracy'};
h.YTickLabelRotation = 90;
