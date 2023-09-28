# UDP_Smart_Set2023

I dispositivi domotici di nuova generazione (punti luce, elementi di condizionamento climatico, prese di alimentazione per elettrodomestici, ...) si connettono alla rete WiFi: essi sono comandati mediante datagram UDP – specifici per ciascuna tipologia di dispositivo – indirizzati alla porta 23365; tutti i dispositivi accettano i seguenti comandi: 

• ON tempo (accensione: il parametro tempo rappresenta il numero di secondi dopo il quale effettuare l’accensione, se 0 è immediata): il primo byte del datagram è 1, il tempo è un valore numerico contenuto nel secondo byte del datagram;
• OFF tempo (spegnimento: il parametro tempo rappresenta il numero di secondi dopo il quale effettuare lo spegnimento, se 0 è immediato): il primo byte del datagram è 0, il tempo è un valore numerico contenuto nel secondo byte del datagram.

In ogni caso il dispositivo che riceve un comando invia al programma che lo ha inviato una delle seguenti risposte: 

• OK (comando accettato): il primo byte del datagram vale 1;
• ERR (comando rifiutato): il primo byte del datagram vale 0.

Realizzare due programmi in linguaggio C/C++ per sistema operativo Linux (ON e OFF ) che, quando eseguiti, inviino al dispositivo, il cui indirizzo IP viene fornito come primo argomento della riga di comando, rispettivamente i comandi ON e OFF con valore del parametro tempo fornito come secondo argomento della riga di comando: entrambi i programmi devono attendere per un periodo massimo di un secondo la risposta da parte del dispositivo prima di visualizzare all’utente l’esito del comando. Allo scopo di verificare il corretto funzionamento del programma di comando è richiesta la realizzazione di un programma che simuli il comportamento di un dispositivo domotico rispondendo OK a ogni comando corretto ricevuto, o ERR in caso di comando non corretto.
