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

    /home/nadahman/Desktop/minishell$ cat | bash: syntax error near unexpected token `|' faire comme pour les redirections

    regarder le parsing pour "|" quqnd y a un caractere avant les guillemets

tester tout ca et faire fonctionner correctement, ou attendre d etre a lecole pour tester sur l ordi labas echo salut | exit echo salut | export

avec l ancienne versiion ca fonctionne, a voir ce que j ai fais

il faudra allouer la structure data

02-04

    <!-- gerer espace -->
    mettre un message d erreur qund on exit avec des arguments
    gerer la valeur de retour pou commande interne
    <!-- export | ls et ls | export a gerer -->
    <!-- la variable PATH ne se suprime pas avec unset -->



03-04
<!-- - voir si c est export ou non le probleme -->
<!-- - pareil pour env "ls | env" est cense donne env    -->
<!-- - faire le path -->
- heredoc doit s ouvrir avec << et rien avant faire en sorte de rajouter cat devant si il n yest pas deja 

<!-- - corriger les segfaults /mnt/c/users/nasim/desktop/minishell$ <
bash: syntax error near unexpected token `newline'
/mnt/c/users/nasim/desktop/minishell$ < ls
[34]    117184 segmentation fault (core dumped)  ./minishell                    // a cause du malloc dans le main 
revoir comment je l avais corriger avant
et tester ducoup commande avec redirections etc
- Test << redirection (il n'est pas nécessaire de mettre à jour l'historique). -->

<!-- - quand je test des espaces vides ou tabs et qu ensuite je fais entree lorsque je test une commande ca ne l execute pas -->

- expr $? + $

- controle C dans les cat sans arguments grep qqchose ou redirection

- ca "ls | grep c | wc -l" ne fait rien mais en bash il ecris command not found dans le notre

<!-- - ls | export doit fonctionner et montrer export -->

<!-- - tester redirection dans pipe et comparer avec bash -->

<!-- - quand je fais entrer ca ecris un M retester cat cat ls -->


07-04

- regarder a l ecole si j ai le soucis de double free quand je fais "cat >>" ou autre
- regarder aussi les fd non fermer et les fermer