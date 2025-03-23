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


derniere version
<!-- - commande vide ca net un message pareil pour espace et tab il faut enlever     nas    #c'est fait -->

- gerer cd avec plusieurs arguments pareil pour les autres commandes internes a voir ya
- ajouter les valeurs de retour fonction interne ya

<!-- - regler la double sortie "/home/nadahman/Desktop/minishell$ /home/nadahman/Desktop/minishell$" quqnd je ctrl c ou autre nas # je pense qu il faut integrer les signaux dans les redirections a voir
- faut que apres les redirections sa soit un fichier valide sinon gerer -->

- controle heredoc ya
- faire que controle z ne fasse rien ya
- gerer les quotes /home/nadahman/Desktop/minishell$ ech""o ya
  command not found: ech""o

<!-- - gerer les commandes avec des arguments vide ou incorrect comme sa : cat > "" nas # c est fait normalement a tester encore --> 

- gerer variable expansion guillemet simple : echo '$USER' ya

<!-- - gerer ca export VAL="|" nas
- regarder Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right. nas # c est fait
- tester bien les pipes et les redirections nas
- les sorties d erreeurs doivent etre bien ecris et gerer 
- faire la gestion des signaux selon la ou on se trouve et adapter en fonction
- lancer minishell dans minishell sans tout casser et control c -->

-leaks
-norminette