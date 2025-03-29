# minishell

![alt text](<Screenshot from 2025-02-20 13-25-26.png>)



- valeur de retour
- faire la gestion des signaux selon la ou on se trouve et adapte
- afficher le conitrole C quqnd on quitte
- exit code au milieu des signaux qui doit donner une autre valeur je crois
qund tu control c dans un cat par exemple tu dois avoir un exit code different


tests speciaux

cat | cat | ls

export PIPE="|"
echo $PIPE




pouvoir executer minishell dans minishell et faire controle c


- gerer cd avec plusieurs arguments pareil pour les autres commandes internes a voir ya
- ajouter les valeurs de retour fonction interne ya

<!-- - regler la double sortie "/home/nadahman/Desktop/minishell$ /home/nadahman/Desktop/minishell$" quqnd je ctrl c ou autre nas # je pense qu il faut integrer les signaux dans les redirections a voir
- faut que apres les redirections sa soit un fichier valide sinon gerer -->

- controle heredoc ya
- faire que controle z ne fasse rien ya



- gerer variable expansion guillemet simple : echo '$USER' ya

<!-- - gerer ca export VAL="|" nas
- tester bien les pipes et les redirections nas
- les sorties d erreeurs doivent etre bien ecris et gerer 
- faire la gestion des signaux selon la ou on se trouve et adapter en fonction
- lancer minishell dans minishell sans tout casser et control c -->

-leaks
-norminette




27-03

- /home/nadahman/Desktop/minishell$ cat |
bash: syntax error near unexpected token `|'
faire comme pour les redirections

- regarder le parsing pour "|" quqnd y a un caractere avant les guillemets


echo $? ne fonctionne plus
le cat ne fonctionne plus 
