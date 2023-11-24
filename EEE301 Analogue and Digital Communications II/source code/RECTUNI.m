close all;
Tb1=1; % bit duration
fs = 8; % sampling rate
dt=Tb1/fs; %increament
N1=8192; %number of data bits

t1=0:dt:(Tb1*N1-dt);
t2=0:dt:(fs*N1-dt); 
t3=0:dt:(Tb1*N1);
signal = randi([0 1], fs*N1, 1); %generate discrete bit 0 or 1.

rect_pulse = rectpulse(signal,fs); %pulse shaping and oversampling.
figure;
plot(t2, rect_pulse);%plot baseband signal waveform in time domain.
grid on;
axis([0 fs*Tb1*N1 -3 3]);
title('Unipolar signal in rectangular pulse shaping in baseband');

% example_mix=awgn(rect_pulse, 20); %example: adding noise which is 20dB. 
% figure; %baseband signal waveform in time domain.
% plot(t2, rect_pulse);
% hold on;
% plot(t2, example_mix);
% grid on;
% axis([0 fs*Tb1*N1 -3 3]);
% title('Unipolar signal with AWGN in rectangular pulse shaping in baseband');
% legend('Without AGWN','With AGWN');

noise_index =-39:1:26; %noise in dB, it is from -80~52. 
ber=[];%for storing every ber when noise_index varies

for i=1:length(noise_index) %obtain a series of ber when noise_index varies
    noise = wgn(size(rect_pulse, 1), 1, noise_index(i));
    ber_mix = awgn(rect_pulse, noise_index(i), 'measured');%adding noise
    ber_matched_filter = ones(fs,1); %initialize matched filter
    ber_matched_output = conv(ber_mix, ber_matched_filter); %convolution of signal with noise and matched filter
    ber_matched_output1=[]; % initialize the ber_matched_output1
    
    for c=1:length(ber_matched_output) %transposition
        ber_matched_output1(1, c) = ber_matched_output(c);
    end
    
    ber_matched_output2= circshift(ber_matched_output1, [0,-7]); %remove delay
    
    output = downsample(ber_matched_output2,8); %downsample 
    
    output_series=[];% used for storing recovered digits
    for j=1:length(output) 
        if (output(j)>4) %threshold is 4
            output_series(j)=1;
        else
            output_series(j)=0;
        end
    end
    
    e=0;
    for k=1:length(signal) %calculate number of error
        if (signal(k)~=output_series(k))
            e = e + 1;
        end
    end

    ber(i) = e/length(output_series); %calculate BER
    
end

semilogy(noise_index,ber); %plot practical BER vs Eb/No and theoretical BER vs Eb/No
tBER1=qfunc(sqrt((4./(10.^(noise_index./10))))); 
hold on;
semilogy(10*log10(4./(10.^(noise_index./10))),(tBER1)); 
grid on;
xlim([-10 8]);
ylim([0.0001 1]);
legend('Practical BER vs Eb/No','Theoretical BER vs Eb/No')
xlabel('Eb/No (/dB)');
ylabel('Bit Error Rate ');
title('Optimum Receiver Performance BER vs. Eb/No');

% figure;
% nfft=2^15; %number of FFT
% [pxx, f] = pwelch(rect_pulse, nfft, nfft/2, 'centered','power'); 
% plot(f,10*log10(pxx));  %plot power spectrum density
% xlabel('Frequency (/Hz)');
% ylabel('Magnitude (/dB)');
% %axis([-8 8 -30 30]);
% title('Power spectrum density of baseband unipolar signal in rectangular pulse.');