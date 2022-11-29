%% Computer Apps Final
% Load data and plot all

data = load('EEG_Data.csv');

for n = 1:5
data_n = data(n,:);
subplot(5, 1, n), plot(data_n);
end

%% Calculate number of zero-crossings. High count = awake
num_cross = zeros(50, 1);

for row = 1:50
    count = 0;
    for col = 1:2999
       if (data(row, col) > 0 && data(row, col + 1) < 0) ||  (data(row, col) < 0 && data(row, col + 1) > 0)
          count = count + 1;
       end
    end
    num_cross(row, 1) = count;
end
