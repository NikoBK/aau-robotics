% Name:     forwardKinematics.m
% Created:  5/29/2023
% Author:   NikoBK

% Clear cache and console.
clear; clc; close all;

disp("If you are reading this in your command window it means you have pressed 'Run'.")
disp("Please use 'Run Section' while being in the correct section within the code instead.")
return;

%% Derive forward kinematics
% Given up to 6 Denavit Hartenberg parameters, use this function to get the
% complete modified Denavit Hartenberg transformation matrix.
clear; clc; close all;

d = sym('d', [1,6]);
l = sym('L', [1,6]);
l_abs = sym('L')
t = sym('t', [1,6]);
pi = sym(pi);

% Specify this to your number of robot joints.
joints = 2;

% Denavit Hartenberg Parameters, change these to the ones you have.
dhParams = [
%    alpha_i-1     a_i-1        d_i    theta_i
        0,           0,        0,   t(1);
    90 * pi/180,    sym('L'),       d(2),     0
];

% Change this row to compute the matrix respective for the i'th row in the
% dh parameters.
row = 1;

r11 = cos(dhParams(row, 4));
r12 = -sin(dhParams(row, 4));
r13 = 0;
r14= dhParams(row, 2);

r21 = sin(dhParams(row, 4)) * cos(dhParams(row, 1));
r22 = cos(dhParams(row, 4)) * cos(dhParams(row, 1));
r23 = -sin(dhParams(row, 1));
r24= -sin(dhParams(row, 1)) * dhParams(row, 3);

r31 = sin(dhParams(row, 4)) * sin(dhParams(row, 1));
r32 = cos(dhParams(row, 4)) * sin(dhParams(row, 1));
r33 = cos(dhParams(row, 1));
r34 = cos(dhParams(row, 1)) * dhParams(row, 3);

dhMatrix = [
    r11, r12, r13, r14;
    r21, r22, r23, r24;
    r31, r32, r33, r34;
     0,   0,   0,   1
];

disp("Modified DH matrix for {" + (row - 1) + "} to {" + row + "} is:")
disp(dhMatrix)

T01 = [
    cos(t(1)), -sin(t(1)), 0, 0;
    sin(t(1)),  cos(t(1)), 0, 0;
          0,        0, 1, 0;
          0,        0, 0, 1
];

T12 = [
    1, 0,  0,   sym('L');
    0, 0, -1, -d(2);
    0, 1,  0,   0;
    0, 0,  0,   1
];


T02 = T01 * T12;
disp("Full transformation matrix based on modified DH parameters is computed to be:")
disp(T02)

%% Forward Kinematics Using the Robotic Tool box
clear all
a1=1;
a2=0.5;
C1=2;
c3=1;
C2=1;

% Using Robotic Toolbox
L(1) = Link('alpha', pi/2,'a', 0,'d', 0,'modified') %rotational
L(2) = Link('alpha', 0,'a', -0.425,'d', 0,'offset',-pi/2,'modified') %rotational
L(3) = Link('alpha', 0,'a',-0.39225 ,'d', 0,'offset',-pi/2,'modified') %rotational
L(4) = Link('alpha', pi/2,'a', 0,'d', c3,'modified') %rotational
L(5) = Link('alpha', -pi/2,'a', 0,'d', 0,'offset',0,'modified') %rotational
L(6) = Link('alpha', 0,'a', 0,'d', 0,'modified') %rotational
SixDOF=SerialLink(L, 'name', 'SixDOF-RRRRRR');

% Lets test the movement
SixDOF.teach();

%% 2018
clear all
a1=1;
a2=0.5;
C1=2;
c3=1;
C2=1;
%Using Robotic Toolbox
L(1) = Link('alpha', 0,         'a', 0,              'd', 0.089159, 'offset',5,    'modified') %rotational
L(2) = Link('alpha', pi/2,      'a', -0.425,         'd', 0,        'offset',10+pi,     'modified') %rotational
L(3) = Link('alpha', 0,         'a', -0.39225,       'd', 0,        'offset',15,    'modified') %rotational
L(4) = Link('alpha', 0,         'a', 0,              'd', 0.10915,  'offset',20,    'modified') %rotational
L(5) = Link('alpha', -pi/2,     'a', 0,              'd', 0.09465,  'offset',25,    'modified') %rotational
L(6) = Link('alpha', pi/2,       'a', 0,             'd', 0.0823,   'offset',30+pi,     'modified') %rotational
SixDOF=SerialLink(L, 'name', 'SixDOF-RRRRRR');

%Lets test the movement
SixDOF.teach();