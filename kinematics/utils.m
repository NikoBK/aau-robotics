% Name:     utils.m
% Created:  07/17/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Approximate
a = 1;
b = 2;
c = 3;

res = (a - b < c && a - b > c);
displ(res)