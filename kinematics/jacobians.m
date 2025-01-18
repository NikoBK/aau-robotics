% Name:     jacobians.m
% Created:  07/17/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Jacobian
% The usage of syms is for MATLAB to allow undefined variables.
syms x y z L1 d2 theta theta2 e

% Usage:
% jacobian([Your functions], [var's to diff. in relation to])
%
% Constructor:
% elem1 = x^3 * y^2 - 5 * x^2 * y^2;
% elem2 = y^6 - 3 * y^3 * x + 7;
% jacboian([elem1, elem2], [x, y, z]) 

jacobian([ ...
    L1 * cos(theta) + d2 * sin(theta), ...
    L1 * sin(theta) - d2 * cos(theta), ...
    theta - theta2 ...
    ], ...
    [ theta, d2, theta2])