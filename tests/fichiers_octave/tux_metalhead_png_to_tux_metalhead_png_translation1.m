clear
clf
A = [-0.004336 -0.001090 0.759876 0.035878 -0.000012 0.000032 -0.849181  ; -0.003632 -0.001149 0.928581 -0.002457 -0.000017 0.000034 0.623774  ; -0.003372 -0.001054 0.928741 0.000286 -0.000006 0.000000 0.170532  ; -0.001379 -0.000730 0.951535 0.052485 0.000016 -0.000047 0.168852  ; 0.004861 0.001322 1.035143 -0.000898 -0.000021 -0.000054 0.303571  ; 0.009090 0.003039 0.561973 -0.111034 0.000011 0.000025 0.130142  ; -0.001465 -0.000394 -0.199631 0.029340 0.000035 0.000012 -0.065586  ; 0.000269 0.000066 0.036030 -0.003561 -0.000006 -0.000002 -0.028792  ; -0.000133 -0.000071 -0.006860 -0.000819 0.000002 0.000002 0.071180  ; 0.000158 0.000109 0.006931 0.001507 -0.000003 -0.000004 -0.059761  ; -0.000120 -0.000121 -0.004758 -0.002118 0.000003 0.000004 0.032792  ; 0.000121 0.000141 0.004354 0.002907 -0.000003 -0.000005 -0.017632  ; -0.000107 -0.000143 -0.003941 -0.002907 0.000003 0.000005 0.012756  ; 0.000107 0.000148 0.004093 0.003113 -0.000003 -0.000006 -0.010374  ; -0.000103 -0.000147 -0.003952 -0.003255 0.000003 0.000006 0.009933  ; 0.000101 0.000149 0.003904 0.003189 -0.000003 -0.000006 -0.007956  ; -0.000099 -0.000147 -0.003900 -0.003228 0.000003 0.000006 0.006534  ; 0.000097 0.000150 0.003868 0.003306 -0.000003 -0.000006 -0.006457  ; -0.000094 -0.000150 -0.003846 -0.003349 0.000002 0.000006 0.006030  ; 0.000092 0.000150 0.003846 0.003364 -0.000002 -0.000006 -0.006425  ; -0.000092 -0.000152 -0.003791 -0.003423 0.000002 0.000006 0.006078  ; 0.000089 0.000153 0.003728 0.003433 -0.000002 -0.000006 -0.006428  ; -0.000085 -0.000155 -0.003641 -0.003520 0.000002 0.000006 0.006089 ];
% Vecteur colonne du nombre d'itérations
N=length(A(:,1));
iterations=[1:N]';

% Tracé
titres=['Increments de a1';'Increments de a2';'Increments de c1';'Increments de c2';'Increments de q1';'Increments de q2';'Increments de xi'];
for i=1:7
	subplot(2,4,i)
	plot(iterations(1:end), A(1:end,i), '*-');
	title(titres(i,:));
end

