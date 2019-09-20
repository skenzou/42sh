# 42sh

## Current tasks

- Midrissi : core of the project (parser, lexer, executor, ...)
- Aben-azz : termcaps/prompt
- Ghamelek : test_builtin/has_table
- tlechien : cd_builtin/jobs control/signal monitoring/alias

## TODO
- builtin test
- POSIX norme on builtins
- Signal monitoring.
- Error management.

## TODO ACHRAF
- Mot selectionné a l'endroit du curseur durant l'autocompletion
- !!, !word, !number, !-number
- CTRL-R
- Completion automatique si path ou si env_var
- fc ? (Pas sur que ce soit dans termcaps, a voir)
- Gestion du redimensionnement de fenetre
- Couleurs dans l'autocompletion
- Gestion des leaks
- Copy/cut/past
- Home et End evenement
- SHIFT_UP et SHIFT_DOWN pour se deplacer dans une commande en haut et en bas
- Bonus
	- Autocompletion en fonction de la commande, ex:
		- cd => que des dossier
		- ls => fichier/dossier
		- man => fichier present dans le dossier man
- Floation point exception avec fleche du bas
- Protection getenv fichier historique

## DEBUG

- FPE: Down arrow while typing a command;
- unable to exit autocompletion when started;
- autocompletion doesn't work with for example ../../
- job research not working just yet (crashes)

## DONE

- Prompt
- Lexer
- Parser
- exec + fork + jobs
- builtin_jobs, fg, bg
- builtin_alias, unalias

fc -e vim
//ouvre la derniere commande dans un fichier temporaire avec vim. Quand on quitte en sauvegardant sur vim, la commande est executée.

fc -e vim X
//X est un nombre, ouvre la commande avec lindex X dans l'historique et fait pareil que fc -e vim

fc -e vim X Y
//ouvre les commandes dans lhistorique des index x a y pareil que fc -e vim X

fc -re vim X Y
//pareil quen haut sauf que cest inversé

fc -l
//liste les 16 derniere commandes dans lhistorique

fc -l X Y

//liste les commandes dans lhistorique aux index X a Y

fc -nl
//retire les index dans la liste
fc -lr X Y
//pareil en reverse

fc X=NaN
//cherche la derniere commande commencant par X;
fc -l X=NaN
//affiche depuis la derniere commande commencant par X

fc -l chien chat
//affiche une liste des commandes a partir dune commande commencant par chien jusqua lindex dune commande commencant par chat


DEUX COMMANDES FC PAREILLES


"fc -lr bite 10807" == "fc -l 10807 bite"
"fc -e - X Y" == "fc -s X Y"
