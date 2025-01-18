% Name:     trajectory.m
% Created:  5/29/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Trajectory Planning: 1D Cubic Polynomial, No Via Points
% The following values are from a random task in RMMS.
theta0 = 10;
theatF = 50;
tf = 3;

a0 = theta0;
a1 = 0;
a2 = 3 / (tf * tf) * (thetaF - theta0)
a3 = -2 / (tf * tf * tf) * (thetaF - theta0)

% Theta (Blue) is a third degree polynomial that models degrees or m/mm over time.
% ThetaDot (Orange) is a second degree polynomial that models the speed
% over time.
% TheDotDot (Yellow) is a linear function that models acceleration over
% time.

t = 0:0.05:tf;
theta = a0 + a1 * t + a2 * t.^2 + a3 * t.^3;
thetaDot = a1 + 2 * a2 * t+3 * a3 * t.^2;
thetaDotDot = 2 * a2 + 6 * a3 * t;

thetaRef = [theta0; thetaF];
tRef = [0.0; tf];
plot(t, theta, t, thetaDot, t, thetaDotDot);
F = a0 + a1 * 1.4 + a2 * 1.4^2 + a3 * 1.4.^3

%% Trajectory Planning: 1D Cubic Polynomial w/ Via Points
% The following values are from a random task in RMMS.

% Start
theta1 = 50;
theta1Dot = 0.0;

% Via point (degree & speed)
theta2 = 20;
theta2Dot = -2;

% End
theta3 = -25;
theta3Dot = 0.0;

% Movement duration part 1
tf12 = 2;

% Move duration part 2
tf23 = 3

% First segment
a012 = theta1;
a112 = theat1Dot;
a212 = 3 / (tf12^2) * (theta2 - theta1) - 2 / tf12 * theta1dot - 1 / tf12 * theta2Dot;
a312 = - 2 / (tf12^3) * (theta2 - theta1) + 1 / (tf12^2) * (theta2Dot + theta1Dot);
 
t12 = 0:0.05:tf12;
theta12 = a012 + a112 * t12 + a212 * t12.^2 + a312 * t12.^3;
thetaDot12 = a112 + 2 * a212 * t12 + 3 * a312 * t12.^2;
thetaDotDot12 = 2 * a212 + 6 * a312 * t12;

% Second segment
a023 = theta2
a123 = theta2Dot
a223 = 3 / (tf23^2) * (theta3 - theta2) - 2 / tf23 * theta2Dot - 1 / tf23 * theta3Dot
a323 = -2 / (tf23^3) * (theta3 - theta2) + 1 / (tf23^2) * (theta3Dot + theta2Dot)
 
t23=0:0.05:tf23;
theta23= a023 + a123 * t23 + a223 * t23.^2 + a323 * t23.^3;
thetaDot23 = a123 + 2 * a223 * t23 + 3 * a323 * t23.^2;
thetaDotDot23 = 2 * a223 + 6 * a323 * t23;
  
t=[t12 t23 + tf12];
theta=[theta12 theta23];
thetaDot=[thetaDot12 thetaDot23]; 
thetaDotDot=[thetaDotDot12 thetaDotDot23];

% Reference trajectory
thetaRef =[theta1; theta2; theta3];
tRef =[0.0; tf12; tf12 + tf23];

plot(t, thetaDot, t, thetaDotDot, t, theta);

%% Trajectory Planning: 1D Parabolic Blend - No Via Points
% The following values are from a random task in RMMS.

theta0 = -43;
thetaf = 28;
tf = 6.7;
a = 10;

tb= tf/2 - sqrt(a^2 * tf^2 - 4 * a * (thetaf - theta0)) / (2 * a);

t=0:0.05:tf;
theta = 0:0.05:tf; 
thetaDot = 0:0.05:tf; 
thetaDOtDot = 0:0.05:tf; 
thetaRef = [theta0; thetaf];
tRef = [0.0; tf];

for i=1:size(t,2)
    if (t(i) < tb)
        theta(i) = theta0 + 0.5 * a * t(i)^2;
        thetaDot(i) = a * t(i);
        thetaDotDot(i) = a;

    elseif (t(i) > (tf - tb))
            theta(i) = thetaf - 0.5 * a * (tf - t(i))^2;
            thetaDot(i) = a * (tf - t(i));
            thetaDotDot(i) = -a;
    else
            theta(i) = 0.5 * a * tb^2 + theta0 + a * tb * (t(i) - tb);
            thetaDot(i)=a * tb;
            thetaDotDot(i) = 0;

    end
end


plot(t, theta);




