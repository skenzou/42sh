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
- [✓] Copy/cut/past
- [✓] SHIFT_UP et SHIFT_DOWN pour se deplacer dans une commande en haut et en bas
- [✓] Gestion du redimensionnement de fenetre
- [✓] Recherche incrémentale dans l’historique avec CTRL-R
- La gestion complète de l’historique :
	- Les expansions :
		- !! **commande precedente dans lhisto**
		- !*word* **cherche la premiere commande matchant avec word dans lhisto**
		- !*number* **cherche la n ieme commande dans lhisto**
		- !-*number* **cherche le number ieme precedent dans lhisto**
	- Le built-in fc (toutes les options POSIX)
		- e *editor* **Specifie un editeur, si pa specifie la variable FCEDIT le specifie**
		- l **affiche les N premiere commande de l'histo + ID**
		- n	 **N'affiche pas les ID quand -l est appelé**
		- r	 **Inverse l'ordre de tri**
		- s	 **Re-executer une commande sans ouvrir lediteur**
- Smart autocompletion
- Protection getenv fichier historique
- Gestion des leaks

## DEBUG

error commands that require prompt reading

## DONE

- Prompt
- Lexer
- Parser
- exec + fork + jobs
- builtin_jobs, fg, bg
- builtin_alias, unalias
