# 21sh

## Current tasks

- missidri : core > pipes
- aben-azz : termcaps/prompt
- ghamelek : type_builtin ?
- tlechien : jobs controls, cd_builtin

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

## TODO

- Merge alias feature and add builtin to the list.
- Add '&' and merge job feature.
- Signal monitoring.
- Error management.
- test_builtin
- substitution ??


## DEBUG

error commands that require prompt reading

## DONE

- Prompt
- Lexer
- Parser
- exec + fork + jobs
- builtin_jobs, fg, bg
- builtin_alias, unalias
