# FT_IRC

## Docs :
 - https://modern.ircdocs.horse/
 - https://github.com/marineks/Ft_irc

## Infos :
 - Signaux a gerer (priorite) : CTRL+C, CTRL+D, CTRL+Z
 - Tout les inputs du client DOIVENT finir par "\r\n" pour eviter les EOF inattendu

A suggestion of project roadmap : 1- Begin by establishing a working client/server socket connection, 2- Then build on that : add the signals handling (CTRL+C, CTRL+D, CTRL+Z); 3- Only then begin the client registration system (NICK, USER, PASS), 4- The server commands (PING, OPER, KILL...) and 5- The channel operations commands (JOIN, PART, INVITE, KICK, PRIVMSG, NOTICE...).

### server functions :
  - getaddrinfo -> recupere ton adresse pour socket
  - socket -> creer un fd pour communiquer a distance (fd donc doit close)
  - bind -> lie le fd au port local
  #### boucle infini :
    - poll / epoll -> permet d'eviter d'avoir un programme bloquant en regardant si des fd clients sont dispo ou non
	#### for poll_count :
	  #### if fd == server :
	   - accept -> rajoute les nouveaux fd clients
	  #### else :
	   - recv -> recoit les messages envoye par les clients
	   #### if recv <= 0 :
	     - client disconnect = close le socket
	   #### else :
	     - client a envoyer qqch, interpreter