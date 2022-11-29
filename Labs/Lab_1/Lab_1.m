% Using import function, load data into an array

data1 = readtable('cardio_dataset.txt');

Mean = mean(data1{:,:}) % Outputs the mean of each column
Median = median(data1{:,:}) % Outputs the median of each column
Mode = mode(data1{:,:}) % Outputs the mode of each column
Stddev = std(data1{:,:}) % Outputs the standard deviation of each column
Variance = var(data1{:,:}) % Outputs the variance of each column
Skew = skewness(data1{:,:})  % Outputs the skewness of each column


