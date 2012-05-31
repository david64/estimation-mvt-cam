#!/bin/bash

# Nettoyage !
rm images/*.translation*
rm images/*.rotation*
rm images/*.zoom
rm images/*.superposition

# Le script proprement dit
cd images
for image in *
do
	# Créer les images modifiées par le programme simul_mvt
	../../simul_mvt $image ${image}.translation1 0 0 0 0.05 0 0 >> /dev/null
	../../simul_mvt $image ${image}.translation2 0 0 0 0 0.05 0 >> /dev/null
	../../simul_mvt $image ${image}.rotationaxe 0 0 0.05 0 0 0 >> /dev/null
	../../simul_mvt $image ${image}.rotationprojective 0.1 0.05 0 0 0 0 >> /dev/null
	../../simul_mvt $image ${image}.zoom 0 0 0 0 0 0.05 >> /dev/null
	../../simul_mvt $image ${image}.superposition 0.1 0.05 0.05 0.05 0.05 0.05 >> /dev/null
	
	# Un message pour informer de l'avancement
	echo "Images découlant de $image créées."

	# Écrire dans un fichier les deltatheta_k
	for image2 in ${image}.*
	do
		../../deltathetas $image $image2 > ../matrices_deltathetas/${image}_to_${image2}
		echo "Matrice découlant de $image et $image2 écrite."
	done
done

exit 0;

