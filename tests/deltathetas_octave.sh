#!/bin/bash

cd matrices_deltathetas
for matrice in *
do
	nom_corrige=$(echo $matrice | tr '.' '_' | tr '-' '_')
	nom_fichier=$(echo ../fichiers_octave/${nom_corrige}.m)
	echo 'clear' > $nom_fichier
	echo 'clf' >> $nom_fichier
	cat $matrice >> $nom_fichier
	cat ../fin_script_octave_2 >> $nom_fichier
done
exit 0;

