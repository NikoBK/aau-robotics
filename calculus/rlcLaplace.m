% Name:     rlcLaplace.m
% Created:  6/15/2023
% Author:   nikobk

% ABOUT
% text

% Clear cache and console.
clear; clc; close all;

% Parameters
I0 = 0.8;
IPrime0 = 2.5;
tmin = 0;
tmax = 15;
omega0 = 2.5;

% Numeric calculation tolerance
options = odeset('AbsTol', 1e-6, "'RelTol", 1e-4);

% The three different choices for zeta are denoted zeta1, zeta2 and zeta3
% for different solutions.
zeta1 = 1;
zeta2 = 2;
zeta3 = 3;

[t, y] = ode45(@(t, y) gg(t, y, zeta1, omega0), [0 tmax], [I0; Iprime0], options);
[tt, z] = ode45(@(t, y) gg(t, y, zeta2, omega0), [0 tmax], [I0; Iprime0], options);
[s, w] = ode45(@(t, y) gg(t, y, zeta3, omega0), [0 tmax], [I0; Iprime0], options);

figure
plot(t, y(:, 1), '-r', tt, z(:, 1), '-b', s, w(:, 1), '-k', 'LineWidth', 1.5);

legend(strcat('\zeta= ', num2str(zeta1)),...
       strcat('\zeta= ', num2str(zeta2)),...
       strcat('\zeta= ', num2str(zeta3)) ...
);

% The parameters zeta and omega should be constructed in the usage of
% ode45.
function dydt = getDiff(t, y, zeta, omega)
    dydt = zero(2, 1);
    dydt(1) = y(2);
    dydt(2) = -2 * zeta * omega * y(2) - omega^2 * y(1);
end