-- $Id: greeting.sql,v 1.5 2002/03/11 08:26:10 nighty Exp $
-- spanish + catalan by Algol.
-- norwegian by MrIron.
-- french by nighty.
-- romanian by TheBeast.

DELETE FROM translations where response_id = 9998;
COPY "translations" FROM stdin; 
1	9998	Remember: Nobody from CService will ever ask you for your password, do NOT give out your password to anyone claiming to be CService.	31337	0
2	9998	Rappelez-vous: Jamais personne de CService ne vous demandera votre mot de passe, ne donnez votre mot de passe � personne meme pas � quelqu'un qui dit �tre de CService	31337	0
8	9998	Nu Uita: Nici un reprezentant CService nu iti va cere vreodata parola, NU iti da parola de la username cuiva care spune ca este reprezentant Cservice.	31337	0
9	9998	Recordeu: Cap membre de CService us demanar� mai la vostra contrasenya, NO doneu la vostra contrasenya a ning� encara que afirmi que �s membre de CService	31337	0
10	9998	Recuerda: Ning�n miembro de CService te ha de pedir nunca la contrase�a, NUNCA des tu contrase�a a nadie aunque afirme que es miembro de CService	31337	0
13	9998	Husk: Ingen fra CService vil noen gang sp�rre deg om ditt passord, s� derfor m� du ALDRI gi det til noen som utgir seg for � v�re med i CService	31337	0
\.
