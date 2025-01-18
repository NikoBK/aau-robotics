% Name:     quaternions.m
% Created:  5/29/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Rotation matrix to quaternions.
% Based on page of 61 of 'Introduction to robotics' by John Craig.
% This code will calculate quaterions for you based on a defined rotation
% matrix.
clear; clc; close all;

% Change this rotation matrix R to the rotation matrix you need converted:
R = [
    1,  0,  0;
    0,  1,  0;
    0,  0,  1
];

% e = epsilon
e4 = 1/2 * (sqrt(1 + R(1,1) + R(2, 2) + R(3,3)));
e1 = (R(3,2) - R(2,3)) / 4 * e4;
e2 = (R(1,3) - R(3,1)) / 4 * e4;
e3 = (R(2,1) - R(1,2)) / 4 * e4;

disp("Calculated quaternion values are:")
disp("    epsilon1 is: " + e1)
disp("    epsilon2 is: " + e2)
disp("    epsilon3 is: " + e3)
disp("    epsilon4 is: " + e4)

%% Quaternions to rotation matrix.
clear; clc; close all;

% Change the epsilon values to your quaternions.
e1 = 0.064071;
e2 = 0.091158;
e3 = 0.15344;
e4 = 0.98186;

r11 = 1 - 2 * e2^2 - 2 * e3^2;
r12 = 2 * (e1 * e2 - e3 * e4);
r13 = 2 * (e1 * e3 + e2 * e4);
r21 = 2 * (e1 *e2 + e3 *e4);
r22 = 1 - 2 * e1^2 - 2 * e3^2;
r23 = 2 * (e2 * e3 - e1 * e4);
r31 = 2 * (e1 * e3 - e2 * e4);
r32 = 2 * (e2 * e3 + e1 * e4);
r33 = 1 - 2 * e1^2 - 2 * e2^2;

R = [
    r11, r12, r13;
    r21, r22, r23;
    r31, r32, r33
];

fprintf("Using quaternions:\n")
disp("    epsilon1 = " + e1)
disp("    epsilon2 = " + e2)
disp("    epsilon3 = " + e3)
disp("    epsilon4 = " + e4)
fprintf("\nYour rotation matrix is:\n")
disp(R)

%% Quaternions to Roll Pitch Yaw (xyz)
clear; clc; close all;

% Change the epsilon values to your quaternions.
e1 = 0.064071;
e2 = 0.091158;
e3 = 0.15344;
e4 = 0.98186;

r11 = 1 - 2 * e2^2 - 2 * e3^2;
r12 = 2 * (e1 * e2 - e3 * e4);
r13 = 2 * (e1 * e3 + e2 * e4);
r21 = 2 * (e1 *e2 + e3 *e4);
r22 = 1 - 2 * e1^2 - 2 * e3^2;
r23 = 2 * (e2 * e3 - e1 * e4);
r31 = 2 * (e1 * e3 - e2 * e4);
r32 = 2 * (e2 * e3 + e1 * e4);
r33 = 1 - 2 * e1^2 - 2 * e2^2;

R = [
    r11, r12, r13;
    r21, r22, r23;
    r31, r32, r33
];

beta = atan2(-R(3,1), sqrt(R(1,1)^2 + R(2,1)^2));
alpha = atan2(R(2,1) / cos(beta), R(1,1) / cos(beta));
gamma = atan2(R(3,2) / cos(beta), R(3,3) / cos(beta));

fprintf("Using quaternions:\n")
disp("    epsilon1 = " + e1)
disp("    epsilon2 = " + e2)
disp("    epsilon3 = " + e3)
disp("    epsilon4 = " + e4)
fprintf("\nUsing rotation matrix:\n")
disp(R)
fprintf("Computed Roll Pitch Yaw is:\n")
disp("    Roll: " + gamma + "(Gamma)")
disp("    Pitch: " + beta + "(Beta)")
disp("    Yaw: " + alpha + "(Alpha)")

%% Intrensic Rotation Matrix to Quaternion
r11 = 1 - 2 * e2^2 - 2 * e3^2;
r12 = 2 * (e1 * e2 - e3 * e4);
r13 = 2 * (e1 * e3 + e2 * e4);
r21 = 2 * (e1 *e2 + e3 *e4);
r22 = 1 - 2 * e1^2 - 2 * e3^2;
r23 = 2 * (e2 * e3 - e1 * e4);
r31 = 2 * (e1 * e3 - e2 * e4);
r32 = 2 * (e2 * e3 + e1 * e4);
r33 = 1 - 2 * e1^2 - 2 * e2^2;

R = [
    r11, r12, r13;
    r21, r22, r23;
    r31, r32, r33
];

R13 = R(1,3);
R23 = R(2,3);
R22 = R(2,2);
R21 = R(2,1);
R31 = R(3,1);
R32 = R(3,2);
R33 = R(3,3);
R11 = R(1,1);
R12 = R(1,2);

e4=sqrt(1 + R11 + R22 + R33) / 2;
e1 = (R32 - R23) / (4 * e4);
e2 = (R13 - R31) / (4 * e4);
e3 = (R21 - R12) / (4 * e4);

ang1 = [e1; e2; e3; e4];