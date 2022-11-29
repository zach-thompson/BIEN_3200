% Load the ECG and ERGO files
load('ECG.txt');
load('ERGO.txt');

% Store the important data columns in arrays
ecg_1 = ECG(:,2);
ecg_2 = ECG(:,3);
ergo_1 = ERGO(:,2);
ergo_2 = ERGO(:,4);

% Create time vectors for the respective files
t_ecg = 0:1/100:(7.8-1/100);
t_ergo = 0:3:569;

% Plot the ECG on separate graphs
figure
subplot(2,1,1), plot(t_ecg, ecg_1);
title('Healthy ECG Simulation')
ylabel('Voltage (mV)')
xlabel('Time (s)')
subplot(2,1,2), plot(t_ecg, ecg_2);
title('Fibrilation Simulation')
ylabel('Voltage (mV)')
xlabel('Time (s)')

% Plot the ERGO graphs on the same axis
figure
plot(t_ergo, ergo_1, t_ergo, ergo_2)
title('Blood Oxygenation')
ylabel('O_{2} Consumption (L/min)')
xlabel('Time (s)')
lgd = legend({'Test 1','Test 2'},'Location','northwest');

% Calculate and print the minimum and maximum of each column
fprintf("The minimum from the healthy ECG test is: %f\n", min(ecg_1))
fprintf("The maximum from the healthy ECG test is: %f\n\n", max(ecg_1))
fprintf("The minimum from the damaged ECG test is: %f\n", min(ecg_2))
fprintf("The maximum from the damaged ECG test is: %f\n\n", max(ecg_2))
fprintf("The minimum from the first ERGO test is: %f\n", min(ergo_1))
fprintf("The maximum from the first ERGO test is: %f\n\n", max(ergo_1))
fprintf("The minimum from the second ERGO test is: %f\n", min(ergo_2))
fprintf("The maximum from the second ERGO test is %f\n", max(ergo_2))

