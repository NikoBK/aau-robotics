% Name:     mulitpleVariableIntegration.m
% Created:  6/15/2023
% Author:   nikobk

% ABOUT
% A script for finding the integral for a function with multiple
% variables.

% Clear cache and console.
clear; clc; close all;

% Integral upper and lower limits.
a = 0;
b = 1;

% A constant that is part of the function.
c = 10;

% The function for which we want the integral:
func = @(c, s) -(-1+(c.^2+2).*s-3.*s.^2 +2.*s.^3).* (1-2.*s+(c.^2+2).*s.^2-2.*s.^3 +s.^4).^(-3/2) ;

% Take the integral of the function above:
funcInt = integral(@(x) func(c,x), a, b);

% Display the result.
disp("Integral of function f(c, s) is: ");
disp(funcInt);