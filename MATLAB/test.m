%% Project
% Tyson Cross   - 1239448
clc; clear all; close all;

timing1 = '../timings.txt';
time_data = timings(timing1, 2, 150);

x = unique(time_data(:,1));
counts = nonzeros(hist(time_data(:,1), x )');
temp = time_data(:,2);

j = 1;
for i = 1:length(counts);
    v = counts(i);
    y(i) = mean(temp(j:j+v-1));
    j = j + v;
end
y = y';


% Draw Plot
runplot

% Export Plot
export_fig ('../Report/images/asymptotic.eps',fig1)