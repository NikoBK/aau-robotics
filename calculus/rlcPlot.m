% Name:     rlcPlot.m
% Created:  6/15/2023
% Author:   nikobk

% ABOUT
% A script for plotting power throughout a RLC circuit, where the power is
% denoted with I(t), with t being time. The startvalues are denoted I(0) =
% I0 and I'(0) = Iprimezero.
% The plots are the results from time tmin to tmax.

% Clear cache and console.
clear; clc; close all;

% Parameters
I0 = -1;
Iprme0 = 5;
tmin = 0;
tmax = 20;

% Numeric calculation tolerance
options = odeset('AbsTol', 1e-6, "'RelTol", 1e-4);

% The differential equations with two different start values is solved and
% plotted as well as the exact solution for a random task. The solution
% with the given start values is highlighted red the one with start values
% 0, 0 is blue and the analytical solution is black.

[t, y] = ode45(@diffParams, [0 tmax], [I0; Iprime0], options);
[x, z] = ode45(@diffParams, [0 tmax], [0; 0], options);
plot(t, y(:,1), '-r', x, z(:,1), '--b', 'LineWidth', 1);

hold on
I = @(s) sin(2.*s) / 4 - sqrt(3) * exp(-s).*sin(sqrt(3).*s) / 6;
fplot(I, [0 tmax], '-.k', 'LineWidth', 1);
hold off

% The absolute value of the difference can be plotted to see the change
% between the analytical and calculated solution.
figure
plot(x, abs(I(x) - z(:,1)))

% Differential equations
function dydt = diffParams(t, y)
    dydt = zero(2, 1);
    dydt(1) = y(2);
    dydt(2) = -4 * y(1) - 2 * y(2) + cos(2 * t);
end