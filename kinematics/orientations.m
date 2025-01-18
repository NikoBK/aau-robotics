% Name:     orientations.m
% Created:  5/29/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Convert rotation matrix to extrinsic XYZ rotation (XYZ fixed angles)
% Gamma (Roll), Beta (Pitch), Alpha (Yaw).
% Based on page of 53, equation (2.66) of 'Introduction to robotics' by John Craig.
clear; clc; close all;

% Rotation matrix, change this to your rotation matrix.
R = [
    0.9363,   -0.2896,    0.1987;
    0.3130,    0.9447,   -0.0978;
   -0.1593,    0.1538,    0.9752
];

beta = atan2(-R(3,1), sqrt(R(1,1)^2 + R(2,1)^2));
alpha = atan2(R(2,1) / cos(beta), R(1,1) / cos(beta));
gamma = atan2(R(3,2) / cos(beta), R(3,3) / cos(beta));

disp("Rotation matrix:")
disp(R)
fprintf("has been converted to:\n\n")
disp("Roll: " + gamma + "(Gamma)")
disp("Pitch: " + beta + "(Beta)")
disp("Yaw: " + alpha + "(Alpha)")

%% Convert Rotation Matrix to RPY (Roll Pitch Yaw)
R = [
    0.9363,   -0.2896,    0.1987;
    0.3130,    0.9447,   -0.0978;
   -0.1593,    0.1538,    0.9752
];

beta = atan2(-rotm(3,1), sqrt(rotm(1,1)^2 + rotm(2,1)^2));
alpha = atan2(rotm(2,1) / cos(beta), rotm(1,1) / cos(beta));
gamma = atan2(rotm(3,2) / cos(beta), rotm(3,3) / cos(beta));

RPY = [gamma, beta, alpha];