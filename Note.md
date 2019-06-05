# si la cmd == fonction cd || nimporte quoi dir
	si espace
		autocomplete nom de la fonction
	sinon
		autocomplete avec des dossier

# si la cmd == fonction != cd && nimporte kel dir
	si espace
		autocomplete nom de la fonction
	sinon
		autocomplete avec des dossier et fichier dossier courant

# si la cmd == dossier connu
	si dernier char cmd != dernier char dossier
		autocomplete fin du dossier
	sinon
		autocomplete avec /

# si on est au premier argument
	autocomplete dossier + fonction
# si on est au deuxieme argument apres un premier argument != fonction
	autocomplete dossier/fichier dossier courant
# si aucun resultat
	tcap->sound

#Type de completion
- fichier/dossier
- argument speciaux
- commandes/builtin
- path
- envvar

# Argument speciaux
	- man:
		commandes du man;
	- cd/ls:
		dossier
	- cat/diff:
		fichiers
	- gcc:
		fichier .c/.cc/.a/dossier
	- git:
		add fichiers/dossier
		commit -m ""
	- export/env_var
		env_var=
	- cp/mv/rm/test:
		fichier/dossier
	- sh:
		.sh/executable
	- fg/jobs_builtin:
		pid
	- type/test:
		tout

#couleur:
	fifo: jaune + '|'
	execfile: vert + '\*'
	dir: rouge grad + '//'
	regular file: white

on est au 1er argument || apres ; ou && ou ||:
	si derniere lettre == / || correspond a dossier courrant
		- ajoute / si pas && complete path/dossier
	sinon
		- dossier/cmd/builtin
on est au deuxieme argument
	si cmd == CD || Builtin/cmd connue
		- argument speciaux;
	sinon
		si derniere lettre == / || correspond a dossier courrant
			- complete path/dossier
		sinon
			-dossier/fichier/courant
on est au premier argument fin du nom dune commande
	- on ajoute un espace
Si premiere lettre du mot == $
	- complete env_var
