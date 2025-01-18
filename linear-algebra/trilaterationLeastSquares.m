% Name:     trilaterationLeastSquares.m
% Created:  6/15/2023
% Author:   nikobk

% ABOUT
% Find the least squares solution (u) for the equation:
% Xy = vHat so that ||v - vHat||^2 is minimized.

% Clear cache and console.
clear; clc; close all;

% Placeholder, replace this with values.
PLACEHOLDER = 10;

% Seed for better randomness
seed = 9;

if mod(N,1) ~= 0 || N < 3 || p < 0 || q < 0 || q > 1
    error('N must be a whole number of N >= 3. p >= 0 og 0 <= q < 1.');
end

x = [0.3; 0.1]; % Correct position. 
rand('seed', 12)
pos = zeros(N, 2);
pos = [[0; 0], 2 * rand(2, N - 1) -1]';
r = sqrt((pos(:, 1) - x(1)).^2 + (pos(:, 2) - x(2)).^2);

% Equally divided random errors on positions and distances.
rand('seed', seed   )
eta = (2 * rand(2, N - 1) - 1)';
posfejl = [pos(1, :); pos(2:end, :) + p * eta./sqrt(eta(:, 1).^2 + eta(:, 2).^2)];
rand('seed', seed + 1)
tau = rand(N, 1);
rfejl = r;
rfejl(tau <= 0.5) = (1 - q) * rfejl(tau <= 0.5);
rfejl(tau > 0.5) = (1 + q) * rfejl(tau > 0.5);

% Solving the system of equations.
A = posfejl(2:end, :);
v = 0.5 * (r(1).^2 - rfejl(2:end).^2  + posfejl(2:end,1).^2 + posfejl(2:end,2).^2);
x_ls = A\v;
abserr = norm(x - x_ls, 2);   % Absolute error.

% Plots and more.
display(['Absolut fejl: ',num2str(abserr)]);

hf = figure;
hold on;
axis equal;
xlim([-1 - p, 1 + p]);
ylim([-1 - p, 1 + p]);
for j = 2:N
    h = plot([posfejl(j, 1), pos(j, 1)], [posfejl(j, 2), pos(j, 2)], 'b-');
end
h2 = plot(pos(:, 1), pos(:, 2), 'b.', 'markersize', 15);
h3 = plot(x(1), x(2), 'rx', 'markersize', 7);
h4 = plot(x_ls(1), x_ls(2), 'go', 'markersize', 7);
hl = legend([h, h2, h3, h4], {'Fejlagtige positioner af sensorer','Faktiske positioner af sensorer','Korrekt position x','Mindste kvadraters løsning'},'location','southoutside');