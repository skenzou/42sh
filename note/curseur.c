/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 11:33:18 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/28 12:02:47 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** tgetent:
** initialisation de termcaps en fonction du terminal;
*/

/*
** tgetflag:
** int tgetflag(char *id);
** recuperer une information de type booleenne (int)
*/

/*
** tgetnum:
** int tgetnum(char *id);
** recuperer une information de type nombre (int)
*/

/*
** tgetstr:
** char *tgetstr(char *id, char **area);
** recuperer une information de type string (char *)
** deuxieme parametre a mettre a nul == premier argument tegtent
*/

/*
** tgoto:
** char *tgoto(const char *cap, int col, int row);
** sert a parametrer le termcap (cap) en fonction de col et row
*/

/*
** tputs:
** int tputs(const char *str, int affcnt, int (*putc)(int));
** Fonctionne avec tgetstr, elle va permettre d'afficher un termcap a l'ecran
** le premier parametre est le termcap en question, affcnt est le nombre de
** ligne affectee, putc est la fonction qui va afficher le termcap en question
** exemple:
**	char *cl_cap = tgetstr("cl", NULL);
**	tputs (cl_cap, 1, putchar);
**		Pour afficher le termcap qui clean le terminal.
**		Le troisieme argument est la fonction necessaire pour afficher la chaine
**		en question
** 2eme exemple:
** char *cm = tgetstr("le", NULL);
** tputs(tgoto(cm, 6, 6), 0, fputchar);
**		Pour afficher le termcap qui positionne le curseur
*/

/*
** commandes:
** le: "deplacer le curseur de 1 vers la gauche";
** nd: "deplacer le curseur de 1 vers la droite";
** RI: "deplacer le curseur de x vers la droie";
** LE: "deplacer le curseur de x vers la gauche";
** UP: "deplacer le curseur de x vers le haut";
** DO: "deplacer le curseur de x vers le bas";
*/
