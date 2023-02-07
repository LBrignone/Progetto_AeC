Su database creato dai file in File_Test_2, eccetto quelli ri-generati presenti in questa cartella

I file contenuti in questa cartella servono a verificare lo spegnimento dei corsi, e il loro conseguente spostamento da attivi a non attivi nei corsi di studio in cui sono usati.
Si vuole in particolare verificare la doppia permanenza attivo - non attivo nel caso non vengano spenti tutti gli anni accademici per un dato corso e la cancellazione dalla programmazione "standard" (primo semestre / secondo semestre) nel caso in cui vengano spenti tutti gli anni accademici per un dato corso.

Uno scheduling è eseguito per verificare la corretta gestione, in particolare:
01AAAAG --> viene spento solo l'anno accademico 2007-2008 (1/1)
01AAAAT --> viene spento solo l'anno accademico 2020-2021 (1/0/0)
01AAABE --> viene spento l'anno accademico 2007-2008 e 2021-2022 (1/0)
01AAABN --> viene spento l'unico anno accademico 2007-2008 (1)
01AAABQ --> non subisce modifiche rimanendo attivo (1)
(Tra parentesi è indicata la configurazione di partenga del database per i corsi in questione con:
1 --> attivo, 0 --> non attivo
Le operazioni che verranno eseguite saranno di tipo differenziale rispetto alla configurazione iniziale)

- SI FA NOTARE CHE UNA PRIMA VERIFICA DIELLO SPEGNIMENTO DEI CORSI È STATA EFFETTUATA CON I FILE 
  CONTENUTI NELLA CARTELLA "File_Test_2"

- una generazione dello scheduling è stata fatta senza avere indisponibilità dei professori per 
  l'anno accademico preso in considerazione (2007-2008)

- potrebbero esserci errori di incongruenza con i raggruppamenti essendo che non sono stati 
  modificati i corsi raggruppati