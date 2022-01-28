clc
%ve = readtable('out.txt')
ve = readmatrix('out.txt')
plot(ve(:,1),ve(:,2),'b', ve(:,1),ve(:,3),'r')
legend('ve')
xlabel('t (s)')
ylabel('ve, vs (V)')
title('ve(t), vs(t)')
