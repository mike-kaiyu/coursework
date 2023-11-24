close all;
Tb1=1; % bit duration
fs = 8; % sampling rate
dt=Tb1/fs; %increament
N1=8192; %number of data bits

t1=0:dt:(Tb1*N1-dt); 
t2=0:dt:(fs*Tb1*N1-dt); 
signal = randi([0 1], Tb1*fs*N1, 1); %generate discrete bit 0 or 1.

rolloff = 1; %Roll-off
span = 8;  %Filter span
sps = 8; %Samples per symbol

RRC_filter = rcosdesign(rolloff, span, fs,'sqrt'); %RRC filter
RRC_pulse = upfirdn(signal, RRC_filter, sps); % oversample

t3=0:1:size(RRC_pulse, 1)-1; 
figure;
plot(t3, RRC_pulse);%plot baseband signal waveform in time domain.
grid on;
axis([0 1100 -0.3 0.6]);
title('Unipolar signal in RRC pulse shaping in baseband');

% example_mix=awgn(RRC_pulse, 20);%example: adding noise which is 20dB. 
% figure;
% plot(t3, RRC_pulse);%baseband signal waveform in time domain.
% hold on;
% plot(t3, example_mix);
% grid on;
% axis([0 1100 -0.6 0.8]);
% title('Unipolar signal with AWGN in RRC pulse shaping in baseband');
% legend('Without AGWN','With AGWN');

noise_index =-39:1:26;%noise in dB, it is from -39~26.
ber=[];%for storing every ber when noise_index varies
SNR=[];

for i=1:length(noise_index)%for storing every ber when noise_index varies
    %noise = wgn(size(RRC_pulse, 1), 1, noise_index(i));
    SNR = noise_index(i)- 10*log10(sps); % real SNR
    ber_mix = awgn(RRC_pulse, SNR, 'measured');%adding noise
    output_filter = upfirdn(ber_mix, RRC_filter, 1, sps);%convolution of signal with noise and matched filter and downsample
    output_filter = output_filter(span+1:end-span); % remove delay

    output_series=[];
    for j=1:length(signal) % used for storing recovered digits
        if (output_filter(j)>0.5)%threshold is 0.5
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

    ber(i) = e/length(output_series);
    
end

semilogy(noise_index,ber);%plot practical BER vs Eb/No and theoretical BER vs Eb/No
tBER1=qfunc(sqrt((0.5./(2.*10.^(noise_index./10)))));
hold on;
semilogy(10*log10(0.5./(2.*10.^(noise_index./10))),(tBER1)); 
grid on;
xlim([-20 50]);
ylim([0.01 5]);
legend('Practical BER vs Eb/No','Theoretical BER vs Eb/No')
xlabel('Eb/No (/dB)');
ylabel('Bit Error Rate ');
title('Optimum Receiver Performance BER vs. Eb/No');

% figure;
% nfft=2^15; %number of FFT
% [pxx, f] = pwelch(RRC_pulse, [], nfft/2, 'centered','power'); 
% plot(f,10*log10(pxx));  %plot power spectrum density
% xlabel('Frequency (/Hz)');
% ylabel('Magnitude (/dB)');
% %axis([-8 8 -30 30]);
% title('Power spectrum density of baseband unipolar signal in RRC');