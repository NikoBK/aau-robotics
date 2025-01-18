% Name:     parabolicBlends.m
% Created:  07/17/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Parabolic Blend
%Remember when plotting piecewise function to set interval. 
% This way the plot opens up showing the whole function
%fplot(pw(t),[0 t_f])

theta0 = 0;
theta_f = 0;
a = 0;
t_f = 0;
% pw = 0;

syms t
t_b = round((t_f/2 - sqrt(a^2 * (t_f)^2 - 4*a*(theta_f - theta0))/(2*a)),2);
theta_b = round((1/2 * a * (t_b)^2 + theta0),2);

ParaBlend_Accel = theta0 + 1/2 * a * t^2;
ParaBlend_MaxVel = theta_b + a * t_b * (t-t_b);
ParaBlend_Decel = theta_f - 1/2 * a * (t_f-t)^2;

pw = piecewise((t >= 0)&(t <= t_b), ParaBlend_Accel, (t >= t_b)&(t <= t_f-t_b), ParaBlend_MaxVel, (t >= t_f-t_b)&(t <= t_f), ParaBlend_Decel);