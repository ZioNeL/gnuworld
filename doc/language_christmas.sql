-- Merry Christmas!

-- Christmas language definition.
-- 19/12/01 - Reed Loden <reed@reedloden.com>.
-- Special thanks to Vampire-.

-- run this once.

INSERT INTO languages VALUES(16, 'CH', 'Christmas', 31337);

DELETE FROM translations WHERE language_id = 16;

COPY "translations" FROM stdin;
16	1	We know choosing a present is difficult, but having an identity crisis is a no-no %s	31337
16	2	Welcome to the Winter Wonderland %s	31337
16	3	Sorry, you don't have the magic to cast that spell :)	31337
16	4	Sorry, the tree %s is empty	31337
16	5	I don't see %s anywhere	31337
16	6	I can't find %s on tree %s	31337
16	7	The tree %s doesn't appear to be in Santa's sled	31337
16	8	You're opped by %s (%s) on %s	31337
16	9	You're voiced by %s (%s) on %s	31337
16	10	%s: You are not in that tree	31337
16	11	%s is already opped in %s	31337
16	12	%s is already voiced in %s	31337
16	13	You're deoped by %s (%s)	31337
16	14	You're devoiced by %s (%s)	31337
16	16	%s is not scared in %s	31337
16	16	%s is not frightened in %s	31337
16	17	%s is snowed out of the Winter Wonderland (Invalid Ornament)	31337
16	18	I'm not in that tree!	31337
16	19	Invalid curse-level range. Valid range is 1-%i.	31337
16	20	Invalid curse duration. Your curse duration can be a maximum of 336 hours.	31337
16	21	curse reason cannot exceed 128 chars	31337
16	22	Specified curse is already in my curse-list!	31337
16	23	The curse %s is already covered by %s	31337
16	24	Invalid minimum level.	31337
16	25	Invalid maximum level.	31337
16	26	elf: %s STARS: %s %s	31337
16	27	tree: %s -- AUTOMODE: %s	31337
16	28	LAST MODIFIED: %s (%s ago)	31337
16	29	** CHARMED ** - Expires in %s (Level %i)	31337
16	30	LAST SEEN: %s ago.	31337
16	31	There are more than 15 matching entries.	31337
16	32	Please restrict your query.	31337
16	33	End of stars list	31337
16	34	No Match!	31337
16	35	Cannot add an elf that will have equal or more stars than you have.	31337
16	36	Invalid stars level.	31337
16	37	%s is already added to %s with stars level %i.	31337
16	38	Added elf %s to %s with stars level %i	31337
16	39	Something went wrong: %s	31337
16	40	%s: End of curse list	31337
16	41	That elf is under an invisible spell, therefore, you cannot view elf details	31337
16	42	Information about: %s (%i)	31337
16	43	Currently logged on via: %s	31337
16	44	URL: %s	31337
16	45	Language: %i	31337
16	46	Trees: %s	31337
16	47	Input Flood Points: %i	31337
16	48	Ouput Flood (Bytes): %i	31337
16	49	%s is registered by:	31337
16	50	%s - last seen: %s ago	31337
16	51	Desc: %s	31337
16	52	Flood me will you? I'm spoiled so I'm not going to listen to you anymore! :p	31337
16	53	I think I've sent you a little too much data, I'm going to ignore you for a while.	31337
16	54	Incomplete command	31337
16	55	To use %s, you must /msg %s@%s	31337
16	56	Sorry, You must give a present to use this command.	31337
16	57	The tree %s has been suspended by one of Santa's North Pole Helpers.	31337
16	58	Your stars on %s has been suspended.	31337
16	59	The NOOP flag is set on %s	31337
16	60	The STRICTOP flag is set on %s	31337
16	61	You just scared more than %i people	31337
16	62	SYNTAX: %s	31337
16	63	Temporarily increased your stars on tree %s to %i	31337
16	64	%s is present in Santa's sled.	31337
16	65	%s is not present in Santa's sled.	31337
16	66	I don't think %s would appreciate that.	31337
16	67	\002*** Curse List for Tree %s ***\002	31337
16	68	%s %s Level: %i	31337
16	69	ADDED BY: %s (%s)	31337
16	70	SINCE: %s	31337
16	71	EXP: %s	31337
16	72	\002*** END ***\002	31337
16	73	I don't know who %s is.	31337
16	74	Someone has taken your present from you.	31337
16	75	%s doesn't appear to have stars in %s.	31337
16	76	Cannot modify an elf with equal or more stars than you have.	31337
16	77	Cannot give an elf more or equal stars than you have.	31337
16	78	Modified %s's stars level on tree %s to %i	31337
16	79	Set AUTOMODE to OP for %s on tree %s	31337
16	80	Set AUTOMODE to VOICE for %s on tree %s	31337
16	81	Set AUTOMODE to NONE for %s on tree %s	31337	
16	82	Your secret ornament cannot be your elfname or current nick - syntax is: NEWPASS <new passphrase>	31337
16	83	Ornament successfully changed.	31337
16	84	The NOOP flag is set on %s	31337
16	85	The STRICTOP flag is set on %s (and %s isn't authenticated)	31337
16	86	The STRICTOP flag is set on %s (and %s has insufficient stars)	31337
16	87	%s is frozen in ice never to be thawed	31337
16	88	%s is already registered with me.	31337
16	89	Invalid tree name.	31337
16	90	Registered tree %s	31337
16	91	Removed %s from my silence list	31337
16	92	Couldn't find %s in my silence list	31337
16	93	Cannot remove an elf with equal or more stars than you have	31337
16	94	You can't remove yourself from a tree you own	31337
16	95	Removed elf %s from %s	31337
16	96	You have casted an INVISIBLE SPELL on yourself.	31337
16	97	You have revoked the INVISIBLE SPELL on yourself.	31337
16	98	%s for %s is %s	31337
16	99	value of %s must be ON or OFF	31337
16	100	Invalid ELFFLAGS setting. Correct values are 0, 1, 2.	31337
16	101	ELFFLAGS for %s is %i	31337
16	102	value of MASSDEOPPRO has to be 0-7	31337
16	103	MASSDEOPPRO for %s is set to %d	31337
16	104	value of FLOODPRO has to be 0-7	31337
16	105	FLOODPRO for %s is set to %d	31337
16	106	The DESCRIPTION can be a maximum of 80 chars!	31337
16	107	DESCRIPTION for %s is cleared.	31337
16	108	DESCRIPTION for %s is: %s	31337
16	109	The URL can be a maximum of 75 chars!	31337
16	110	URL for %s is cleared.	31337
16	111	URL for %s is: %s	31337
16	112	The string of keywords cannot exceed 80 chars!	31337
16	113	KEYWORDS for %s are: %s	31337
16	114	Language is set to %s.	31337
16	116	ERROR: Invalid language selection.	31337
16	116	Can't locate tree %s on the network!	31337
16	117	ERROR: Invalid tree setting.	31337
16	118	Ignore list:	31337
16	119	Ignore list is empty	31337
16	120	-- End of Ignore List	31337
16	121	CMaster Tree Services internal status:	31337
16	122	[Tree Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
16	123	[Elf Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
16	124	[Stars Level Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
16	125	[Curse Record Stats] \002Cached Entries:\002 %i    \002DB Requests:\002 %i    \002Cache Hits:\002 %i    \002Efficiency:\002 %.2f%%	31337
16	126	Last received Elf NOTIFY: %i	31337
16	127	Last received Tree NOTIFY: %i	31337
16	128	Last received Level NOTIFY: %i	31337
16	129	Last received Curse NOTIFY: %i	31337
16	130	Custom data containers allocated: %i	31337
16	131	\002Uptime:\002 %s	31337
16	132	tree %s has %d elfs (%i operators)	31337
16	133	Mode is: %s	31337
16	134	Flags set: %s	31337
16	135	Cannot suspend an elf with equal or more stars than you have.	31337
16	136	bogus time units	31337
16	137	Invalid suspend duration.	31337
16	138	SUSPENSION for %s is cancelled	31337
16	139	%s is already suspended on %s	31337
16	140	SUSPENSION for %s will expire in %s	31337
16	141	ERROR: Topic cannot exceed 145 chars	31337
16	142	You have insufficient stars to remove the curse %s from %s's database	31337
16	143	Removed %i curses that matched %s	31337
16	144	Removed your temporary stars of %i from tree %s	31337
16	145	You don't appear to have forced stars in %s, perhaps it expired?	31337
16	146	%s isn't suspended on %s	31337
16	147	%s is one of Santa's reindeer	31337
16	148	%s does not believe in Santa Claus.	31337
16	149	%s is listed in Santa's Book as %s%s	31337
16	150	%s is an Official North Pole Helper%s and logged in as %s	31337
16	151	%s is a Generous Official North Pole Helper%s and logged in as %s	31337
16	152	%s is an Angel%s and logged in as %s	31337
16	153	There are more than %i entries matching [%s]	31337
16	154	Please restrict your search mask	31337
16	155	No matching entries for [%s]	31337
16	156	%s: Cleared tree modes.	31337
16	158	Invalid option.	31337
16	159	%s is an Official UnderNet Red-Nosed Reindeer.	31337
16	160	%s is an Official Coder-Com Representative%s and logged in as %s	31337
16	161	%s is an Official Coder-Com Contributer%s and logged in as %s	31337
16	162	%s is an Official Coder-Com Developer%s and logged in as %s	31337
16	163	%s is an Official Coder-Com Senior%s and logged in as %s	31337
16	164	 and is one of Santa's reindeer	31337
16	165	Added curse %s to %s at level %i	31337
16	166	%s: curse list is empty.		31337
16	167	I'm already in that tree!	31337
16	168	This command is reserved to Santa's reindeer	31337
16	169	I'm not opped on %s	31337
16	170	%s for %i minutes	31337
\.