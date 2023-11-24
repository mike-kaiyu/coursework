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

MSE=[];
centerNum = 20; %nuber of centers
for c = 1:centerNum
    [temp, centers] = kmeans(train_set, centerNum);

    for i=1: length(train_set) %get trained thate
        for j=1:centerNum
            distance_train = norm(train_set(i,:)-centers(j,:));
            train_theta(i,j)=exp(-distance_train^2/2);
        end
    end
    
    %get the trained weights
    W_trained = inv(train_theta'*train_theta)*train_theta'*train_label;

    %get testing results
    for i=1: size(test_set,1)
        sumUp = ones(centerNum, 1);
        for j=1:centerNum
            distance_test = norm(test_set(i,:)-centers(j,:));
            sumUp(j, 1) = W_trained(j) * exp(-distance_test^2/2);
        end
        fx(i) = sum(sumUp);
    end
    MSE(c)=immse(fx, test_label');  
end

[val, idx] = min(MSE);
c = 1:1:centerNum;
figure;
plot(c, MSE);
title('MSE VS. Number of centers (hidden units)');