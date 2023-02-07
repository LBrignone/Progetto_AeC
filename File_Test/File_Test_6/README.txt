Su database creato dai file in File_Test_2, eccetto quelli ri-generati presenti in questa cartella

I file contenuti in questa cartella servono a verificare la riattivazione dei corsi, e la verifica,
per i corsi di studio in cui sono inseriti, se il corso di studi è presente nei corsi spenti e:
	1. tutti gli AA di quel corso erano spenti, e almeno uno diventa attivo, la copia
	   dai corsi spenti e l'inserimento nei corsi nel corretto semestre di riferimento
	2. tutti gli AA di quel corso passano da spento ad attivo, la cancellazione del
	   corso dai corsi spenti
	3. almeno un AA di quel corso era attivo, e più di un corso era spento, il 
	   mantenimento dell'id del corso sia nei corsi spenti che nei corsi attivi
	4. almeno un AA di quel corso era attivo, e solo un corso era spento, la 
	   cancellazione dai corsi spenti, senza modificarne la posizione del corso stesso 
	   nei corsi attivi
In particolare per quanto riguarda i casi 1 e 2, essendosi perso il riferimento per il semestre del corso sarà necessario operare un update dei corsi di studio in cui il corso si trovava, successivamente alla cancellazione del corso dai corsi spenti.

In particolare si modificheranno i seguenti corsi:
01AAAAD --> viene aggiunto l'anno accademico 2013-2014 come spento	|
	    viene spento l'anno accademico 2020-2021			|(0/0)
	    viene attivato l'anno 2013-2014
01AAAAI --> viene spento l'anno accademico 2013-2014			|(0/1/0)
	    viene attivato l'anno accademico 2021-2022
01AAAAZ --> viene aggiunto l'anno accademico 2013-2014 come spento	|(0/1/1)
	    viene attivato l'anno accademico 2013-2014
01AAABD --> viene spento l'anno accademico 2013-2014			|(0)
	    viene attivato l'anno accademico 2013-2014
01AAABJ --> viene spento l'anno accademico 2013-2014 e 2022-2023	|(0/0)
	    vengono riattivati entrambi gli anni accademici
(Tra parentesi è indicata la configurazione dei corsi dopo le prime modifiche riportate sulla sinistra, si 
indica con:
1 --> attivo, 0 --> non attivo (spento))

