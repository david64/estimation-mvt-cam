clear
clf

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

