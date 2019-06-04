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
- [✓] Floation point exception avec fleche du bas
- [✓] Home et End evenement
- Mot selectionné a l'endroit du curseur durant l'autocompletion
- !!, !word, !number, !-number
- CTRL-R
- Completion automatique si path ou si env_var
- fc ? (Pas sur que ce soit dans termcaps, a voir)
- Gestion du redimensionnement de fenetre
- Couleurs dans l'autocompletion
- Gestion des leaks
- Copy/cut/past
- Deplacement par mots a regler
- SHIFT_UP et SHIFT_DOWN pour se deplacer dans une commande en haut et en bas
- Bonus
	- Autocompletion en fonction de la commande, ex:
		- cd => que des dossier
		- ls => fichier/dossier
		- man => fichier present dans le dossier man
- Protection getenv fichier historique

## DEBUG

error commands that require prompt reading

## DONE

- Prompt
- Lexer
- Parser
- exec + fork + jobs
- builtin_jobs, fg, bg
- builtin_alias, unalias
