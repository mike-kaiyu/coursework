close all;
Tb1=1; % Bit rate = 1
fs = 8; % Sample rate = fs
dt=Tb1/fs; %increament
N1=8192; %Data bits

t1=0:dt:(Tb1*N1-dt); %Data transmittion time
t2=0:dt:(fs*N1-dt); %oversample
t3=0:dt:(Tb1*N1);
signal_UNI = randi([0 1], fs*N1, 1);
signal_BI = 2*(randi([0 1], Tb1*fs*N1, 1))-1;

rect_pulse_UNI = rectpulse(signal_UNI,fs);
rect_pulse_BI = rectpulse(signal_BI,fs);
figure;
plot(t2, rect_pulse_UNI);
grid on;
axis([0 fs*Tb1*N1 -3 3]);
title('Unipolar signal_UNI in baseband');


noise_index =-29:1:15;
ber_UNI=[];
ber_BI=[];
SNR=[];

for i=1:length(noise_index)
    %noise = wgn(size(rect_pulse_UNI, 1), 1, noise_index(i));
    ber_mix_UNI = awgn(rect_pulse_UNI, noise_index(i), 'measured');
    ber_matched_filter_UNI = ones(fs,1);
    ber_matched_output_UNI = conv(ber_mix_UNI, ber_matched_filter_UNI);
    ber_matched_output1_UNI=[];
    
    ber_mix_BI = awgn(rect_pulse_BI, noise_index(i), 'measured');
    ber_matched_filter_BI = ones(fs,1);
    ber_matched_output_BI_UNI = conv(ber_mix_BI, ber_matched_filter_BI);
    ber_matched_output1_BI=[];
    
    
    for c=1:length(ber_matched_output_UNI)
        ber_matched_output1_UNI(1, c) = ber_matched_output_UNI(c);
    end
    
    ber_matched_output_2_UNI= circshift(ber_matched_output1_UNI, [0,-7]);
    
    output_UNI = downsample(ber_matched_output2_UNI,8);
    
    output_UNI_series=[];
    for j=1:length(output_UNI) %remove delay and define value
        if (output_UNI(j)>4)
            output_UNI_series(j)=1;
        else
            output_UNI_series(j)=0;
        end
    end
    
    e=0;
    for k=1:length(signal_UNI) %remove delay and define value
        if (signal_UNI(k)~=output_UNI_series(k))
            e = e + 1;
        end
    end

    ber_UNI(i) = e/length(output_UNI_series);
    
end

semilogy(noise_index,ber_UNI); %Draw the practical BER vs Eb/No
tBER1=qfunc(sqrt((16./(10.^(noise_index./10))))); %Theoretical BER
hold on;
semilogy(10*log10(4./(10.^(noise_index./10))),(tBER1)); %Draw the theoretical BER vs Eb/No
grid on;
xlim([-5 5]);
ylim([0.001 0.5]);
legend('Practical BER vs Eb/No','Theoretical BER vs Eb/No')
xlabel('Eb/No (/dB)');
ylabel('Bit Error Rate ');
title('Optimum Receiver Performance BER vs. Eb/No');




% figure;
% nfft=2048; %FFT number
% [pxx, f] = pwelch(rect_pulse_UNI, nfft, nfft/2, 'centered','power'); 
% plot(f,10*log10(pxx));  %get PSD
% xlabel('Frequency (/Hz)');
% ylabel('Magnitude (/dB)');
% %axis([-8 8 -30 30]);
% title('Power spectrum density of baseband bipolar signal_UNI');

