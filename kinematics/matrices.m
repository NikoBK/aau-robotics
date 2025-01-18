% Name:     mactrices.m
% Created:  07/17/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Template for Transformation Matrices
% Usefull for matrix multiplication

% Wrist -> mantel
T = [
    0.7500   -0.6597    0.0474  100;
    0.4330    0.4356   -0.7891  300;
    0.5000    0.6124    0.6124  200;
         0         0         0    1
];

% Base -> mantel
T2 = [  
       1           0           0         500;
       0           1           0        2200;
       0           0           1           0;
       0           0           0           1
];

inv(T2) * T

%% Matrix Representation to Axis-Angle Representation
% The firsth method of doing this is to insert the transformation matrix in
% the following code which the script will use to yield a vector that
% represents the axis-angle.

m = [
   0    -0.866  0.5     -0.4;
   0   -0.5    -0.866   1.2;
   1    0       0       0.6;
   0    0       0       1
];

radangle = acos((m(1,1) + m(2, 2) + m(3, 3) - 1) / 2);
angle = rad2deg(acos((m(1,1) + m(2,2) + m(3,3) - 1) / 2));
x = (m(3,2) - m(2,3)) / sqrt((m(3,2) - m(2,3))^2 + (m(1,3) - m(3,1))^2 + (m(2,1) - m(1,2))^2);
y = (m(1,3) - m(3,1)) / sqrt((m(3,2) - m(2,3))^2 + (m(1,3) - m(3,1))^2 + (m(2,1) - m(1,2))^2);
z = (m(2,1) - m(1,2)) / sqrt((m(3,2) - m(2,3))^2 + (m(1,3) - m(3,1))^2 + (m(2,1) - m(1,2))^2);

% The alternative method by Craig:
x1 = (1 / (2 * sin(radangle))) * (m(3,2) - m(2,3));
y1 = (1 / (2 * sin(radangle))) * (m(1,3) - m(3,1));
z1 = (1 / (2 * sin(radangle))) * (m(2,1) - m(1,2));

AxisAngle = [angle, x, y, z]
CraigAngle = [angle, x1, y1, z1]'

%% Rotation Matrix from Angle Axis
K = N/A;

Kx = K(1);
Ky = K(2);
Kz = K(3);
t = K(4);
ct = cos(t);
vt = 1-cos(t);
st = sin(t);

T=  [
    Kx * Kx * vt + ct, Kx * Ky * vt - Kz * st, Kx * Kz * vt + Ky * st;
    Kx * Ky * vt + Kz * st, Ky * Ky * vt + ct, Ky * Kz * vt - Kx * st;
    Kx * Kz * vt - Ky * st, Ky * Kz * vt + Kx * st, Kz * Kz * vt + ct
];

%% XYZ Fixed Intrinsic
R = [
    0.9363,   -0.2896,    0.1987;
    0.3130,    0.9447,   -0.0978;
   -0.1593,    0.1538,    0.9752
];

R31 = R(3,1);
R32 = R(3,2);
R33 = R(3,3);
R11 = R(1,1);
R12 = R(1,2);
R21 = R(2,1);

beta_1=atan2(-R31, sqrt(R11^2 + R21^2));
alpha_1=atan2(R21 / cos(beta_1), R11 / cos(beta_1));
gamma_1=atan2(R32 / cos(beta_1), R33 / cos(beta_1));

beta_2 = atan2(-R31, -sqrt(R11 * R11 + R21 * R21));
alpha_2 = atan2(R21 / cos(beta_2), R11 / cos(beta_2));
gamma_2 = atan2(R32 / cos(beta_2), R33 / cos(beta_2));


if(APX(beta_1, pi / 2, 0.1))
     
    alpha_1 = 0;
    gamma_1 = atan2(-R12, R11);

    alpha_2 = 0;
    gamma_2 = atan2(-R12, R11);
end
if(APX(beta_1, -pi / 2, 0.1))
    
    alpha_1 = 0;
    gamma_1 = atan2(R12, R11);

    alpha_2 = 0;
    gamma_2 = -atan2(R12, R11);
end

ang1 = [alpha_1; beta_1; gamma_1];
ang2 = [alpha_2; beta_2; gamma_2];
T = [ang1, ang2];

%% ZYZ Intrinsic
R = [
    0.9363,   -0.2896,    0.1987;
    0.3130,    0.9447,   -0.0978;
   -0.1593,    0.1538,    0.9752
];

R13 = R(1,3);
R23 = R(2,3);
R31 = R(3,1);
R32 = R(3,2);
R33 = R(3,3);
R11 = R(1,1);
R12 = R(1,2);

beta_1 = atan2(sqrt(R31 * R31 + R32 * R32), R33);
alpha_1 = atan2(R23 / sin(beta_1), R13 / sin(beta_1));
gamma_1 = atan2(R32 / sin(beta_1), -R31 / sin(beta_1));

beta_2 = atan2(-sqrt(R31 * R31 + R32 * R32), R33);
alpha_2 = atan2(R23 / sin(beta_2), R13 / sin(beta_2));
gamma_2 = atan2(R32 / sin(beta_2), -R31 / sin(beta_2));

if(APX(beta_1_1, pi / 2, 0.1))  
    alpha_1 = 0;
    gamma_1 = atan2(-R12, R11);

    alpha_2 = 0;
    gamma_2 = atan2(-R12, R11);
end
if(APX(beta_1_1, -pi / 2, 0.1))
    alpha_1 = 0;
    gamma_1 = atan2(R12, -R11);

    alpha_2 = 0;
    gamma_2 = -atan2(R12, -R11);
end
ang1 = [alpha_1; beta_1; gamma_1];
ang2 = [alpha_2; beta_2; gamma_2];


%% ZYX Euler Intrinsic
R = [
    0.9363,   -0.2896,    0.1987;
    0.3130,    0.9447,   -0.0978;
   -0.1593,    0.1538,    0.9752
];

R13 = R(1,3);
R23 = R(2,3);
R31 = R(3,1);
R32 = R(3,2);
R33 = R(3,3);
R11 = R(1,1);
R12 = R(1,2);

beta_1 = atan2(sqrt(R31 * R31 + R32 * R32), R33);
gamma_1 = atan2(R23 / sin(beta_1), R13 / sin(beta_1));
alpha_1 = atan2(R32 / sin(beta_1), -R31 / sin(beta_1));

beta_2 = atan2(-sqrt(R31 * R31 + R32 * R32), R33);
gamma_2 = atan2(R23 / sin(beta_2), R13 / sin(beta_2));
alpha_2 = atan2(R32 / sin(beta_2), -R31 / sin(beta_2));

if(APX(beta_1_1, pi / 2, 0.1))  
    gamma_1 = 0;
    alpha_1 = atan2(-R12, R11);

    gamma_2 = 0;
    alpha_2 = atan2(-R12, R11);
end
if(APX(beta_1_1, -pi / 2, 0.1))
    alpha_1 = 0;
    gamma_1 = atan2(R12, -R11);

    alpha_2 = 0;
    gamma_2 = -atan2(R12, -R11);
end
ang1 = [alpha_1; beta_1; gamma_1];
ang2 = [alpha_2; beta_2; gamma_2];