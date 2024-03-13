Pentru prima cerință, am creat o listă pentru echipe, în care fiecare element din listă conține o listă de jucători. Am parcurs fișierul și am umplut lista de echipe și de jucători. Apoi am afișat lista rezultată.

Pentru a doua cerință, am căutat cele n echipe cu cel mai mare punctaj și am eliminat echipele cu punctajul cel mai mic (numărul total de echipe minus n echipe). Am eliminat echipele una câte una, căutând în fiecare iterație echipa cu cel mai mic punctaj, până când am ajuns la n echipe rămase.

Pentru a treia cerință, am creat o funcție numită "tournament" care primește coada "team_queue" cu meciurile. În interiorul unei bucle "while" până când numărul de echipe este egal cu 1, am folosit funcția "matches" pentru a selecta echipele și funcția "select_winner" pentru a alege câștigătorul fiecărui meci. Am creat, de asemenea, două stive separate pentru pierzători și câștigători. Când numărul de echipe ajunge la 8, am copiat conținutul cozii de meciuri curente într-o listă.

Pentru a patra cerință, am creat funcția "createBST" care creează un arbore binar de căutare folosind lista creată la cerința 3. Am parcurs arborele inordine pentru a afișa echipele în ordine crescătoare.

Pentru a cincea cerință, am creat funcția "createAVL" care ar trebui să creeze un arbore AVL echilibrat. 