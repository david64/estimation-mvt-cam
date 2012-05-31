clear
clf
A = [-0.000069 0.008145 -0.171711 0.575643 -0.000007 -0.000041 -0.072971  ; -0.000033 0.009265 -0.216488 0.750498 -0.000000 -0.000059 0.432192  ; 0.001031 0.009487 -0.170698 0.632276 0.000002 -0.000059 -0.039438  ; -0.000095 0.005355 -0.015939 0.486321 -0.000009 0.000004 0.030259  ; -0.000190 0.000192 0.051644 0.269555 0.000003 0.000061 0.005360  ; -0.000250 -0.002472 0.073066 0.205524 0.000006 0.000068 0.005475  ; -0.000712 -0.003467 0.086758 0.258789 0.000002 0.000051 0.000904  ; -0.000404 -0.005858 0.095390 0.429630 0.000001 0.000021 0.006417  ; -0.000283 -0.008716 0.140551 0.639484 -0.000006 -0.000014 0.042782  ; 0.000539 -0.012032 0.126818 0.822305 0.000008 -0.000028 0.034719  ; 0.000522 0.000149 -0.000202 -0.077642 0.000001 -0.000005 0.039973  ; -0.000066 -0.000023 0.002051 0.010233 -0.000001 0.000003 0.012679  ; 0.000039 -0.000072 -0.002901 -0.005740 0.000001 -0.000004 -0.017404  ; -0.000040 0.000090 0.003054 0.005905 -0.000000 0.000004 0.008718  ; 0.000040 -0.000090 -0.003022 -0.005756 0.000000 -0.000004 -0.006051  ; -0.000039 0.000091 0.003075 0.005796 -0.000000 0.000004 0.005807  ; 0.000039 -0.000092 -0.003038 -0.005755 0.000000 -0.000004 -0.005954  ; -0.000039 0.000092 0.003005 0.005778 -0.000000 0.000004 0.005256  ; 0.000039 -0.000092 -0.002986 -0.005808 0.000000 -0.000004 -0.005352  ; -0.000039 0.000092 0.002999 0.005791 -0.000000 0.000004 0.005730  ; 0.000038 -0.000092 -0.002966 -0.005741 0.000000 -0.000004 -0.005701 ];
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

