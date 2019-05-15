%% Project
% Tyson Cross   - 1239448
clc; clear all; close all;

timing1 = '../timings.txt';
time_data = timings(timing1, 2, 15);

x = time_data(:,1);
y = time_data(:,2)*1e6;


% Draw Plot
runplot

% Export Plot
% export_fig ('../Report/images/asymptotic.eps',fig1)