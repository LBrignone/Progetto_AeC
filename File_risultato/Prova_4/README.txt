PROVA ESEGUITA CON FILE DI DATABASE CONTENUTI NELLA CARTELLA "da_File_Test_2" CON INSERT DEI FILE IN
CARTELLA "File_Test_5"
Questa prova è stata eseguita per l'AA 2007-2008, anno di programmazione delle sessioni esami.

Questo test è teso a verificare il corretto scheduling per gli esami spenti, con corretta rilevazione del semestre, e contestuale verifica di coerenza rispetto ai corsi a lui raggruppati, inoltre si verifica anche il comportamento del rilassamento del constrain 4, per cui è prevista la segnalazione nei warning e la non programmazione dell'esame stesso.
In particolare:
01AAAAG --> schedulato come corso spento e raggruppato a 01AAABN
01AAAAT --> non schedulato causa assenza di un'aula capace di contenerlo
01AAABe --> schedulato come corso spento
01AAABN --> schedulato come corso spento e raggruppato a 01AAAAG
01AAABN --> schedulato come corso attivo per il secondo semestre

PER MAGGIORE DETTAGLI VEDERE IL "README.txt" nella cartella "File_Test_5"