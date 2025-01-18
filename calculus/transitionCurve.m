% Name:     transitionCurve.m
% Created:  6/15/2023
% Author:   nikobk

% ABOUT
% This script is designed to be used for transition curves represent a
% mobile robot's path around an obstacle with a predefined linear path that
% will then transition along the curve of a circle until the obstacle is no
% longer in range of the robot.

% Clear cache and console.
clear; clc; close all;

% Placeholder value, remove this.
PLACEHOLDER = 10;

% Parameters.
numPoints = 1000; % The amount of points to plot on the curve.
t1 = linspace(-1.5, 0, numPoints); % Time for the linear line.
t2 = linspace(0, 1, numPoints); % Time for the transition curve.
t3 = linspace(1, 6, numPoints); % Time for the circlebow.
k = 1/3; % The allowed curvature during movement.
r = PLACEHOLDER; % Radius of the circle curve.
theta = PLACEHOLDER; % Turn angle in degrees.

%% Determination of the circular curve
% The center of the circle to the linear line:
c1 = [0;R];

% Determine the transition point P:
getCos = @(x) cos(x.^2 / (2 * R));
getSin = @(x) sin(x.^2 / (2 * R));

P = [
    integral(getCos, 0, 1);
    integral(getSin, 0, 1)
];

% Center of the circle curve when a transitioncurve has been applied.
C2 = P + r * [PLACEHOLDER, PLACEHOLDER];

% Parameter construction for when the linear line tangents the circlebow.
x1_naive = t1;                              % When t < 0
y1_naive = 0 * t1;

x2_naive = C1(1) + R*cos(t2./R-pi/2);       % When 0 < t < 1
y2_naive = C1(2) + R*sin(t2./R-pi/2); 

x3_naive = C1(1) + R*cos(t3./R-pi/2);       % When 1 < t
y3_naive = C1(2) + R*sin(t3./R-pi/2); 

%% Parameter construction for when a transition curve is applied.
x1_klotoide = t1;                           % When t < 0
y1_klotoide = 0 * t1;

x2_klotoide = zeros(1, length(t2));          % When 0 < t < 1
y2_klotoide = zeros(1, length(t2));

for i = 1:length(t2)
x2_klotoide(i) = integral(fun1, 0, t2(i));        
y2_klotoide(i) = integral(fun2, 0, t2(i));
end

x3_klotoide = C2(1) + R * cos(t3./R-theta); 	% When 1 < t
y3_klotoide = PLACEHOLDER;

%% Plot
figure('pos',[250 250 2000 1000])
subplot(1, 2, 1);
plot(x1_naive, y1_naive, 'red', 'LineWidth', 1.5)
xlabel('x')
ylabel('y')
title('Straight line that tangents the circlebow')
set(gca, 'fontsize', 24)
axis([-2 4 -1 5])
daspect([1 1 1])
grid on
hold on 
plot(x2_naive,y2_naive,'blue', 'LineWidth', 1.5)
plot(x3_naive,y3_naive,'green', 'LineWidth', 1.5)
legend('$t\leq 0$', '$0<t<1$', '$1\leq t$', 'Location', 'northwest', 'Interpreter', 'latex')
hold off

subplot(1, 2, 2);
plot(x1_klotoide, y1_klotoide, 'red', 'LineWidth', 1.5)
xlabel('x')
ylabel('y')
title('Transitioncurve applied')
set(gca,'fontsize', 24)
axis([-2 4 -1 5])
daspect([1 1 1])
grid on
hold on 
plot(x2_klotoide, y2_klotoide, 'blue', 'LineWidth', 1.5)
plot(x3_klotoide, y3_klotoide, 'green', 'LineWidth', 1.5)
legend('$t\leq 0$', '$0<t<1$', '$1\leq t$', 'Location', 'northwest', 'Interpreter', 'latex')
hold off