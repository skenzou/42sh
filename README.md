# 42sh

## Current tasks

- Midrissi : core of the project (parser, lexer, executor, ...)
- Aben-azz : termcaps/prompt
- Ghamelek : test_builtin/has_table
- tlechien : alias

## TODO
- POSIX norme on builtins
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

- autocompletion doesn't work with for example ../../

## DONE

- Prompt
- Lexer
- Parser
- exec + fork + jobs
- builtin_jobs, fg, bg
- builtin_alias, unalias
