-- Language Definition Table for CMaster Undernet channel services.
-- English language definition.
-- 27/12/00 - Greg Sikorski <gte@atomicrevs.demon.co.uk>.
-- 01/03/01 - Daniel Simard <svr@undernet.org>.

DELETE FROM languages;
COPY "languages" FROM stdin;
1	English	31337
2	French	31337
3	Danish	31337
4	Dutch	31337
5	German	31337
6	Portuguese	31337
\.

DELETE FROM translations;
COPY "translations" FROM stdin;
1	1	Sorry, You are already authenticated as %s	31337
1	2	AUTHENTICATION SUCCESSFUL as %s	31337
1	3	Sorry, you have insufficient access to perform that command	31337
1	4	Sorry, the channel %s is empty	31337
1	5	I don't see %s anywhere	31337
1	6	I can't find %s on channel %s	31337
1	7	The channel %s doesn't appear to be registered	31337
1	8	You're opped by %s (%s)	31337
1	9	You're voiced by %s (%s)	31337
1	10	%s: You are not in that channel	31337
1	11	%s is already opped in %s	31337
1	12	%s is already voiced in %s	31337
1	13	You're deopped by %s (%s)	31337
1	14	You're devoiced by %s (%s)	31337
1	15	%s is not opped in %s	31337
1	16	%s is not voiced in %s	31337
1	17	AUTHENTICATION FAILED as %s (Invalid Password)	31337
1	18	I'm not in that channel!	31337
1	19	Invalid banlevel range. Valid range is 1-%i.	31337
1	20	Invalid ban duration. Your ban duration can be a maximum of 336 hours.	31337
1	21	Ban reason cannot exceed 128 chars	31337
1	22	Specified ban is already in my banlist!	31337
1	23	The ban %s is already covered by %s	31337
1	24	Invalid minimum level.	31337
1	25	Invalid maximum level.	31337
1	26	USER: %s ACCESS: %s %s	31337
1	27	CHANNEL: %s -- AUTOMODE: %s	31337
1	28	LAST MODIFIED: %s (%s ago)	31337
1	29	** SUSPENDED ** - Expires in %s	31337
1	30	LAST SEEN: %s ago.	31337
1	31	There are more than 15 matching entries.	31337
1	32	Please restrict your query.	31337
1	33	End of access list	31337
1	34	No Match!	31337
1	35	Cannot add a user with equal or higher access than your own.	31337
1	36	Invalid access level.	31337
1	37	%s is already added to %s with access level %i.	31337
1	38	Added user %s to %s with access level %i	31337
1	39	Something went wrong: %s	31337
1	40	%s: End of ban list	31337
1	41	Unable to view user details (Invisible)	31337
1	42	Information about: %s (%i)	31337
1	43	Currently logged on via: %s	31337
1	44	URL: %s	31337
1	45	Language: %i	31337
1	46	Channels: %s	31337
1	47	Input Flood Points: %i	31337
1	48	Ouput Flood (Bytes): %i	31337
1	49	%s is registered by:	31337
1	50	%s - last seen: %s ago	31337
1	51	Desc: %s	31337
1	52	Flood me will you? I'm not going to listen to you anymore	31337
1	53	I think I've sent you a little too much data, I'm going to ignore you for a while.	31337
1	54	Incomplete command	31337
1	55	To use %s, you must /msg %s@%s	31337
1	56	Sorry, You must be logged in to use this command.	31337
1	57	The channel %s has been suspended by a cservice administrator.	31337
1	58	Your access on %s has been suspended.	31337
1	59	The NOOP flag is set on %s	31337
1	60	The STRICTOP flag is set on %s	31337
1	61	You just deopped more than %i people	31337
1	62	SYNTAX: %s	31337
1	63	Temporarily increased your access on channel %s to %i	31337
1	64	%s is registered.	31337
1	65	%s is not registered.	31337
1	66	I don't think %s would appreciate that.	31337
1	67	\002*** Ban List for channel %s ***\002	31337
1	68	%s %s Level: %i	31337
1	69	ADDED BY: %s (%s)	31337
1	70	SINCE: %i	31337
1	71	EXP: %s	31337
1	72	\002*** END ***\002	31337
1	73	Sorry, I don't know who %s is.	31337
1	74	Sorry, you are not authorized with me anymore.	31337
1	75	doesn't appear to have access in %s.	31337
1	76	Cannot modify a user with equal or higher access than your own.	31337
1	77	Cannot give a user higher or equal access to your own.	31337
1	78	Modified %s's access level on channel %s to %i	31337
1	79	Set AUTOMODE to OP for %s on channel %s	31337
1	80	Set AUTOMODE to VOICE for %s on channel %s	31337
1	81	Set AUTOMODE to NONE for %s on channel %s	31337	
1	82	Your passphrase cannot be your username or current nick - syntax is: NEWPASS <new passphrase>	31337
1	83	Password successfully changed.	31337
1	84	The NOOP flag is set on %s	31337
1	85	The STRICTOP flag is set on %s (and %s isn't authenticated)	31337
1	86	The STRICTOP flag is set on %s (and %s has insufficient access)	31337
1	87	Purged channel %s	31337
1	88	%s is already registered with me.	31337
1	89	Invalid channel name.	31337
1	90	Registered channel %s	31337
1	91	Removed %s from my silence list	31337
1	92	Couldn't find %s in my silence list	31337
1	93	Cannot remove a user with equal or higher access than your own	31337
1	94	You can't remove yourself from a channel you own	31337
1	95	Removed user %s from %s	31337
1	96	Your INVISIBLE setting is now ON.	31337
1	97	Your INVISIBLE setting is now OFF.	31337
1	98	%s for %s is %s	31337
1	99	value of %s must be ON or OFF	31337
1	100	Invalid USERFLAGS setting. Correct values are 0, 1, 2.	31337
1	101	USERFLAGS for %s is %i	31337
1	102	value of MASSDEOPPRO has to be 0-7	31337
1	103	MASSDEOPPRO for %s is set to %d	31337
1	104	value of FLOODPRO has to be 0-7	31337
1	105	FLOODPRO for %s is set to %d	31337
1	106	The DESCRIPTION can be a maximum of 80 chars!	31337
1	107	DESCRIPTION for %s is cleared.	31337
1	108	DESCRIPTION for %s is: %s	31337
1	109	The URL can be a maximum of 75 chars!	31337
1	110	URL for %s is cleared.	31337
1	111	URL for %s is: %s	31337
1	112	The string of keywords cannot exceed 80 chars!	31337
1	113	KEYWORDS for %s are: %s	31337
1	114	Language is set to %s.	31337
1	115	ERROR: Invalid language selection.	31337
1	116	Can't locate channel %s on the network!	31337
1	117	ERROR: Invalid channel setting.	31337
1	118	Ignore list:	31337
1	119	Ignore list is empty	31337
1	120	-- End of Ignore List	31337
1	121	CMaster Channel Services internal status:	31337
1	122	[     Channel Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
1	123	[        User Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
1	124	[Access Level Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
1	125	[         Ban Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
1	126	Last recieved User NOTIFY: %i	31337
1	127	Last recieved Channel NOTIFY: %i	31337
1	128	Last recieved Level NOTIFY: %i	31337
1	129	Last recieved Ban NOTIFY: %i	31337
1	130	Custom data containers allocated: %i	31337
1	131	\002Uptime:\002 %s	31337
1	132	Channel %s has %d users (%i operators)	31337
1	133	Mode is: %s	31337
1	134	Flags set: %s	31337
1	135	Cannot suspend a user with equal or higher access than your own.	31337
1	136	bogus time units	31337
1	137	Invalid suspend duration.	31337
1	138	SUSPENSION for %s is cancelled	31337
1	139	%s is already suspended on %s	31337
1	140	SUSPENSION for %s will expire in %s	31337
1	141	ERROR: Topic cannot exceed 145 chars	31337
1	142	You have insufficient access to remove the ban %s from %s's database	31337
1	143	Removed %i bans that matched %s	31337
1	144	Removed your temporary access of %i from channel %s	31337
1	145	You don't appear to have a forced access in %s, perhaps it expired?	31337
1	146	%s isn't suspended on %s	31337
1	147	%s is an IRC operator	31337
1	148	%s is NOT logged in.	31337
1	149	%s is logged in as %s%s	31337
1	150	%s is an Official CService Representative%s and logged in as %s	31337
1	151	%s is an Official CService Administrator%s and logged in as %s	31337
1	152	%s is an Official CService Developer%s and logged in as %s	31337
1	153	There are more than %i entries matching [%s]	31337
1	154	Please restrict your search mask	31337
1	155	No matching entries for [%s]	31337
1	156	%s: Cleared channel modes.	31337
1	158	Invalid option.	31337
1	159	%s is an Official Undernet Service Bot.	31337
1	160	Added ban %s to %s at level %i	31337
1	161	%s: ban list is empty.		31337
1	162	I'm already in that channel!	31337
\.

-- French language definition.
-- 29/12/00 - Daniel Simard <svr@undernet.org>.
-- 01/03/01 - Daniel Simard <svr@undernet.org>.

COPY "translations" FROM stdin;
2	1	D�sol�. Vous �tes d�j� authentifi� avec le nick %s	31337
2	2	AUTHENTICATION R�USSIE pour %s	31337
2	3	D�sol�. Votre acc�s est insuffisant pour utiliser cette commande	31337
2	4	D�sol�. Le canal %s est vide	31337
2	5	Je suis incapable de trouver %s	31337
2	6	Je ne vois pas %s sur le canal %s	31337
2	7	Le canal %s ne semble pas �tre enregistr�	31337
2	8	Vous avez �t� op par %s (%s)	31337
2	9	Vous avez �t� voice par %s (%s)	31337
2	10	%s: Vous n'�tes pas dans ce canal	31337
2	11	%s est d�j� op sur %s	31337
2	12	%s est d�j� voice sur %s	31337
2	13	Vous avez �t� deop par %s (%s)	31337
2	14	Vous avez �t� devoice par %s (%s)	31337
2	15	%s n'est pas op sur %s	31337
2	16	%s n'est pas voice sur %s	31337
2	17	AUTHENTIFICATION REFUS�E pour %s (Mot-de-passe Invalide)	31337
2	18	Je ne suis pas dans ce canal!!	31337
2	19	Niveau de ban invalide. Niveau valide: entre 1-%i.	31337
2	20	Duration du ban invalide. La duration maximale est de 336 heures.	31337
2	21	La raison d'un ban ne peut d�passer 128 caract�res.	31337
2	22	Ce ban est d�j� dans ma liste!	31337
2	23	Le ban %s est dej� affect� par %s	31337
2	24	Niveau minimum invalide.	31337
2	25	Niveau maximum invalide.	31337
2	26	USAGER: %s NIVEAU: %s %s	31337
2	27	CANAL: %s -- AUTOMODE: %s	31337
2	28	DERNI�RE MODIFICATION: %s (%s avant)	31337
2	29	** SUSPENDU ** - Expire dans %s	31337
2	30	DERNI�RE FOIS VU: %s avant.	31337
2	31	Il y a plus de 15 requ�tes trouv�es.	31337
2	32	SVP restreindre votre requ�te	31337
2	33	Fin de la liste des acc�s	31337
2	34	Aucune correspondace trouv�e	31337
2	35	Vous ne pouvez additionner un usager au m�me niveau que vous ou plus �lev�. 	31337
2	36	Niveau d'acc�s invalide	31337
2	37	%s a d�j� �t� ajout� sur %s au niveau %i.	31337
2	38	Addition de l'usager %s sur %s au niveau %i	31337
2	39	Quelque chose semble incorrecte: %s	31337
2	40	%s: fin de la liste de ban		31337
2	41	Impossible de visualiser les d�tails de l'usager (Invisible).	31337
2	42	Information � propos de: %s (%i)	31337
2	43	Pr�sentement connect� via: %s	31337
2	44	URL: %s	31337
2	45	Langue: %i	31337
2	46	Canaux: %s	31337
2	47	Entr�e Flood: %i	31337
2	48	Sortie Flood (Bytes): %i	31337
2	49	%s a �t� enregistr� par:	31337
2	50	%s - vu pour la derni�re fois: %s avant	31337
2	51	Desc: %s	31337
2	52	Floodez moi voulez-vous? Je ne vais plus vous r�pondre dor�navant.	31337
2	53	Je crois que je vous ai envoy� beaucoup trop d'informations. Je vais vous ignorer un peu.	31337
2	54	Commande incompl�te	31337
2	55	Pour utiliser %s, Vous devez /msg %s@%s	31337
2	56	D�sol�. Vous devez �tre authentifi� pour utiliser cette commande.	31337
2	57	Le canal %s a �t� suspendu par un administrateur de cservice.	31337
2	58	Votre access sur %s a �t� suspendu.	31337
2	59	Le mode NOOP est actif sur %s	31337
2	60	Le mode STRICTOP est actif sur %s	31337
2	61	Vous venez de deop plus de %i personnes	31337
2	62	SYNTAXE: %s	31337
2	63	Temporairement authentifi� sur %s au niveau %i	31337
2	64	%s est enregistr�.	31337
2	65	%s n'est pas enregistr�.	31337
2	66	Je ne crois pas que %s appr�cierait �a.	31337
2	67	\002*** Liste de Ban pour le canal %s ***\002	31337
2	68	%s %s Niveau: %i	31337
2	69	AJOUT� PAR: %s (%s)	31337
2	70	DEPUIS: %i	31337
2	71	EXP: %s	31337
2	72	\002*** FIN ***\002	31337
2	73	D�sol�, Je ne sais pas qui est %s.	31337
2	74	D�sol�, Vous n'�tes plus authentifi�.	31337
2	75	Aucune acc�s correspondant sur %s.	31337
2	76	Vous ne pouvez pas modifier un usager au m�me niveau ou sup�rieur � vous.	31337
2	77	Vous ne pouvez pas donner un acc�s � un usager au m�me niveau ou sup�rieur � vous.	31337
2	78	Modification du niveau de %s sur le canal %s � %i	31337
2	79	Activation du MODE Automatique (OP) pour %s sur le canal %s	31337
2	80	Activation du MODE Automatique (VOICE) pour %s sur le canal %s	31337
2	81	D�sactivation des MODES Automatiques pour %s sur le canal %s	31337	
2	82	Votre mot de passe ne peut �tre votre nom d'usager ni votre nick - La Syntaxe est: NEWPASS <nouveau mot-de-passe>	31337
2	83	Votre mot de passe a �t� chang� avec succ�s.	31337
2	84	Le mode NOOP est actif sur %s	31337
2	85	Le mode STRICTOP est actif sur %s (et %s n'est pas authentifi�)	31337
2	86	Le mode STRICTOP est actif sur %s (et l'acc�s de %s est insuffisant)	31337
2	87	%s a �t� purg�	31337
2	88	%s est d�j� enregistr� avec moi.	31337
2	89	Nom de canal invalide.	31337
2	90	%s a �t� enregistr�	31337
2	91	Enlev� %s de ma liste silence/ignore	31337
2	92	Incapable de trouver %s dans ma liste silence/ignore	31337
2	93	Vous ne pouvez pas effacer un acc�s donc le niveau est �gal ou plus �lev� que le votre.	31337
2	94	Vous ne pouvez pas effacer votre acc�s sur un canal que vous poss�dez.	31337
2	95	L'acc�s de l'usager %s a �t� effac� sur %s	31337
2	96	Le mode INVISIBLE pour vos options confidentiels est maintenant � ON.	31337
2	97	Le mode INVISIBLE pour vos options confidentiels est maintenant � OFF.	31337
2	98	%s pour %s est %s	31337
2	99	La valeur de %s doit �tre ON ou OFF	31337
2	100	Configuration USERFLAGS invalide! Les valeurs correctes sont 0, 1, 2.	31337
2	101	Le USERFLAGS de %s est %i	31337
2	102	La valeur de MASSDEOPPRO doit �tre entre 0-7	31337
2	103	MASSDEOPPRO de %s a �t� configur� � %d	31337
2	104	La valeur de FLOODPRO doit �tre entre 0-7	31337
2	105	FLOODPRO de %s a �t� configur� � %d	31337
2	106	La DESCRIPTION ne doit pas d�passer 80 caract�res.	31337
2	107	La DESCRIPTION de %s a �t� �ffac�.	31337
2	108	La DESCRIPTION de %s est: %s	31337
2	109	L'URL ne doit pas d�passer 75 caract�res.	31337
2	110	L'URL de %s a �t� effac�.	31337
2	111	L'URL de %s est: %s	31337
2	112	Les KEYWORDS (MotsCl�s) ne doivent pas d�passer 80 caract�res.	31337
2	113	KEYWORDS de %s sont: %s	31337
2	114	Langue activ�: %s.	31337
2	115	ERREUR: S�lection d'une langue invalide.	31337
2	116	Le canal %s est introuvable sur le r�seau!	31337
2	117	ERREUR: Configuration de canal invalide.	31337
2	118	Liste d'Ignor�(s):	31337
2	119	La liste d'ignore est vide	31337
2	120	-- Fin de la liste d'ignore 	31337
2	121	Status interne du Service de Canaux CMaster:	31337
2	122	[          Statistiques du Canal] \002Entr�es en cache:\002 %i    \002Requ�tes BaseD:\002 %i    \002# de fois Cache touch�:\002 %i    \002Efficacit�:\002 %.2f%%	31337
2	123	[           Statistiques Usagers] \002Entr�es en cache:\002 %i    \002Requ�tes BaseD:\002 %i    \002# de fois Cache touch�:\002 %i    \002Efficacit�:\002 %.2f%%	31337
2	124	[   Statistiques niveaux d'acc�s] \002Entr�es en cache:\002 %i    \002Requ�tes BaseD:\002 %i    \002# de fois Cache touch�:\002 %i    \002Efficacit�:\002 %.2f%%	31337
2	125	[          Statistiques des bans] \002Entr�es en cache:\002 %i    \002Requ�tes BaseD:\002 %i    \002# de fois Cache touch�:\002 %i    \002Efficacit�:\002 %.2f%%	31337
2	126	Derni�re r�ception NOTIFY d'usager: %i	31337
2	127	Derni�re r�ception NOTIFY de canal: %i	31337
2	128	Derni�re r�ception NOTIFY de niveau: %i	31337
2	129	Derni�re r�ception NOTIFY de ban: %i	31337
2	130	Donn�es assign�es: %i	31337
2	131	\002En fonction depuis (uptime):\002 %s	31337
2	132	Le canal %s a %d usager(s) (%i op�rateurs)	31337
2	133	Le(s) Mode(s) du canal: %s	31337
2	134	Flags activ�s: %s	31337
2	135	Vous ne pouvez pas suspendre un usager au m�me niveau que vous ni sup�rieur.	31337
2	136	Unit� de temps invalide.	31337
2	137	Dur�e de suspension invalide.	31337
2	138	La SUSPENSION pour %s a �t� annul�.	31337
2	139	%s est d�j� suspendu sur %s	31337
2	140	La SUSPENSION pour %s va expirer dans %s	31337
2	141	ERREUR: Le topic ne peut d�passer 145 caract�res.	31337
2	142	votre acc�s est insuffisant pour enlever le ban %s de la base de donn�es de %s	31337
2	143	Supprim� %i ban(s) qui figuraient %s	31337
2	144	Supprim� votre acc�s temporaire de niveau %i du canal %s	31337
2	145	Vous ne semblez pas d'avoir forcer l'acc�s � %s, Serait-elle expir�e?	31337
2	146	%s n'est pas suspendu sur %s	31337
2	147	%s est un Op�rateur IRC	31337
2	148	%s n'est pas authentifi�.	31337
2	149	%s est authentifi� via le userid %s%s	31337
2	150	%s est un repr�sentant Officiel de CService%s et authentific� via le userid %s	31337
2	151	%s est un Administrateur Officiel de CService%s et authentific� via le userid %s	31337
2	152	%s est un Programmeur Officiel de CService%s et authentific� via le userid %s	31337
2	153	Il y a plus de %i entr�es figurants [%s]	31337
2	154	Veuillez svp restreindre votre requ�te.	31337
2	155	Aucune entr�e figurante pour votre requ�te. [%s]	31337
2	156	%s: Les modes du canal on �t� effac�s.	31337
2	158	Option invalide.	31337
2	159	%s est un Service Officiel du r�seau Undernet.	31337
2	160	Addition du ban %s sur %s au niveau %i	31337
2	161	%s: la liste des bans est vide.		31337
2	162	Je suis d�j� sur ce canal!	31337
\.

-- Danish language definition.
-- 28/12/2000 - David Henriksen <david@itwebnet.dk>.

COPY "translations" FROM stdin;
3	1	Beklager, Du er allerede autoriseret som %s	31337
3	2	AUTORISATION LYKKEDES som %s	31337
3	3	Beklager, du har utilstr�kkelig adgang til at udf�re den kommando	31337
3	4	Beklager, kanalen %s er tom	31337
3	5	Jeg kan ikke se %s nogen steder	31337
3	6	Jeg kan ikke finde %s p� kanalen %s	31337
3	7	Kanelen %s ser ikke ud til at v�re registreret	31337
3	8	Du er op'et af %s (%s)	31337
3	9	Du er voice'et af %s (%s)	31337
\.

-- Dutch language definition.
-- 30/12/2000 - Sebastian Serruys <sebastian.serruys@pandora.be>.

COPY "translations" FROM stdin;
4	1	Sorry, Je bent reeds geautoriseerd als %s	31337
4	2	AUTORISATIE SUCCESVOL als %s	31337
4	3	Sorry, je hebt onvoldoende toegang om dat commando uit te voeren	31337
4	4	Sorry, het kanaal %s is leeg	31337
4	5	Ik zie nergens %s	31337
4	6	Ik kan %s niet vinden op het kanaal %s	31337
4	7	Het kanaal %s ziet er niet geregistreerd uit	31337
4	8	Je bent geopt door %s (%s)	31337
4	9	Je bent gevoiced door %s (%s)	31337
4	10	%s: Je bent niet in dat kanaal	31337
\.

-- German language definition.
-- 03/01/2001 - Alexander Maassen <outsider@key2peace.org>.

COPY "translations" FROM stdin;
5	1	Sorry, Du bist schon authorisiert als %s	31337
5	2	AUTHORISATION als %s ACCEPTIERT	31337
5	3	Sorry, du hast zu wenig access fr dieses commando	31337
5	4	Sorry, Channel %s ist lehr	31337
5	5	Ich kann %s nirgendwo sehen	31337
5	6	Ich kann %s nicht im Channel %s sehen	31337
5	7	Channel %s is nicht registriert	31337
5	8	%s (%s) hat dich geopt	31337
5	9	%s (%s) hat dich gevoiced	31337
5	10	%s: Du bist nicht im Channel	31337
5	11	%s wurde bereits von %s geopt	31337
\.


-- Portuguese language definition.
-- 02/03/01 - Ed Cattuci <maniac@undernet.org>

COPY "translations" FROM stdin;
6	1	Sorry, You are already authenticated as %s	31337
6	2	AUTHENTICATION SUCCESSFUL as %s	31337
6	3	Sorry, you have insufficient access to perform that command	31337
6	4	Sorry, the channel %s is empty	31337
6	5	I don't see %s anywhere	31337
6	6	I can't find %s on channel %s	31337
6	7	The channel %s doesn't appear to be registered	31337
6	8	You're opped by %s (%s)	31337
6	9	You're voiced by %s (%s)	31337
6	10	%s: You are not in that channel	31337
6	11	%s is already opped in %s	31337
6	12	%s is already voiced in %s	31337
6	13	You're deopped by %s (%s)	31337
6	14	You're devoiced by %s (%s)	31337
6	15	%s is not opped in %s	31337
6	16	%s is not voiced in %s	31337
6	17	AUTHENTICATION FAILED as %s (Invalid Password)	31337
6	18	I'm not in that channel!	31337
6	19	Invalid banlevel range. Valid range is 1-%i.	31337
6	20	Invalid ban duration. Your ban duration can be a maximum of 336 hours.	31337
6	21	Ban reason cannot exceed 128 chars	31337
6	22	Specified ban is already in my banlist!	31337
6	23	The ban %s is already covered by %s	31337
6	24	Invalid minimum level.	31337
6	25	Invalid maximum level.	31337
6	26	USER: %s ACCESS: %s %s	31337
6	27	CHANNEL: %s -- AUTOMODE: %s	31337
6	28	LAST MODIFIED: %s (%s ago)	31337
6	29	** SUSPENDED ** - Expires in %s	31337
6	30	LAST SEEN: %s ago.	31337
6	31	There are more than 15 matching entries.	31337
6	32	Please restrict your query.	31337
6	33	End of access list	31337
6	34	No Match!	31337
6	35	Cannot add a user with equal or higher access than your own. 	31337
6	36	Invalid access level.	31337
6	37	%s is already added to %s with access level %i.	31337
6	38	Added user %s to %s with access level %i	31337
6	39	Something went wrong: %s	31337
6	40	%s: End of ban list		31337
6	41	Unable to view user details (Invisible)	31337
6	42	Information about: %s (%i)	31337
6	43	Currently logged on via: %s	31337
6	44	URL: %s	31337
6	45	Language: %i	31337
6	46	Channels: %s	31337
6	47	Input Flood Points: %i	31337
6	48	Ouput Flood (Bytes): %i	31337
6	49	%s is registered by:	31337
6	50	%s - last seen: %s ago	31337
6	51	Desc: %s	31337
6	52	Flood me will you? I'm not going to listen to you anymore	31337
6	53	I think I've sent you a little too much data, I'm going to ignore you for a while.	31337
6	54	Incomplete command	31337
6	55	To use %s, you must /msg %s@%s	31337
6	56	Sorry, You must be logged in to use this command.	31337
6	57	The channel %s has been suspended by a cservice administrator.	31337
6	58	Your access on %s has been suspended.	31337
6	59	The NOOP flag is set on %s	31337
6	60	The STRICTOP flag is set on %s	31337
6	61	You just deopped more than %i people	31337
6	62	SYNTAX: %s	31337
6	63	Temporarily increased your access on channel %s to %i	31337
6	64	%s is registered.	31337
6	65	%s is not registered.	31337
6	66	I don't think %s would appreciate that.	31337
6	67	\002*** Ban List for channel %s ***\002	31337
6	68	%s %s Level: %i	31337
6	69	ADDED BY: %s (%s)	31337
6	70	SINCE: %i	31337
6	71	EXP: %s	31337
6	72	\002*** END ***\002	31337
6	73	Sorry, I don't know who %s is.	31337
6	74	Sorry, you are not authorized with me anymore.	31337
6	75	doesn't appear to have access in %s.	31337
6	76	Cannot modify a user with equal or higher access than your own.	31337
6	77	Cannot give a user higher or equal access to your own.	31337
6	78	Modified %s's access level on channel %s to %i	31337
6	79	Set AUTOMODE to OP for %s on channel %s	31337
6	80	Set AUTOMODE to VOICE for %s on channel %s	31337
6	81	Set AUTOMODE to NONE for %s on channel %s	31337	
6	82	Your passphrase cannot be your username or current nick - syntax is: NEWPASS <new passphrase>	31337
6	83	Password successfully changed.	31337
6	84	The NOOP flag is set on %s	31337
6	85	The STRICTOP flag is set on %s (and %s isn't authenticated)	31337
6	86	The STRICTOP flag is set on %s (and %s has insufficient access)	31337
6	87	Purged channel %s	31337
6	88	%s is already registered with me.	31337
6	89	Invalid channel name.	31337
6	90	Registered channel %s	31337
6	91	Removed %s from my silence list	31337
6	92	Couldn't find %s in my silence list	31337
6	93	Cannot remove a user with equal or higher access than your own	31337
6	94	You can't remove yourself from a channel you own	31337
6	95	Removed user %s from %s	31337
6	96	Your INVISIBLE setting is now ON.	31337
6	97	Your INVISIBLE setting is now OFF.	31337
6	98	%s for %s is %s	31337
6	99	value of %s must be ON or OFF	31337
6	100	Invalid USERFLAGS setting. Correct values are 0, 1, 2.	31337
6	101	USERFLAGS for %s is %i	31337
6	102	value of MASSDEOPPRO has to be 0-7	31337
6	103	MASSDEOPPRO for %s is set to %d	31337
6	104	value of FLOODPRO has to be 0-7	31337
6	105	FLOODPRO for %s is set to %d	31337
6	106	The DESCRIPTION can be a maximum of 80 chars!	31337
6	107	DESCRIPTION for %s is cleared.	31337
6	108	DESCRIPTION for %s is: %s	31337
6	109	The URL can be a maximum of 75 chars!	31337
6	110	URL for %s is cleared.	31337
6	111	URL for %s is: %s	31337
6	112	The string of keywords cannot exceed 80 chars!	31337
6	113	KEYWORDS for %s are: %s	31337
6	114	Language is set to %s.	31337
6	115	ERROR: Invalid language selection.	31337
6	116	Can't locate channel %s on the network!	31337
6	117	ERROR: Invalid channel setting.	31337
6	118	Ignore list:	31337
6	119	Ignore list is empty	31337
6	120	-- End of Ignore List	31337
6	121	CMaster Channel Services internal status:	31337
6	122	[     Channel Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
6	123	[        User Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
6	124	[Access Level Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
6	125	[         Ban Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
6	126	Last recieved User NOTIFY: %i	31337
6	127	Last recieved Channel NOTIFY: %i	31337
6	128	Last recieved Level NOTIFY: %i	31337
6	129	Last recieved Ban NOTIFY: %i	31337
6	130	Custom data containers allocated: %i	31337
6	131	\002Uptime:\002 %s	31337
6	132	Channel %s has %d users (%i operators)	31337
6	133	Mode is: %s	31337
6	134	Flags set: %s	31337
6	135	Cannot suspend a user with equal or higher access than your own.	31337
6	136	bogus time units	31337
6	137	Invalid suspend duration.	31337
6	138	SUSPENSION for %s is cancelled	31337
6	139	%s is already suspended on %s	31337
6	140	SUSPENSION for %s will expire in %s	31337
6	141	ERROR: Topic cannot exceed 145 chars	31337
6	142	You have insufficient access to remove the ban %s from %s's database	31337
6	143	Removed %i bans that matched %s	31337
6	144	Removed your temporary access of %i from channel %s	31337
6	145	You don't appear to have a forced access in %s, perhaps it expired?	31337
6	146	%s isn't suspended on %s	31337
6	147	%s is an IRC operator	31337
6	148	%s is NOT logged in.	31337
6	149	%s is logged in as %s%s	31337
6	150	%s is an Official CService Representative%s and logged in as %s	31337
6	151	%s is an Official CService Administrator%s and logged in as %s	31337
6	152	%s is an Official CService Developer%s and logged in as %s	31337
6	153	There are more than %i entries matching [%s]	31337
6	154	Please restrict your search mask	31337
6	155	No matching entries for [%s]	31337
6	156	%s: Cleared channel modes.	31337
6	158	Invalid option.	31337
6	159	%s is an Official Undernet Service Bot.	31337
6	160	Added ban %s to %s at level %i	31337
6	161	%s: ban list is empty.		31337
6	162	I'm already in that channel!	31337
\.
