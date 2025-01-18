% Name:     cubicPolynomials.m
% Created:  07/17/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Cubic Polynomial (Craig)
clear; close all; clc;

% Cubic polynominals
% - p. 225 Craig
% - eq. 7.1 -> 7.6

% syms t
t = sym('t', [1,1])

% theta0 = Initial angle/position
% thetaF = Final angle/position
% tF = Total time to do operation
theta0 = [70, 90, -150];
thetaF = [35, 90, 120];
tF = 32;

% Calculating values for the cubic polynomial
a0 = theta0;
a1 = 0;
a2 = (3/(tF^2))*(thetaF-theta0);
a3 = (-2/(tF^3))*(thetaF-theta0);

% Calculating the cubic polynomial
theta(t) = a0 + a1 * t + a2 * (t^2) + a3 * (t^3);

CP = theta(t);
aValues = [a0, a1, a2, a3];

%% Cubic Polynomial (Craig), w/ Via Points
% Cubic polynominals with viapoints
% - p. 227 Craig
% - eq. 7.9 -> 7.14

syms t

% theta0 = Initial angle/position
% thetaF = Final angle/position
% dotTheta0 = Initial velocity
% dotThetaF = Final velocity
% tF = total time to do operation
theta0 = 0;
thetaF = 0;
dotTheta0 = 0;
dotThetaF = 0;
tF = 0;
currentTimeElapsed = 0;

% Calculating values for the cubic polynomial
a0 = theta0;
a1 = dotTheta0;
a2 = (3 / tF^2) * (thetaF - theta0) - (2 / tF) * dotTheta0 - (1/tF) * dotThetaF;
a3 = (-2 / tF^3) * (thetaF - theta0) + (1 / tF^2) * (dotThetaF + dotTheta0);

% Calculating the cubic polynomial
theta(t) = a0 + a1 * (t - currentTimeElapsed) + a2 * (t - currentTimeElapsed)^2 + a3*(t - currentTimeElapsed)^3;

CP = theta(t);
aValues = [a0, a1, a2, a3];
