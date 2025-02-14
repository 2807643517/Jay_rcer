clear;
clc;

% 画场地
DrawMap % tr
% Map % dr
    
% 定义变量
N = 5; % 控制点个数
T = 5.0;
Hz = 100;
Robot_R = 0.7; % 轮子到中心半径

% 控制点
% yaw = [45.0 35.0 0 -35.0 -45.0];
% x = [0.0 -2650.0 -5250.0 -7875.0 -10500.0];
% y = [0.0 175.0 350.0 525.0 700.0];
x = [-10600.0 -9300.0  -8000.0  -6700.0 -5400.0];
y = [ 800.0  825.0   850.0   875.0  900.0];

yaw = zeros(1,N);
% x = [-1000.0 -900.0 -3800.0 -7300.0 -8840.0];
% y = [ 4900.0   1650   210.0   270.0  1900.0];

% dr
% x = [0 -600.0 -1320.0 -2940.0 -4865.0];
% y = [0 1710.0  3250.0  4575.0  4185.0];

% yaw = zeros(1,N);
% x = [0.0 -3135.0 -5500.0 -7700.0 -8700.0];
% y = [0.0   817.7   400.0   570.0  1600.0];

% x = [-8800.0 -4400.0 0];
% y = [ 2100.0  1050.0 0];
% yaw = (-45:45/(N-1):0);

% figure(2);
% plot(res(:,1) , res(:,2) ,'-r.','MarkerSize',20);

main(N, T, Hz, x, y, yaw, Robot_R);
