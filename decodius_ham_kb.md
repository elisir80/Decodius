# Knowledge Base Radioamatoriale di Decodius
# Generata e verificata da workflow multi-agente. Operatore: IU8LMC (Italia, IARU R1).
# Consultata dallo strumento ham_kb. Dati variabili (frequenze/normativa): verificare MIMIT, ARI, IARU, AMSAT.



## Bande radioamatoriali e piani di banda HF/VHF/UHF/SHF (IARU Regione 1 e Italia)

L'Italia appartiene alla **IARU Regione 1**. Le bande assegnate al servizio di amatore sono definite dal **PNRF** (Piano Nazionale di Ripartizione delle Frequenze, gestito dal **MIMIT**) e i segmenti per modo dal **bandplan IARU R1** (raccomandazione, non legge, ma rispettata per convivenza). La normativa italiana di riferimento è il **Codice delle comunicazioni elettroniche** (D.Lgs. 259/2003, **Allegato 26**, aggiornato dal D.Lgs. 48/2024). Verifica sempre attribuzioni e potenze sul PNRF vigente (MIMIT) e su ARI.

### Potenze (Italia)
- **Classe A**: **500 W PEP** (potenza di picco fornita alla linea di alimentazione dell'antenna), stazioni fisse o mobili/portatili.
- **Classe B** (patente conseguita con esame ridotto, ex Novice): **50 W PEP**.
- **Stazioni ripetitrici automatiche non presidiate**: limite espresso in **ERP** (potenza efficace irradiata rispetto al dipolo).
- I **60 m** hanno limite specifico (vedi sotto). Su **2200 m (135,7–137,8 kHz)** e **630 m (472–479 kHz)** valgono limiti EIRP ridotti (tipicamente 1 W EIRP su 2200 m, 5 W EIRP su 630 m).

> Nota: la classe inferiore NON è limitata a "10 W EIRP" — quel valore non corrisponde alla normativa italiana (classe B = 50 W PEP).

### Bande HF (segmenti chiave IARU R1, MHz)

| Banda | Estremi (MHz) | CW (estremi) | Centro attività SSB / note |
|---|---|---|---|
| 160 m | 1.810–1.850 | 1.810–1.838 | SSB da 1.840; FT8 ~1.840; digitali ~1.838 |
| 80 m | 3.500–3.800 | 3.500–3.570 | SSB da 3.600; FT8 3.573 |
| 60 m | 5.3515–5.3665 | tutto (≤500 Hz) | max **15 W EIRP**, secondario; **SSB in USB**; FT8 5.357 |
| 40 m | 7.000–7.200 | 7.000–7.040 | SSB da 7.060; FT8 7.074 |
| **30 m (WARC)** | 10.100–10.150 | tutto | **no fonia/SSB**, solo CW/digitali; FT8 10.136 |
| 20 m | 14.000–14.350 | 14.000–14.070 | SSB da 14.101; FT8 14.074 |
| **17 m (WARC)** | 18.068–18.168 | 18.068–18.095 | SSB da 18.111; FT8 18.100 |
| 15 m | 21.000–21.450 | 21.000–21.070 | SSB da 21.151; FT8 21.074 |
| **12 m (WARC)** | 24.890–24.990 | 24.890–24.915 | SSB da 24.931; FT8 24.915 |
| 10 m | 28.000–29.700 | 28.000–28.070 | SSB da 28.225; FT8 28.074; FM >29.200; satelliti/ripetitori in alto |

**Bande WARC** (30/17/12 m, dalla WARC-1979): **vietati i contest**; sui **30 m** niente SSB (solo CW e digitali).

### Frequenze QRP e di chiamata
- **CW QRP**: 1.836, 3.560, 7.030, 10.116, 14.060, 18.086, 21.060, 24.906, 28.060.
- **SSB QRP**: 3.690, 7.090, 14.285, 18.130, 21.285, 24.950, 28.360.
- **SSB chiamata DX**: 14.195 / 14.230 (centro attività generale SSB 14.101+); chiamata SSB QRP 14.285.
- **Centres of Activity / emergenza**: vedi il bandplan IARU R1 (es. 3.760, 7.110, 14.300, 18.160, 21.360 come Global Centre of Activity for emergency communications).

### VHF / UHF (R1, MHz)
- **6 m**: 50.000–52.000 (in Italia attribuzione/condizioni da verificare sul PNRF/MIMIT). CW/EME in basso, SSB centro **50.150**, FT8 **50.313**, FM in alto; beacon 50.400–50.500.
- **4 m (70 MHz)**: in Italia **non** assegnato in via generale; eventuali autorizzazioni speciali/temporanee — verificare MIMIT.
- **2 m**: 144.000–146.000. CW/EME 144.000–144.110; SSB centro **144.300**; FT8 144.174; chiamata SSB 144.300; ingressi ripetitori FM 145.600–145.800 con shift **−0.6 MHz**; satelliti 145.800–146.000; chiamata FM **145.500**.
- **70 cm**: 430.000–440.000. SSB centro **432.200**; FT8 432.174; ripetitori FM con shift **−1.6 MHz** (uscite 433.x, ingressi 431.x); chiamata FM **433.500**; satelliti 435.000–438.000.

### SHF (R1)
- **23 cm**: 1240–1300 MHz (attenzione alla protezione di **Galileo/RNSS**, restrizioni in corso a seguito di WRC-23/decisioni CEPT — verificare MIMIT/IARU). SSB/EME centro 1296.200.
- **13 cm**: 2300–2450 MHz (in Italia segmento spesso ridotto/condiviso — verificare).
- **9 cm**: 3400–3475 MHz.
- **6 cm**: 5650–5850 MHz (**QO-100**: uplink 2400 MHz, downlink 10489 MHz).
- **3 cm**: 10000–10500 MHz.
- Bande superiori: **24 GHz** (24000–24250), **47 GHz** (47000–47200), **76 GHz** (76000–81000) e oltre.

### Procedura operativa: scelta segmento
1. Identifica la banda secondo licenza/classe e propagazione.
2. Consulta il bandplan IARU R1 per il **modo** (CW in basso, poi digitali a banda stretta, SSB, FM/ripetitori in alto).
3. **Convenzione SSB**: su **160/80/40 m** si usa **LSB**; **da 20 m in su** si usa **USB**; le digitali si trasmettono **sempre in USB**. Eccezione: sui **60 m** si usa **USB** anche se sotto i 10 MHz.
4. Ascolta prima di trasmettere ("is this frequency in use?" / "QRL?"), rispetta i centri di attività e i segmenti satellitari/EME.
5. Verifica potenza massima e status (primario/secondario) sul PNRF prima di operare.

Dati ufficiali aggiornati: **MIMIT** (PNRF, decreti, Codice comunicazioni elettroniche – Allegato 26), **ARI**, **IARU R1** (bandplan HF/VHF/UHF/SHF), **AMSAT** (satelliti).

## Normativa italiana per radioamatori: patente, autorizzazione, classi e potenze

Il quadro di riferimento è il **Codice delle Comunicazioni Elettroniche (D.Lgs. 259/2003 e s.m.i.)**, **Allegato n. 26** (modificato dal DM 1° marzo 2021), gestito dal **MIMIT** (ex MISE). Verifica sempre gli aggiornamenti su mimit.gov.it, sul portale ispettorati.mise.gov.it e presso ARI.

> **Nota di aggiornamento (2026):** con il **DM 26 gennaio 2026** (G.U. n. 51 del 3 marzo 2026) è stata introdotta la nuova **Classe N** (radioamatore novizio, corrispondente alla raccomandazione **CEPT ECC/REC (05)06**), con restrizioni di frequenza e potenza. I dettagli tecnici sono in fase di implementazione: verificare i decreti attuativi.

### Patente e autorizzazione generale
Sono due atti distinti:
1. **Patente di radioamatore**: titolo a carattere permanente rilasciato dall'Ispettorato Territoriale MIMIT dopo il superamento dell'esame (prova scritta a quiz su tecnica/elettroradiotecnica, normativa e regolamenti, più operazioni di trasmissione/ricezione ove previste). **Non scade.**
2. **Autorizzazione generale**: titolo che abilita all'impianto e all'esercizio della stazione. Si consegue presentando una **dichiarazione** (SCIA, in genere via PEC) all'Ispettorato Territoriale competente. Ha **durata fino a 10 anni**, rinnovabile (richiesta di rinnovo da presentare almeno **60 giorni** prima della scadenza).

**Contributi (aggiornamento dal 5 luglio 2023):**
- Per le **nuove autorizzazioni** è dovuto un **contributo una tantum di 50,00 euro** per l'intero periodo di validità decennale (non più 5 euro annui).
- Per le autorizzazioni **già in essere** alla data di entrata in vigore della modifica, resta dovuto il **contributo annuo di 5,00 euro** fino alla naturale scadenza.
- Dal **1° ottobre 2024** i versamenti vanno effettuati tramite il **portale pagamenti DGST** (pagamentidgst.mimit.gov.it).

### Classi
- **Classe A (piena)**: armonizzata secondo **CEPT T/R 61-01**; nessuna limitazione specifica oltre a quelle del PNRF e dell'Allegato 26. Richiede l'esame completo.
- **Classe N (novizio)**: corrispondente alla **CEPT ECC/REC (05)06**, con **restrizioni di bande e potenza** rispetto alla Classe A. È la classe introdotta in Italia dal DM gennaio 2026 (in precedenza la distinzione "Classe B/Novice" non era operativamente attiva in Italia; il vecchio riferimento "T/R 61-02" non è corretto). Verifica le condizioni operative attuali presso MIMIT/ARI.

### Potenze massime
La potenza è definita come **p.e.p. — peak envelope power** (potenza di picco dell'inviluppo: potenza media fornita alla linea di alimentazione dell'antenna durante un ciclo a radiofrequenza in corrispondenza della massima ampiezza dell'inviluppo di modulazione). **Non** è la "potenza media".

| Classe / Banda | Potenza massima (p.e.p.) |
|----------------|--------------------------|
| **Classe A** — tutte le bande attribuite (HF, 50 MHz, 144 MHz, 432 MHz, microonde) | **500 W** |
| **Classe N** (novizio) | **potenza ridotta** secondo i limiti del decreto attuativo (tipicamente alcune decine di W; verificare) |

- Su richiesta sono possibili **autorizzazioni speciali per potenze superiori** (fino a **1 kW**) per attività particolari (sperimentazione, contest, alcune stazioni ripetitrici).
- I limiti restano comunque subordinati al rispetto dei vincoli di **esposizione ai campi elettromagnetici** (DPCM 8 luglio 2003 e D.Lgs. 259/2003).

### Bande e PNRF
Le frequenze attribuite al servizio di amatore seguono il **PNRF (Piano Nazionale di Ripartizione delle Frequenze)** e, per l'uso operativo, il **band plan IARU Regione 1**. Esempi (segmenti italiani principali):
- **10 m**: 28,000–29,700 MHz
- **6 m**: 50,000–52,000 MHz (in Italia tipicamente fino a 51 o 52 MHz; **servizio secondario**)
- **2 m**: 144,000–146,000 MHz
- **70 cm**: 430,000–440,000 MHz

Alcune bande sono attribuite a titolo **secondario** (es. 50 MHz, 70 MHz dove ammesso in via sperimentale): in tali bande l'amatore **non deve causare interferenze** ai servizi primari e **non può pretendere protezione** dalle interferenze da essi causate.

### Nominativo
Assegnato dal MIMIT. Per l'Italia il **prefisso** è composto dalle lettere internazionali assegnate (**I**, e gruppi **IA–IZ**); i prefissi comuni includono **I, IK, IZ, IW, IU** (i nominativi **IU** sono i più recenti per le nuove licenze). Struttura: **prefisso + cifra del distretto (0–9, su base geografica) + suffisso** (es. IK0XYZ, IZ8ABC, IU2DEF).
Sono possibili **nominativi speciali/contest** a carattere temporaneo o di sezione, con prefissi quali **II, IO, IR, IQ** (tipicamente **IQ** per le stazioni di sezione ARI), su richiesta.

### Registro di stazione (log)
L'obbligo formale di tenuta del **registro di stazione** è stato **abolito** con le semplificazioni introdotte nell'Allegato 26. La tenuta di un log resta **fortemente raccomandata** (per QSL, contest, diari di attività e gestione interferenze). Verificare sempre l'obbligo vigente presso MIMIT.

### Esercizio mobile e portatile
- **/M (mobile)**: stazione installata su veicolo/mezzo in movimento.
- **/P (portatile)**: stazione operante da postazione provvisoria diversa dalla sede dichiarata.

La condizione si indica **dopo** il nominativo (es. *IK0XYZ/P*, *IK0XYZ/M*). Per gli **impianti fissi** ubicati in luogo diverso dalla sede dell'autorizzazione è prevista un'apposita comunicazione/integrazione.

Per l'**operatività in altri Paesi CEPT** vale la raccomandazione **CEPT T/R 61-01**: si antepone al proprio nominativo il **prefisso del Paese ospitante** seguito da barra (es. operando in Olanda: *PA/IK0XYZ*). Per i Paesi extra-CEPT che aderiscono alla raccomandazione **ECC/REC (05)06** si applica il regime "novice" equivalente.

---

### Promemoria tecnico — formule antenne
Lunghezze indicative (f in MHz, risultato in metri; includono il fattore di accorciamento medio):
- **Dipolo a mezz'onda (λ/2):** L ≈ **142,5 / f**
- **Verticale a un quarto d'onda (λ/4):** L ≈ **71,25 / f**
- **Lunghezza d'onda in spazio libero (λ):** λ = **300 / f**

(λ/2 = 150/f e λ/4 = 75/f sono i valori teorici in spazio libero; 142,5 e 71,25 sono i valori pratici con fattore di velocità ~0,95.)

### Promemoria — conversioni dB / potenza
- **+3 dB → potenza ×2**; **−3 dB → potenza ÷2**
- **+10 dB → potenza ×10**; **+6 dB → ×4**; **+20 dB → ×100**
- dBW vs dBm: **0 dBW = 30 dBm = 1 W**; **0 dBm = 1 mW**
- P(dBm) = 10·log₁₀(P/1 mW); esempio: 100 W = **+50 dBm = +20 dBW**

*Fonti consultate: Allegato 26 al D.Lgs. 259/2003 (DM 1/3/2021), schede informative e FAQ MIMIT/Ispettorati territoriali (ispettorati.mise.gov.it), DM 26 gennaio 2026 sulla Classe N.*

## Regolamento internazionale ITU: tre Regioni, prefissi ed entità DXCC, zone CQ e zone ITU, allocazioni

### Le tre Regioni ITU
L'ITU divide il mondo in tre Regioni, che determinano le allocazioni di frequenza nel Radio Regulations (RR).
- **Regione 1**: Europa, Africa, Medio Oriente, ex URSS (Federazione Russa e CSI), Mongolia. **L'Italia è in Regione 1.**
- **Regione 2**: Americhe (Nord, Centro, Sud), Groenlandia e isole del Pacifico orientale.
- **Regione 3**: Asia (a est dell'ex URSS e a sud del Medio Oriente in Regione 1), gran parte dell'Oceania e del Pacifico occidentale.

I confini sono definiti da linee (A, B, C) descritte nell'art. 5 RR. Conseguenza pratica: i piani di banda differiscono tra le Regioni. Esempio importante per i 40 m: in Reg. 1 i radioamatori dispongono di **7.000–7.200 kHz** (cioè 7,000–7,200 MHz); in Reg. 2 e in Reg. 3 la banda arriva fino a **7.300 kHz** (7,300 MHz). I 160 m, i 60 m e altre bande hanno limiti diversi per Regione/Paese.

> Nota sulle unità: nel servizio amatoriale le frequenze HF si esprimono comunemente in **kHz** (es. 7100 kHz) o in MHz con virgola decimale (es. 7,100 MHz). Indicare "7.000–7.200 MHz" per i 40 m è un errore di unità: la banda è 7,000–7,200 MHz, cioè 7000–7200 kHz.

### Prefissi ed entità DXCC
I blocchi di prefissi di chiamata sono assegnati dall'ITU agli Stati (**Appendice 42 RR**) e poi distribuiti dalle amministrazioni nazionali. All'Italia sono assegnati i blocchi **I**, e in particolare le serie comprese in **IAA–IZZ**; in pratica si vedono nominativi come **I, IZ, IK, IU, IW, I0–I9** (la cifra indica l'area/distretto di chiamata, es. I0 Lazio, IS0 Sardegna, IT9 Sicilia).
- Le entità **DXCC** sono definite dall'**ARRL** (DXCC List), **NON** dall'ITU: il conteggio si basa su criteri politici/geografici (governo proprio, separazione geografica/distanza, ecc.). Sono attualmente circa **340** entità attive (il numero varia nel tempo). Verificare la lista ufficiale e gli aggiornamenti su **arrl.org/dxcc**.
- Un prefisso **non** corrisponde 1:1 a un'entità. Caso italiano: l'Italia conta come **tre entità DXCC distinte**:
  - **"Italy"** (penisola e isole minori, prefissi I/IZ/IK/IU/IW, IT0/IO, ecc.);
  - **"Sardinia"** (Sardegna), prefisso **IS0** (e IM0), entità DXCC separata;
  - **"Sicily"** (Sicilia), prefisso **IT9**, entità DXCC separata.
- Da non confondere con il programma **IOTA** (Islands On The Air, gestito da **RSGB**): molte isole italiane hanno un riferimento IOTA ma **non** sono entità DXCC separate.

### Zone CQ e zone ITU
Due sistemi di zone DISTINTI, usati in contest e diplomi:

| Sistema | N° zone | Definito da | Uso tipico |
|---|---|---|---|
| **CQ Zones** | 40 | rivista *CQ Magazine* | CQ WW DX, diploma **WAZ** |
| **ITU Zones** | 90 | **ITU** | IARU HF Championship |

L'Italia (penisola) è **CQ Zone 15** e **ITU Zone 28**. Anche la **Sardegna (IS0)** e la **Sicilia (IT9)** ricadono in **CQ 15 / ITU 28**. Riportare la zona corretta nei log è essenziale per la validità dei punteggi.

### Allocazioni amatoriali (servizio amatoriale)
Le bande sono assegnate al servizio amatoriale su base **primaria** o **secondaria**. In status **secondario** non si deve causare interferenza ai servizi primari e non si è protetti dalle interferenze provenienti da essi (caso tipico dei 30 m e di parte di altre bande).

Bande HF principali in Reg. 1 (Italia), valori indicativi del bandplan IARU R1:

| Banda | Frequenze | Status / Note |
|---|---|---|
| 160 m | 1.810–2.000 kHz | allocazione e segmenti variano per Paese; in Italia tipicamente 1.830–1.850 kHz a piena potenza, segmenti superiori con limitazioni |
| 80 m | 3.500–3.800 kHz | |
| 40 m | 7.000–7.200 kHz | **primaria** in Reg. 1; in Reg. 2/3 fino a 7.300 kHz |
| 30 m | 10.100–10.150 kHz | **secondaria**; solo CW/dati per accordo IARU, no fonia (banda WARC) |
| 20 m | 14.000–14.350 kHz | primaria |
| 17 m | 18.068–18.168 kHz | banda WARC |
| 15 m | 21.000–21.450 kHz | primaria |
| 12 m | 24.890–24.990 kHz | banda WARC |
| 10 m | 28.000–29.700 kHz | primaria |

> **Bande "WARC" (30/17/12 m)**: per accordo IARU i **contest sono vietati** su queste bande. (Sono dette WARC perché introdotte alla World Administrative Radio Conference del 1979.)

### Formule pratiche di antenna (promemoria)
Per il calcolo rapido in aria libera (f in MHz):
- **Lunghezza d'onda**: λ (m) = **300 / f**
- **Dipolo a mezz'onda** (lunghezza fisica totale, con fattore di accorciamento ~0,95): L (m) ≈ **142,5 / f**
- **Verticale a quarto d'onda** (con stesso fattore): L (m) ≈ **71,25 / f**

Esempio: per 7,1 MHz → λ ≈ 42,25 m; dipolo ≈ 20,07 m; verticale ≈ 10,04 m.

### Promemoria dB / potenza
Variazioni di potenza espresse in decibel (campo di potenza): dB = 10·log₁₀(P₂/P₁).
- **+3 dB** ≈ potenza ×2; **−3 dB** ≈ potenza ÷2
- **+6 dB** ≈ ×4; **+10 dB** = ×10; **+20 dB** = ×100
- 0 dBW = 1 W; **0 dBm = 1 mW** (1 W = +30 dBm)

### Verifica e fonti
Limiti di **potenza** e condizioni d'uso in Italia **NON** derivano direttamente dall'ITU ma dalla **normativa nazionale**: fare riferimento al **MIMIT** (Ministero delle Imprese e del Made in Italy, ex MISE) e al **Piano Nazionale di Ripartizione delle Frequenze (PNRF)**. In Italia il limite di potenza per la stazione di radioamatore ordinaria è tipicamente **500 W** di potenza nominale (con valori inferiori per particolari casi/autorizzazioni speciali e patenti); verificare sempre l'edizione vigente della normativa.

Per i piani di banda dettagliati: **IARU Region 1 (iaru-r1.org)** e **ARI (ari.it)**. Per i satelliti: **AMSAT**. Per entità DXCC: **ARRL (arrl.org/dxcc)**; per WAZ/zone CQ: **CQ Magazine**. Tutti i dati sono soggetti ad aggiornamento: verificare sempre l'ultima edizione delle fonti ufficiali.

## Modi in fonia: SSB (USB/LSB), AM, FM — tecnica, chiamata e QSO

### I tre modi e quando usarli
- **SSB (Single Side Band)**: modulazione efficiente in banda stretta (~2,4–2,7 kHz); portante e una delle due bande laterali sono soppresse. È il modo principale per i collegamenti a lunga distanza (DX) in HF, perché concentra tutta la potenza nel segnale utile.
- **AM (modulazione d'ampiezza)**: banda larga (~6 kHz) e poco efficiente, perché la portante (sempre presente) assorbe gran parte della potenza. Oggi è una nicchia per appassionati di apparati d'epoca.
- **FM (modulazione di frequenza)**: banda larga (~12–16 kHz per canale), ottimo rapporto S/N quando il segnale supera la soglia, ma con comportamento "tutto o niente" ed **effetto cattura** (il segnale più forte prevale). Usata soprattutto in VHF/UHF, sui ponti ripetitori, e in HF solo nel segmento alto dei 10 m (tipicamente sopra ~29 MHz).

### Regola USB vs LSB
Convenzione operativa consolidata (è solo una **convenzione**, non un obbligo tecnico: la SSB funziona su entrambe le bande laterali):
- **LSB (banda laterale inferiore)**: bande **160 / 80 / 40 m** (1,8 — 3,5 — 7 MHz).
- **USB (banda laterale superiore)**: bande **30 / 20 / 17 / 15 / 12 / 10 m** (10 — 14 — 18 — 21 — 24 — 28 MHz) e tutto ciò che sta sopra, inclusa la SSB in VHF/UHF.
- **USB** è anche lo standard per la maggior parte dei modi digitali e per i satelliti.

> Nota: sui 30 m (10,1 MHz) la fonia **non è ammessa** (segmento riservato a CW e modi digitali in IARU R1); la regola USB si applicherebbe formalmente, ma in pratica non vi si fa fonia.

| Banda | Segmento fonia tipico (MHz) | Modo |
|---|---|---|
| 160 m | 1,840–1,843 (SSB R1) | LSB |
| 80 m | 3,600–3,800 | LSB |
| 40 m | 7,053–7,200 | LSB |
| 20 m | 14,101–14,350 | USB |
| 15 m | 21,151–21,450 | USB |
| 10 m | 28,300–29,100 (SSB) / 29,300–29,510 (FM/satelliti) | USB / FM |
| 2 m | 144,150–144,400 (SSB), centro chiamata 144,300 | USB |

I segmenti esatti seguono il **band plan IARU Regione 1** e, in Italia, il **Piano Nazionale di Ripartizione delle Frequenze (PNRF)** gestito dal **MIMIT** (Ministero delle Imprese e del Made in Italy, ex MISE): verificare sempre lì prima di operare, perché i band plan vengono aggiornati.

**Potenze (Italia).** Con il nuovo quadro normativo (Codice delle comunicazioni elettroniche, D.Lgs. 207/2021, e relativi provvedimenti MIMIT) il limite per i titolari di **patente/autorizzazione generale ordinaria** è stato elevato a **500 W** di potenza (pep). La **patente di classe limitata** (ex classe B/novizio) ha un limite inferiore, tipicamente **10 W**. Restano possibili ulteriori restrizioni per banda, e per impianti di potenza più elevata possono servire autorizzazioni/valutazioni specifiche (esposizione ai campi elettromagnetici). Fa sempre fede la **normativa MIMIT vigente** e la **propria autorizzazione**.

### Tecnica microfonica
- Distanza dal microfono ~5–10 cm; parla leggermente **di lato** (riduce i "pop" sulle consonanti esplosive P/B/T).
- In SSB regola **MIC GAIN** e **compressore (speech processor)** in modo che l'**ALC** oscilli appena nella zona consentita, senza saturare: l'eccesso genera **splatter** che disturba le frequenze adiacenti.
- Voce piena ma naturale. In AM/FM conta più il livello medio di modulazione che il picco; in SSB è il controllo del picco (ALC) ad essere critico.

### Procedura di chiamata (passo-passo)
1. **Ascolta** sulla frequenza per qualche istante.
2. Chiedi: *"È libera la frequenza? Qui IZ0ABC"* (ripetere il proprio nominativo).
3. **CQ generico**: *"CQ CQ CQ, qui India Zulu Zero Alfa Bravo Charlie, chiama e passo"*.
4. **Rispondere a un CQ**: dai solo il **tuo** nominativo in alfabeto fonetico ICAO/NATO (eventualmente preceduto dal nominativo del chiamante una volta).

### Svolgimento del QSO
Scambio minimo: **nominativi + rapporto**. In fonia si usa **RS** (Readability 1–5, Signal strength 1–9), es. *"59"*. Il terzo parametro, il **tono T (1–9)**, fa parte del codice **RST** ma si applica **solo in telegrafia (CW)**: in fonia non si dà. Seguono nome, QTH, locatore (Maidenhead), descrizione di stazione/antenna.

Esempio:
- *"IK4XYZ da IZ0ABC, ricevuto, mi passi 59, nome Marco, QTH Bologna, locatore JN54. Come copi? A te, IK4XYZ da IZ0ABC."*

Chiusura: *"Grazie del contatto, 73, QSL via bureau. IK4XYZ da IZ0ABC, chiudo e... a riascoltarci. 73!"*

### Codici Q e gergo utili
- **QRZ?** = "Chi mi chiama?"
- **QRM** = disturbi causati da altre stazioni (artificiali)
- **QRN** = disturbi atmosferici/naturali
- **QSB** = evanescenza (fading)
- **QRP** = "Devo diminuire la potenza?" / opero a bassa potenza; **QRO** = aumentare la potenza
- **QSY** = cambio di frequenza
- **QTH** = località; **QSL** = conferma del collegamento
- **QSO** = collegamento/contatto
- **73** = saluti cordiali (sempre al plurale, **non** "73s")

Usa l'**alfabeto fonetico ICAO/NATO** (Alfa, Bravo, Charlie, Delta, Echo, Foxtrot, Golf, Hotel, India, Juliett, Kilo, Lima, Mike, November, Oscar, Papa, Quebec, Romeo, Sierra, Tango, Uniform, Victor, Whiskey, X-ray, Yankee, Zulu), evitando varianti improvvisate. Trasmetti **sempre il tuo nominativo** all'inizio e alla fine del collegamento, e a intervalli regolari durante il QSO, come richiede la normativa sull'identificazione della stazione.

### Promemoria tecnico (formule e conversioni)
- **Dipolo a mezz'onda**: lunghezza totale L (m) ≈ **142,5 / f(MHz)** (ogni braccio ≈ 71,25 / f).
- **Verticale a quarto d'onda**: altezza (m) ≈ **71,25 / f(MHz)**.
- **Lunghezza d'onda**: λ (m) = **300 / f(MHz)**.
- **Conversioni dB ⇄ potenza**: +3 dB = **potenza doppia**; +6 dB ≈ ×4; +10 dB = **×10**; +20 dB = ×100. (Analogamente −3 dB = metà potenza.)

## Codice Morse e telegrafia CW

Il CW (Continuous Wave) è la modalità radiotelegrafica in cui la portante non modulata viene interrotta (keying on/off) secondo il codice Morse. Resta diffusissima sulle HF per la sua efficienza in condizioni di basso rapporto segnale/rumore e per l'occupazione di banda estremamente ridotta.

### Unità di tempo
Tutte le durate derivano da una sola unità di base: la durata del **punto (dit)**.

| Elemento | Durata |
|---|---|
| Punto (dit) | 1 unità |
| Linea (dah) | 3 unità |
| Spazio fra elementi dello stesso carattere (intra-carattere) | 1 unità |
| Spazio fra lettere | 3 unità |
| Spazio fra parole | 7 unità |

### WPM e formula PARIS
La velocità si misura in **WPM** (Words Per Minute). La parola di riferimento standard è **PARIS**, che vale esattamente **50 unità** comprensive dello spazio finale fra parole (7 unità). Da qui:

- Durata del punto (ms) = **1200 / WPM**
- WPM = **1200 / (durata punto in ms)**
- Esempi: 20 WPM → punto = 60 ms; 12 WPM → 100 ms; 25 WPM → 48 ms.

In contesti professionali si usa anche il **CPM** (caratteri al minuto), basato sulla parola convenzionale "CODEX" (60 unità). Il metodo **Farnsworth** trasmette i singoli caratteri a una velocità elevata, ma allunga gli spazi fra lettere e parole per ridurre la velocità media: utile in fase di apprendimento per imparare il suono dei caratteri "a regime".

### Tabella alfabeto
A .-  B -...  C -.-.  D -..  E .  F ..-.  G --.  H ....  I ..  J .---  K -.-  L .-..  M --  N -.  O ---  P .--.  Q --.-  R .-.  S ...  T -  U ..-  V ...-  W .--  X -..-  Y -.--  Z --..

### Numeri
0 -----  1 .----  2 ..---  3 ...--  4 ....-  5 .....  6 -....  7 --...  8 ---..  9 ----.

### Punteggiatura principale
. (punto, AAA) .-.-.-  , (virgola, MIM) --..--  ? (IMI) ..--..  / (DN/barra) -..-.  = (BT, doppio trattino) -...-  + (AR, separatore) .-.-.  - (trattino) -....-  : ---...  ( (parentesi aperta, = prosegno KN) -.--.  ) (parentesi chiusa) -.--.-  @ (AC) .--.-.  apostrofo .----.

### Prosegni (prosigns)
Si trasmettono come un unico carattere, **senza lo spazio interno** fra le lettere che li compongono:

| Prosegno | Codice | Significato |
|---|---|---|
| AR | .-.-. | Fine messaggio / "passo a te" |
| SK (VA) | ...-.- | Fine collegamento (chiusura QSO) |
| KN | -.--. | "Solo la stazione chiamata risponda" (invito specifico). Coincide con il codice della parentesi aperta `(` |
| BT (=) | -...- | Separatore di paragrafo / pausa |
| AS | .-... | Attendi un momento (wait) |
| BK | -...-.- | Break, scambio rapido senza convenevoli |
| KA / CT | -.-.- | Inizio trasmissione / "attenzione" |
| HH | ........ | Errore (8 punti); si ripete la parola o la sequenza sbagliata |

### QSO CW tipico passo-passo
1. **Chiamata CQ**: `CQ CQ CQ DE IZ0XXX IZ0XXX K`
2. Risposta: `IZ0XXX DE I1YYY I1YYY KN`
3. Rapporto: `I1YYY DE IZ0XXX GE TKS RST 599 599 NAME MARCO QTH ROMA HW? KN`
4. Scambio dati e chiusura: `... 73 ES GL DE IZ0XXX SK`

**Nota terminologica:** **RST** non è un codice Q, ma il sistema di rapporto del segnale (Readability–Strength–Tone). In CW si usano tutte e tre le cifre (es. 599: leggibilità 5, intensità 9, tono 9); in fonia si usano solo R e S (es. 59).

Codici Q frequenti: **QRZ?** (chi mi chiama?), **QSB** (fading, segnale evanescente), **QRM** (disturbo causato da altre stazioni), **QRN** (disturbo atmosferico/statico), **QSY** (cambio frequenza), **QRP** (bassa potenza, ≤5 W out in CW), **QRO** (alta potenza), **QRT** (cesso la trasmissione), **QTH** (località), **QSL** (conferma / ricevuto).

### Segmenti CW (banda passante stretta, in MHz)
Nel band plan **IARU Regione 1** i segmenti CW iniziano all'inizio di banda. Valori di riferimento:

- 80 m: 3.500–3.570/3.580
- 40 m: 7.000–7.040
- 30 m (solo CW/digitale): 10.100–10.130
- 20 m: 14.000–14.070
- 17 m: 18.068–18.095
- 15 m: 21.000–21.070
- 12 m: 24.890–24.915
- 10 m: 28.000–28.070

Frequenze **"QRP center"** comuni: 3.560, 7.030, 10.106, 14.060, 18.086, 21.060, 24.906, 28.060 MHz.

**Verifica sempre il bandplan ufficiale**: i limiti esatti, le tolleranze e le sottobande variano nel tempo e sono pubblicati da **IARU Region 1** e ripresi in Italia da **ARI**. I vincoli normativi italiani (allocazione delle bande, potenze, classi di patente) sono di competenza del **MIMIT** (Ministero delle Imprese e del Made in Italy, ex MISE). In Italia la potenza massima per le stazioni di radioamatore è di norma **500 W** (e.i.r.p./alimentazione secondo quanto previsto dal Codice delle comunicazioni elettroniche e dal relativo Piano nazionale di ripartizione delle frequenze), ridotta su alcune bande condivise (es. 2200 m / 135,7 kHz e 630 m / 472 kHz, con limiti specifici e bassissima potenza). La patente di classe A consente l'accesso a tutte le bande/potenze previste; la classe B prevede limitazioni. Consulta sempre il quadro normativo MIMIT vigente per i valori esatti.

## Abbreviazioni CW e codici Q

I **codici Q** sono abbreviazioni a tre lettere (sempre inizianti con Q) nate per la telegrafia (CW) e standardizzate dall'ITU; oggi sono usati anche in fonia. Ogni codice ha valore di **domanda** se seguito da punto interrogativo, di **affermazione/risposta** altrimenti. Esempio: "QRZ?" = "Da chi sono chiamato?"; "QRZ" = "Sei chiamato da... (su... kHz)".

### Codici Q più usati (radioamatori)

| Codice | Domanda | Affermazione / significato |
|--------|---------|----------------------------|
| QRA | Qual è il nome della tua stazione? | Il nome della mia stazione è... |
| QRG | Vuoi indicarmi la mia frequenza esatta? | La tua frequenza esatta è... kHz |
| QRL | Sei occupato? | Sono occupato (non interferire) |
| QRM | Sei disturbato (da altre stazioni)? | Ho interferenze (da altre stazioni) |
| QRN | Sei disturbato da scariche atmosferiche? | Ho disturbi atmosferici/statici |
| QRO | Devo aumentare la potenza? | Aumenta la potenza (alta potenza) |
| QRP | Devo diminuire la potenza? | Diminuisci la potenza (bassa potenza) |
| QRQ | Devo trasmettere più veloce? | Trasmetti più veloce (... PARIS al minuto) |
| QRS | Devo trasmettere più lento? | Trasmetti più lentamente |
| QRT | Devo cessare la trasmissione? | Cessa la trasmissione |
| QRU | Hai qualcosa per me? | Non ho nulla per te |
| QRV | Sei pronto? | Sono pronto |
| QRX | Quando mi richiamerai? | Ti richiamerò alle... ore (su... kHz) |
| QRZ | Da chi sono chiamato? | Sei chiamato da... (su... kHz) |
| QSB | La forza dei miei segnali varia (fading)? | La forza dei tuoi segnali varia (fading) |
| QSL | Puoi confermare la ricezione? | Confermo la ricezione (anche: cartolina QSL) |
| QSO | Puoi comunicare con... direttamente? | Posso comunicare con... (collegamento bidirezionale) |
| QSY | Devo cambiare frequenza di trasmissione? | Passa alla frequenza... (kHz) |
| QTH | Qual è la tua posizione (in lat./long. o località)? | La mia posizione/QTH è... |
| QTR | Qual è l'ora esatta? | L'ora esatta è... |

**QRP**: per convenzione IARU indica potenza ridotta, **≤ 5 W output (potenza RF in uscita) in CW e modi digitali** e **≤ 10 W PEP in SSB/fonia**. **QRO** indica funzionamento ad alta potenza, in Italia fino al limite di legge. Il valore di riferimento attuale per i radioamatori italiani è **500 W** (PEP all'antenna) per il normativo ordinario; sono previste autorizzazioni/condizioni particolari per potenze superiori (fino a **1 kW**). I valori sono soggetti a variazioni: verificare sempre il quadro normativo vigente sul sito del **MIMIT** (ex MISE) e nel Codice delle comunicazioni elettroniche.

### Abbreviazioni CW comuni (non codici Q)

| Abbr. | Significato | | Abbr. | Significato |
|-------|-------------|--|-------|-------------|
| CQ | Chiamata generale | | TNX/TKS | Grazie |
| DE | "da" (precede il nominativo del chiamante) | | UR | Your / you are (il tuo / tu sei) |
| K | Passo a te (a chiunque risponda) | | RST | Rapporto: leggibilità-segnale-tono |
| KN | Passo solo alla stazione specifica | | 73 | Cordiali saluti |
| AR | Fine messaggio (+) | | 88 | Baci e abbracci |
| SK | Fine collegamento/contatto | | PSE | Please (per favore) |
| BK | Break (alternanza rapida) | | HI | Risata |
| R | Ricevuto (Roger) | | OM | Old man (operatore) |
| AS | Attendi (wait) | | YL | Young lady (operatrice) |
| ES | "e" (and) | | WX | Meteo (weather) |
| FB | Fine business (molto bene) | | CUL | See you later (a dopo) |
| GM/GA/GE | Good morning/afternoon/evening | | RIG | Apparato (ricetrasmettitore) |

Nota: in CW i prosegni AR, SK, KN, AS, BK si trasmettono come **caratteri uniti** (un solo carattere Morse senza spazio interno), es. AR = di-dah-di-dah-dit.

### Esempio di QSO in CW

`CQ CQ CQ DE IZ0ABC IZ0ABC IZ0ABC K`
`IZ0ABC DE IK1XYZ IK1XYZ K`
`IK1XYZ DE IZ0ABC = GM OM TNX CALL = UR RST 599 599 = NAME LUCA LUCA = QTH MILANO MILANO = HW? AR IK1XYZ DE IZ0ABC KN`

(Il segno `=` corrisponde al prosegno BT, separatore di paragrafo.)

### Procedura QSY (passo-passo)
1. Stazione A propone lo spostamento: `QSY 14060?` (il valore è in **kHz**, cioè 14,060 MHz, segmento CW dei 20 m).
2. Stazione B conferma: `R QSY 14060`.
3. Entrambe sintonizzano la nuova frequenza; A richiama: `IK1XYZ DE IZ0ABC K`.

### Note operative
- In presenza di **QRM/QRN** elevato si usa `QRS` (rallentare), si chiede `QRX` (attesa) e si ricorre a ripetizioni (`AGN` = again, `PSE RPT` = please repeat).
- `QSB` (fading) è una **constatazione**, non un invito: segnala che la forza del segnale varia; in tal caso può convenire ripetere le informazioni durante i picchi del segnale.
- `QRL?` (eventualmente ripetuto due volte) è la buona prassi prima di occupare una frequenza in CW: si attende risposta prima di chiamare CQ.
- Rapporti **RST**: in fonia (SSB/FM) si omette il tono e si dà la coppia leggibilità-segnale (es. "59"); in CW si dà la terna completa comprensiva del tono (es. "599"). La scala è R = 1-5 (leggibilità), S = 1-9 (forza segnale), T = 1-9 (tono, solo CW).

Per piani di banda, segmenti CW/QRP e limiti di potenza aggiornati, consultare **ARI**, **IARU Regione 1** (band plan ufficiale) e il quadro normativo **MIMIT**, poiché frequenze, segmenti e limiti possono variare nel tempo.

## Codice RST e RSQ: come si valuta e si dà un rapporto in CW, fonia e digitale

Il **codice RST** (Readability, Strength, Tone) è lo standard internazionale per riportare la qualità di un segnale ricevuto. Nasce per la telegrafia (CW); in fonia si usa solo **RS** (la T non ha senso perché in SSB/AM/FM non c'è una nota telegrafica da valutare), nei modi digitali a video si è diffuso il sistema **RSQ**.

### Le tre scale RST

| Cifra | R - Comprensibilità (Readability) | S - Intensità (Strength) | T - Tono (Tone, solo CW) |
|---|---|---|---|
| 1 | Incomprensibile | Appena percettibile | Tono estremamente rauco, AC sibilante (50/100 Hz) |
| 2 | Comprensibile a tratti (qualche parola) | Molto debole | Molto rauco, AC, nessuna musicalità |
| 3 | Comprensibile con notevole difficoltà | Debole | Rauco, AC, basso tono di musicalità |
| 4 | Comprensibile con poca difficoltà | Discreto | Tono rauco, un po' di musicalità |
| 5 | Perfettamente comprensibile | Discretamente buono | Tono modulato/filtrato, forte residuo di AC |
| 6 | — | Buono | Tono modulato, evidente residuo di AC |
| 7 | — | Moderatamente forte | Quasi DC, ondulazione (ripple) percepibile |
| 8 | — | Forte | Tono quasi DC, lieve ondulazione/modulazione |
| 9 | — | Fortissimo | Tono puro DC, nessuna traccia di ripple o modulazione |

R va da 1 a 5, S e T da 1 a 9. La **S** corrisponde idealmente alla scala dell'S-meter: **S9** equivale per convenzione IARU Region 1 in HF (sotto i 30 MHz) a **50 µV ai morsetti del ricevitore su carico da 50 ohm**, cioè **-73 dBm**; ogni punto S vale nominalmente **6 dB** (un raddoppio della scala è 6 dB di potenza). Sopra S9 si riporta "S9 + dB" (es. "59 più 20 dB", scritto **+20 dB over S9**). In VHF/UHF lo standard IARU R1 fissa **S9 = -93 dBm** (circa **5 µV** su 50 ohm), cioè 20 dB più basso che in HF. Nota: la taratura reale degli S-meter varia molto tra apparati e raramente rispetta i 6 dB/punto, quindi la S è in pratica spesso una stima soggettiva.

### Come si dà il rapporto

**CW:** si trasmettono tre cifre, es. `599` ("five nine nine"), oppure si premette `RST`, es. `RST 579`. In contest CW il `599` è quasi sempre di prammatica (e spesso si abbrevia in CW con i numeri "tagliati", es. `5NN`). In un QSO normale, per accuratezza, si valuta davvero: un segnale debole ma leggibile e con tono buono = `459`.

**Fonia (SSB/AM/FM):** solo due cifre RS, es. `59` ("cinque nove" o "five nine"). Anche qui in contest il "59" è di rito; in un QSO ragguagliato si dà il valore reale, es. `57`, `44`. In FM si valuta il rumore di fondo: un segnale che apre completamente lo squelch senza fruscio è "full quieting" ("59 pieno"); altrimenti si segnala fruscio/scratch.

### Digitale: RSQ e SNR

Per i modi a video con codifica leggibile a schermo (RTTY, PSK31, ecc.) si usa **RSQ** (Readability-Strength-Quality), dove **Q** (1-9) descrive la purezza dello spettro, cioè il numero di tracce spurie / portanti laterali visibili nel waterfall (Q9 = nessuna spuria, Q1 = numerose tracce parassite). Esempio: `599` o `579`. Le scale R e S in RSQ usano valori dispari (1-3-5-7-9) perché lette dal waterfall e dall'aspetto della traccia.

Per i modi WSJT-X (**FT8, FT4, JT65, JT9, WSPR**) NON si usa l'RST: il rapporto è il **SNR in dB** riferito convenzionalmente a una larghezza di banda di **2500 Hz**, con range tipico da circa **-24 dB a +10 dB** (FT8 decodifica fino a circa -21 dB; JT65 fino a circa -24/-25 dB). Il software lo calcola e lo scambia automaticamente. Nel protocollo lo standard è che il **nominativo del corrispondente viene per primo**, poi il proprio, poi il rapporto: es. il messaggio inviato da IK0XYZ verso DL1ABC è `DL1ABC IK0XYZ -15` (il `-15` è l'SNR con cui IK0XYZ ha ricevuto DL1ABC); un segnale forte si riporta con un valore positivo, es. `+03`.

### Cenni di normativa italiana (utili in QSO)

In Italia l'autorità competente è il **MIMIT** (Ministero delle Imprese e del Made in Italy, ex MISE); il band plan operativo di riferimento è quello **IARU Region 1**, recepito e diffuso anche dall'**ARI**. I limiti di potenza (EIRP/potenza di uscita secondo la classificazione vigente del Codice delle comunicazioni elettroniche e relativo Allegato 26) sono in sintesi: **fino a 500 W** per i titolari di patente/autorizzazione generale ordinaria, e **fino a 10 W** per la classe entry-level (patente con potenza limitata). Su alcune bande condivise o con vincoli specifici (es. 50 MHz, 70 MHz dove ammessa, 472 kHz, 135 kHz) valgono limiti inferiori e condizioni particolari: verificare sempre il piano nazionale aggiornato.

### Verifica e fonti

Le scale RST sono uno standard de facto consolidato (origine ARRL/IARU). Per le definizioni S-meter e le procedure aggiornate consultare: **IARU Region 1** (iaru-r1.org — raccomandazioni tecniche e VHF Handbook, dove sono fissati S9 = -73 dBm in HF e -93 dBm in VHF/UHF), **ARI** (ari.it) per band plan e divulgazione regolamentare, e il manuale **WSJT-X** per il calcolo dell'SNR e i formati di messaggio. La normativa nazionale (potenze, classi di patente, bande) fa capo al **MIMIT**. La correlazione esatta S-meter/dBm è nominale (6 dB per punto S): verificarla con il manuale del proprio RTX, perché la taratura non è normata in modo vincolante.

## Alfabeto fonetico NATO/ICAO e procedure di fonia

L'alfabeto fonetico internazionale (ITU/ICAO/NATO) serve a trasmettere lettere senza ambiguità in fonia (SSB/FM/AM). È lo standard raccomandato anche dalla IARU Regione 1. Le tre tabelle (ITU, ICAO, NATO) coincidono nelle parole-codice; differiscono solo in dettagli di trascrizione fonetica.

### Tabella alfabeto (lettera – parola – pronuncia ICAO)

| L | Parola | Pronuncia | L | Parola | Pronuncia |
|---|--------|-----------|---|--------|-----------|
| A | Alfa | AL-fah | N | November | no-VEM-ber |
| B | Bravo | BRAH-voh | O | Oscar | OSS-cah |
| C | Charlie | CHAR-lee (o SHAR-lee) | P | Papa | pah-PAH |
| D | Delta | DELL-tah | Q | Quebec | keh-BECK |
| E | Echo | ECK-oh | R | Romeo | ROW-me-oh |
| F | Foxtrot | FOKS-trot | S | Sierra | see-AIR-rah |
| G | Golf | GOLF | T | Tango | TANG-go |
| H | Hotel | hoh-TELL | U | Uniform | YOU-nee-form (o OO-nee-form) |
| I | India | IN-dee-ah | V | Victor | VIK-tah |
| J | Juliett | JEW-lee-ett | W | Whiskey | WISS-key |
| K | Kilo | KEY-loh | X | X-ray | ECKS-ray |
| L | Lima | LEE-mah | Y | Yankee | YANG-key |
| M | Mike | MIKE | Z | Zulu | ZOO-loo |

Nota grafica ufficiale: si scrivono "Alfa" e "Juliett" (non "Alpha"/"Juliet") perché in molte lingue non anglofone il digramma "ph" non si legge come /f/ e la "t" finale singola tenderebbe a non essere pronunciata. La sillaba in MAIUSCOLO indica l'accento tonico.

### Numeri (pronuncia ICAO/ITU)
0 ZE-RO, 1 WUN, 2 TOO, 3 TREE, 4 FOW-er, 5 FIFE, 6 SIX, 7 SEV-en, 8 AIT, 9 NIN-er. Le forme "niner", "fife", "tree", "fower" servono a distinguere queste cifre da parole o numeri foneticamente vicini (per es. "niner" evita la confusione di "nine" con il tedesco "nein" o con "five"). I numeri si dettano cifra per cifra: 145.500 → "uno-quattro-cinque punto cinque" oppure, in inglese ICAO, "one-four-five decimal five" (preferibilmente "wun-fower-fife decimal fife"). Il separatore decimale ICAO è "decimal".

Nota: in radioamatorismo, per dettare il moltiplicatore intero delle migliaia/centinaia, è prassi comune (US/NATO) usare "thousand" e "hundred" (es. 25 000 = "two-five thousand"). Lo standard ICAO puro impone invece la lettura cifra per cifra.

### Prowords (parole-procedura) essenziali

| Proword | Significato |
|---------|-------------|
| OVER | Passo l'ascolto, attendo risposta |
| OUT | Fine comunicazione, niente risposta (mai "over and out") |
| ROGER | Ricevuto e compreso |
| WILCO | Ricevuto e eseguirò (include già il "ROGER": non si dice "roger wilco") |
| AFFIRM(ATIVE) / NEGATIVE | Sì / No |
| SAY AGAIN | Ripeti (NON "repeat", che in ambito militare/artiglieria significa "ripeti il tiro") |
| I SAY AGAIN | Ripeto io |
| I SPELL | Seguito dall'ortografia fonetica della parola precedente |
| FIGURES | Seguono dei numeri |
| CORRECTION | Annulla quanto detto per ultimo; segue la versione corretta |
| WRONG | Quanto trasmesso è errato; segue la versione corretta |
| STANDBY (WAIT) | Attendi |
| BREAK | Separa parti del messaggio (es. testo da firma/istruzioni) |
| RADIO CHECK | Richiesta di controllo della qualità del segnale |
| ROGER SO FAR | Hai ricevuto/compreso fin qui? |

### Procedura operativa passo-passo (chiamata generale)
1. Verifica che la frequenza sia libera: "Is this frequency in use? IZ0XXX" (in CW: "QRL?").
2. Chiamata CQ: "CQ CQ CQ, this is India-Zero-X-Ray-X-Ray-X-Ray, India Zulu Zero X-Ray X-Ray X-Ray, calling CQ and standing by."
3. Risposta: passa prima il nominativo dell'altra stazione, poi il proprio, dai il rapporto (in fonia il RST si riduce a R-S, es. "5 and 9"), nome e QTH.
4. Chiusura: "73, IZ0XXX clear" oppure "... OUT".

### Note pratiche
- In Italia il nominativo va trasmesso con il prefisso completo (es. IZ0, IK4, IW1...) e dato all'inizio e alla fine del collegamento, e comunque ad intervalli regolari durante un QSO prolungato. Verifica le regole vigenti sul sito del MIMIT (ex MISE) e nelle relative norme attuative.
- Esempio di ortografia: nominativo IK2ABC = "India Kilo Two Alfa Bravo Charlie".
- Il rapporto in SSB è RS (R = leggibilità 1-5; S = forza del segnale 1-9); in CW/telegrafia e digitale è RST, dove T = tono 1-9.
- Termini come "QSO", "QTH", "QRZ", "73" derivano dal codice Q: nati per la telegrafia, sono di uso comune anche in fonia.
- Frequenze e segmenti di banda assegnati ai modi fonia variano per banda e per band plan: consulta il band plan IARU Regione 1 aggiornato (iaru-r1.org) e il piano nazionale ARI prima di operare. In Italia la maggior parte delle bande HF è di tipo secondario o condiviso; rispetta sempre i limiti di potenza e i segmenti previsti dalle norme nazionali e dal band plan.

## Modi digitali: caratteristiche, larghezze di banda, frequenze tipiche

Panoramica operativa per Regione 1 (Italia). Le frequenze sono in MHz, USB salvo dove indicato. La frequenza indicata è la "dial" (VFO) tipica del software; i toni audio cadono in genere 0–3000 Hz sopra di essa. Convenzione decimale italiana: la virgola separa la parte intera dai decimali (es. 14,074 MHz).

> Nota su "FT2": **non esiste** un modo digitale ratificato e diffuso chiamato "FT2" nella famiglia WSJT-X. I modi reali della famiglia FT sono **FT8** e **FT4**. La voce è stata rimossa per evitare disinformazione.

### Tabella riepilogativa

| Modo | Larghezza banda | Velocità | Note |
|------|-----------------|----------|------|
| FT8 | ~50 Hz | ciclo T/R 15 s | WSJT-X/JTDX/MSHV, segnali molto deboli (decodifica fino a circa -21 dB SNR) |
| FT4 | ~90 Hz | ciclo T/R 7,5 s | pensato per i contest, più veloce ma meno sensibile di FT8 |
| JT65 | ~178 Hz | ciclo T/R 60 s | EME e HF lente; sottomodi JT65A (HF) / B / C |
| JS8Call | ~50 Hz | normal 15 s / fast 10 s / turbo 6 s / slow 30 s | derivato da FT8, keyboard-to-keyboard, messaggistica/rete in store-and-forward |
| PSK31 | ~31 Hz | ~31,25 baud (≈50 wpm) | BPSK con codifica Varicode, conversazione QSO |
| RTTY | ~250–300 Hz | 45,45 baud, shift 170 Hz | codice Baudot/ITA2, FSK; in audio (AFSK) di norma con dial in LSB |
| Olivia | 125–2000 Hz (es. 500/1000) | lenta ma robustissima | tipico 8/250, 16/500, 32/1000 (toni/larghezza Hz) |
| Contestia | simile a Olivia | più veloce di Olivia | derivato da Olivia, MFSK |
| VARA HF / VARA FM | ~500 Hz (HF) / banda audio (FM) | adattivo, ARQ | usato con Winlink, software proprietario |
| Packet 1200 | banda audio FM | 1200 baud AFSK | VHF, protocollo AX.25 |
| APRS | come packet | 1200 baud AFSK | 144,800 MHz FM in Regione 1 |

### Frequenze tipiche (dial USB, salvo nota)
- **FT8**: 1,840 · 3,573 · 7,074 · 10,136 · 14,074 · 18,100 · 21,074 · 24,915 · 28,074 · 50,313 · 144,174.
- **FT4**: 3,575 · 7,047,5 · 10,140 · 14,080 · 18,104 · 21,140 · 24,919 · 28,180 (frequenze ufficiali WSJT-X; in contest si usano anche segmenti aggiuntivi).
- **JT65**: 3,570 · 7,076 · 14,076 (segmenti JT condivisi; verificare band plan IARU R1).
- **JS8Call**: 7,078 · 14,078 (comuni; non normate, verificare on-air).
- **PSK31**: 3,580 · 7,040 · 14,070 · 21,080 · 28,120.
- **RTTY**: 3,580–3,600 · 7,040 · 14,080–14,099 · 21,080 · 28,080.
- **Olivia/Contestia**: 14,072 ± (centro tono 1500 Hz comune); molto variabile.
- **APRS**: 144,800 (FM) standard Regione 1.

### Procedura FT8 (esempio reale, 20 m)
1. Sincronizza il PC via NTP (errore tipicamente < 1 s, critico per FT8/FT4 che dipendono dalla sincronizzazione temporale).
2. Imposta dial 14,074 USB, modo "Data/USB", larghezza filtro ~3 kHz.
3. Regola il livello audio TX così che l'ALC resti a zero (catena TX puramente lineare, niente compressione).
4. Potenza tipica 20–30 W: a 50 W molti spot non migliorano e si occupa spettro inutilmente. FT8 è progettato per la bassa potenza.
5. In WSJT-X imposta nominativo e locator (es. JN45), seleziona un segnale in Band Activity, doppio clic per rispondere; lo scambio standard procede: **grid (locator) → report (es. -12) → R+report (es. R-10) → RR73 → 73**.

### Promemoria utili (codici, fonetico, formule)

**Codici Q comuni**
- QRZ? = chi mi chiama?
- QSL = confermo / ricevuto
- QRM = disturbo (interferenze artificiali) · QRN = disturbo atmosferico
- QSB = affievolimento (fading) · QRP = bassa potenza · QRO = alta potenza
- QSY = cambio frequenza · QTH = località/posizione · QRT = cesso la trasmissione

**Alfabeto fonetico NATO/ICAO**
Alpha, Bravo, Charlie, Delta, Echo, Foxtrot, Golf, Hotel, India, Juliett, Kilo, Lima, Mike, November, Oscar, Papa, Quebec, Romeo, Sierra, Tango, Uniform, Victor, Whiskey, X-ray, Yankee, Zulu.

**Formule antenne** (lunghezze in metri, f in MHz)
- Dipolo a mezz'onda (con fattore di accorciamento ~0,95): L (totale) ≈ **142,5 / f**; ogni braccio ≈ 71,25 / f.
- Verticale a quarto d'onda (con fattore di accorciamento): L ≈ **71,25 / f**.
- Lunghezza d'onda nel vuoto: λ ≈ **300 / f**.
  - Esempio a 14,074 MHz: λ ≈ 21,3 m; dipolo ≈ 10,1 m (≈ 5,06 m per braccio); verticale 1/4 λ ≈ 5,06 m.

**Conversioni dB / potenza** (campo di potenza: dB = 10·log₁₀(P2/P1))
- +3 dB ≈ raddoppio della potenza · −3 dB ≈ metà.
- +6 dB ≈ ×4 · +10 dB = ×10 · +20 dB = ×100 · +30 dB = ×1000.
- Esempio: da 5 W a 50 W = +10 dB; da 5 W a 500 W = +20 dB.
- Riferimenti assoluti: dBm (riferito a 1 mW): 0 dBm = 1 mW, 30 dBm = 1 W, 37 dBm ≈ 5 W, 50 dBm = 100 W. dBW (riferito a 1 W): 0 dBW = 1 W.

### Note tecniche e normative
- **Potenza massima in Italia (MIMIT)**: l'attuale quadro (D.Lgs. 1°/8/2003 n. 259, Codice delle comunicazioni elettroniche, e relativi allegati/decreti) prevede per la **patente di classe A (piena)** un limite di norma **500 W** di potenza (in molti documenti espressa come potenza fornita all'antenna / o.r.p. a seconda della banda) sulla maggior parte delle bande HF; per la **classe B** il limite è inferiore (tipicamente 10 W / potenze ridotte). Esistono limitazioni e deroghe per banda. **Verificare sempre il band plan e i decreti aggiornati del MIMIT**, perché i valori e le condizioni cambiano nel tempo. (Attenzione: EIRP e potenza all'antenna sono grandezze diverse; non confondere i 500 W con un valore EIRP.)
- I band plan dei segmenti digitali sono **raccomandazioni IARU Region 1, non legge**: il riferimento autorevole è il documento band plan IARU-R1 (e per l'Italia l'ARI). Le frequenze "comunitarie" (JS8Call, Olivia) non sono normate e vanno verificate in aria.
- VARA è software proprietario (licenza a pagamento per la piena velocità) usato con Winlink; in emergenza coordinarsi con la rete locale.
- **Verifica fonti**: band plan IARU-R1, ARI, decreti e Piano di Ripartizione/Assegnazione delle frequenze (MIMIT), documentazione ufficiale WSJT-X.

## Software e flusso dei modi FT (WSJT-X, JTDX e Decodium)

I modi FT (Franke–Taylor, dai loro autori Steven Franke K9AN e Joe Taylor K1JT) sono modulazioni digitali a quadro temporale rigido. La sincronizzazione del PC all'ora UTC (NTP, errore < 1 s, idealmente < 0,2 s) è obbligatoria: senza orologio preciso non si decodifica nulla. Su Windows usa il servizio orario di sistema (w32time) o tool come Meinberg NTP / NetTime; verifica che il fuso e l'ora siano allineati a UTC tramite un server affidabile (es. pool.ntp.org).

### Cicli temporali e parametri

| Modo | Periodo T/R | TX util | Larghezza | Velocità simboli | Modulazione |
|------|-------------|---------|-----------|------------------|-------------|
| FT8 | 15,0 s | ~12,64 s | ~50 Hz | 6,25 baud | 8-FSK (GFSK) |
| FT4 | 7,5 s | ~4,48 s | ~90 Hz | 20,83 baud | 4-GFSK |
| FT2 | ~6 s (sperimentale) | — | — | — | — |

FT8 e FT4 condividono lo stesso schema di codifica: 77 bit di payload + 14 bit di CRC = 91 bit, codificati con un codice LDPC (174, 91) che aggiunge 83 bit di parità, per un totale di 174 bit trasmessi. FT8 usa 79 simboli (di cui 3 blocchi di sincronismo Costas da 7 simboli ciascuno, in testa, al centro e in coda); FT4 usa 105 simboli (4 array di sincronismo Costas da 4 simboli ciascuno). FT2 è sperimentale e non standardizzato: verifica i parametri esatti nella documentazione WSJT-X/MSHV in uso, non assumerli.

### Sequenze e ciclo del QSO

Le finestre TX/RX si alternano in base ai secondi del minuto UTC. In FT8 le sequenze iniziano ai secondi 00, 15, 30, 45 di ogni minuto; chi chiama CQ sceglie "Even/1st" (sequenze che iniziano a 00 e 30 s) oppure "Odd/2nd" (sequenze che iniziano a 15 e 45 s) e l'interlocutore si pone in alternanza. Un QSO minimo (4–5 cicli, ~1 minuto) in FT8:

1. `CQ IU8LMC JN70` (chiamata CQ + nominativo + locatore Maidenhead a 4 cifre)
2. `IU8LMC F5ABC -12` (suo call, mio call, SNR a lui assegnato in dB)
3. `F5ABC IU8LMC R-08` (R = ho ricevuto il tuo riporto + SNR che assegno a te)
4. `IU8LMC F5ABC RRR` (oppure `RR73`, che combina conferma e saluto)
5. `F5ABC IU8LMC 73`

Nota sull'ordine dei nominativi: nel messaggio si scrive prima il destinatario e poi il proprio nominativo (es. `IU8LMC F5ABC -12` è inviato da F5ABC verso IU8LMC). L'uso di `RR73` consente di chiudere in 4 sequenze anziché 5.

SNR FT8 va tipicamente da circa +20 a −24 dB (riferito alla banda di rumore standard di 2500 Hz); la decodifica arriva fino a circa −21 dB (talvolta −24 dB con condizioni favorevoli e decoder ottimizzati), ben sotto la soglia udibile. I messaggi standard usano 28 bit per ciascun nominativo (campo c28) e 15 bit per il locatore (campo g15).

### Frequenze dial USB (Regione 1, IARU)

| Banda | FT8 (MHz) | FT4 (MHz) |
|-------|-----------|-----------|
| 80 m | 3,573 | 3,575 |
| 40 m | 7,074 | 7,0475 |
| 30 m | 10,136 | 10,140 |
| 20 m | 14,074 | 14,080 |
| 17 m | 18,100 | 18,104 |
| 15 m | 21,074 | 21,140 |
| 12 m | 24,915 | 24,919 |
| 10 m | 28,074 | 28,180 |
| 6 m | 50,313 | 50,318 |

Sono frequenze dial USB convenzionali (bandplan IARU R1, da verificare sempre sulla versione aggiornata su iaru-r1.org). In Italia rispetta segmenti e limiti del Piano Nazionale di Ripartizione delle Frequenze (PNRF) e della normativa MIMIT. Attenzione: le bande WARC (30 m, 17 m, 12 m) NON ammettono contest; usale solo per QSO ordinari. Il segnale audio reale sta tipicamente entro i primi ~2700–3000 Hz sopra la dial, ma per FT8 la convenzione operativa è collocare il proprio TX entro circa 200–2900 Hz; mantieni la portante audio nella zona piatta del filtro SSB.

Potenza: i modi FT sono molto efficienti, 10–30 W bastano per la maggior parte dei DX. Evita di "sparare" 100 W o più: saturi la cascata di decodifica altrui, generi prodotti di intermodulazione audio (splatter) se la catena audio/ALC non è regolata correttamente. Tieni l'ALC a zero o appena accennata e riduci il drive lato PC.

### Normativa italiana (potenze)

Per i radioamatori italiani con patente ordinaria il limite di potenza è 500 W (PEP) sulle bande HF dove consentito; per i titolari di autorizzazione di classe inferiore e su determinate bande/segmenti valgono limiti più bassi (es. 10 W per le classi base/principianti dove previsto). I limiti puntuali per banda sono definiti dal MIMIT (ex MISE) e dal PNRF: verifica sempre il segmento operativo, poiché alcune porzioni di banda impongono potenze ridotte. Per i modi FT questi limiti sono ampiamente sovradimensionati rispetto a quanto serve.

### Software

- **WSJT-X** (Joe Taylor K1JT et al.): riferimento ufficiale, supporta FT8, FT4, JT65, Q65, WSPR, MSK144, FST4 e altri.
- **JTDX**: fork orientato all'ottimizzazione del decoder e alla gestione dell'affollamento; fornisce più decodifiche nei pile-up.
- **MSHV**: utile per la modalità Fox & Hound (multi-stream) tipica delle DXpedition, e per operazioni multi-segnale.

Il **Decodium/Decodius** presente in questo progetto (`E:\decodius`, file `Assistant.cpp`, `AudioAnalyzer.cpp`, `Main.qml`) NON è un decoder FT: è un assistente vocale locale Qt6/QML che usa la FFT solo per il visualizzatore audio e Ollama (Gemma) per il dialogo. Non genera né decodifica messaggi FT8/FT4; per quello restano WSJT-X/JTDX/MSHV. Decodius si integra invece come copilota vocale a fianco del decoder reale (per consultazione di nominativi, locatori, codici Q, conversioni dB/W e formule d'antenna durante l'attività).

## Propagazione ionosferica: strati, MUF/LUF, indici solari e grey line

La ionosfera è la regione dell'alta atmosfera (circa 60-1000 km di quota) ionizzata dalla radiazione solare (UV ed X). Gli strati ionizzati **rifrangono** progressivamente le onde HF, che vengono così "ripiegate" verso terra rendendo possibili i collegamenti a lunga distanza (DX). Il fenomeno è più correttamente una rifrazione graduale, anche se nella pratica si parla comunemente di "riflessione".

### Strati ionosferici
| Strato | Quota indicativa | Comportamento |
|--------|------------------|---------------|
| D | 60-90 km | Solo di giorno; **assorbe** le HF basse (l'assorbimento cresce al diminuire della frequenza, ∝ 1/f²). Scompare di notte: per questo 160/80/40 m "si aprono" dopo il tramonto. |
| E | 90-130 km | Presente di giorno; riflette le frequenze più basse. Lo **Sporadic-E (Es)** apre 6 m e talvolta 10 m (e 4 m) soprattutto in estate (maggio-agosto, picco giugno-luglio), con salti tipici ~500-2000 km a singolo hop. |
| F1 | 150-220 km | Solo di giorno; si fonde con F2 di notte. |
| F2 | 220-500 km | Lo strato più importante per il DX in HF; persiste anche di notte (più debole e più basso). La quota e la densità variano molto con ora, stagione e attività solare. |

### Frequenza critica, MUF e LUF
- **foF2 (frequenza critica)**: massima frequenza riflessa con incidenza **verticale** (sondaggio ionosferico). Tipicamente 2-15 MHz secondo ora/stagione/ciclo solare.
- **MUF (Maximum Usable Frequency)**: massima frequenza utilizzabile per una data tratta a incidenza obliqua. Formula approssimata: **MUF ≈ foF2 / cos(φ) = foF2 × sec(φ)**, dove φ è l'**angolo di incidenza** del raggio sullo strato (misurato rispetto alla verticale). Il fattore di obliquità (sec φ) vale spesso ~3-3,5 per tratte ~3000-4000 km a singolo salto. Si opera convenzionalmente al **FOT ≈ 0,85 × MUF** (Frequency of Optimum Transmission / frequenza ottimale di lavoro) per avere maggiore stabilità e margine.
- **LUF (Lowest Usable Frequency)**: frequenza sotto la quale l'assorbimento dello strato D rende il segnale troppo debole per il collegamento. La banda utile è **LUF < f < MUF**.
- **Skip zone (zona di silenzio)**: area "morta" compresa tra il limite massimo dell'onda di terra (ground wave) e il punto di primo rientro dell'onda ionosferica. Per ridurla/superarla: scendere di frequenza (abbassa la MUF di rientro e accorcia lo skip) oppure aumentare l'angolo di partenza verticale, fino alla tecnica **NVIS** (Near Vertical Incidence Skywave) per coperture a corto raggio senza zona di silenzio (tipicamente su 80/40 m).

### Ciclo solare e indici (da consultare in tempo reale)
Il ciclo solare dura mediamente ~11 anni. Il **Ciclo 25** ha avuto il massimo effettivo intorno a **fine 2024 - inizio 2025**; nel 2026 siamo quindi in fase ancora elevata ma in graduale calo verso il minimo (atteso indicativamente verso il 2030).

| Indice | Cosa misura | Lettura pratica |
|--------|-------------|-----------------|
| **SFI** (Solar Flux Index, flusso a 10,7 cm = 2800 MHz, in s.f.u.) | Intensità della radiazione solare a 2,8 GHz, proxy dell'attività | >100 buono, >150 ottimo per 10/12/15 m. Sotto ~70 = bande alte tendenzialmente chiuse. |
| **SSN** (Sunspot Number) | Numero relativo di macchie solari | Correlato a SFI e foF2: più macchie, ionizzazione e MUF più alte. |
| **A-index** | Disturbo geomagnetico medio giornaliero (scala lineare 0-400) | <10 quieto, ottimo; 10-30 instabile; >30 disturbato. |
| **K-index** | Disturbo geomagnetico ogni 3 h (scala quasi-logaritmica 0-9) | 0-2 quieto; 3 instabile; 4 attivo; ≥5 = tempesta geomagnetica (G1+), con possibile blackout HF, abbassamento MUF e aurora. |

Verifica i valori su **NOAA SWPC**, oppure sul widget **N0NBH (hamqsl.com/solar.html)**. Nota: SFI, SSN e A-index sono valori giornalieri; il K-index è planetario (Kp) e si aggiorna ogni 3 ore.

### Grey line
È la fascia crepuscolare lungo il **terminatore** (linea alba/tramonto) lungo cui lo strato D si è già dissolto (o non si è ancora formato) mentre l'F è ancora ionizzato: si creano condizioni eccezionali sulle bande basse (tipicamente 160-30 m) verso le zone che si trovano in crepuscolo, spesso lungo direttrici quasi antipodali. Conviene operare nei minuti attorno alla propria alba e al proprio tramonto. Strumenti: DX Atlas, mappe grey-line online, funzione grey-line dei log e dei propagation tool.

### Procedura operativa
1. Controlla SFI, K e A (hamqsl.com / NOAA SWPC).
2. Stima la MUF della tratta con un tool (es. VOACAP / VOACAP Online, propquest, PropQuest/KC2G MUF map).
3. Scegli la banda più alta utilizzabile sotto la MUF (minore assorbimento e di solito meno QRM/QRN).
4. Con K≥5 (tempesta geomagnetica) ripiega sulle bande basse o rimanda l'attività; durante gli eventi aurorali sfrutta eventualmente la propagazione aurorale su VHF.
5. Sfrutta la grey line per il DX in 160/80/40 m.

I dati propagativi sono fortemente variabili: usa sempre fonti in tempo reale (NOAA SWPC, hamqsl.com, rete di beacon **NCDXF/IARU**) e i **cluster DX** / reti come PSK Reporter e WSPRnet per la verifica operativa effettiva delle aperture.

## Propagazione VHF/UHF e modi particolari

In VHF/UHF la propagazione "normale" è quasi ottica (linea di vista estesa, leggermente oltre l'orizzonte geometrico per la rifrazione troposferica standard); i modi seguenti permettono collegamenti DX ben oltre l'orizzonte.

### Sporadic E (Es)
Nubi di ionizzazione intensa e localizzata nello strato E (~95-120 km). In Italia (IARU R1) picco stagionale principale **maggio-agosto** (massimo tra fine maggio e luglio), con un picco secondario minore intorno al **solstizio d'inverno (fine dicembre - inizio gennaio)**. Statisticamente le aperture sono più frequenti a metà mattina e nel tardo pomeriggio.
La frequenza critica della nube (foEs) può superare 10-15 MHz e, nelle aperture più intense, raggiungere 25-30 MHz. La **MUF** per incidenza obliqua è circa 4-5 volte la foEs (fattore di obliquità), per cui può superare facilmente i 100 MHz; il 144 MHz richiede foEs molto elevata (~28-30 MHz) ed è quindi raro.
- 6 m (50 MHz, es. 50,313 MHz FT8; finestra DX SSB intorno a 50,1 MHz; beacon 50,0-50,1 MHz): banda principe per Es, hop singolo tipico ~600-2300 km.
- 2 m (144 MHz, attività FT8 intorno a 144,174 MHz; SSB DX intorno a 144,300 MHz): Es possibile ma raro; con doppio hop si raggiungono ~1500-2500 km.
- Verifica condizioni: dxmaps.com (mappa MUF e spot in tempo reale), cluster DX, beacon in 50 MHz.

### Tropo e condotti (tropospheric ducting)
Rifrazione anomala negli strati bassi della troposfera dovuta a inversioni termiche e forti gradienti di umidità. Favorito da alta pressione (anticicloni stabili), subsidenza notturna e dall'interfaccia mare-terra (es. mar Adriatico, alto Tirreno, pianura Padana). I condotti permettono DX su 144/432/1296 MHz e oltre, tipicamente fino a 1000-2000 km (in condizioni eccezionali oltre). In generale, quanto più alta è la frequenza tanto più il condotto è "intrappolante": UHF/SHF spesso aprono meglio del 2 m, a patto che lo spessore del condotto sia adeguato alla lunghezza d'onda.
- Previsioni: Hepburn Tropo Index (William Hepburn, dxinfocentre.com).
- Beacon e ponti ripetitori distanti come riferimento per individuare l'apertura.

### Aurora (Au)
Riflessione/scattering su particelle ionizzate dei cinturi aurorali durante l'attività geomagnetica (tempeste solari, CME, fasce HSS). Antenne puntate verso **Nord** (l'azimut ottimale segue la regione aurorale, non necessariamente la direzione geografica del corrispondente). Audio caratteristico: SSB "raschiante" e distorta, CW con nota allargata e diffusa ("buzzy"); per questo motivo in aurora si privilegia il **CW (A1A)**, più robusto in presenza di forte allargamento Doppler. Tipica su 50 e 144 MHz alle latitudini medio-alte europee. Monitorare l'indice planetario **Kp >= 5** (NOAA SWPC, spaceweather.com).

### Meteor scatter (MS)
Riflessione su scie ionizzate lasciate dalle meteore nell'alta atmosfera (~85-120 km), con durata da frazioni di secondo (scie underdense) a diversi secondi o più (scie overdense). Ottimo su 50 e 144 MHz, distanze tipiche ~600-2200 km. Sciami principali: Quadrantidi (~3-4 gennaio), Perseidi (~12-13 agosto), Geminidi (~13-14 dicembre); presente anche fondo sporadico quotidiano, con picco all'alba.
- Modo digitale standard: **WSJT-X / MSK144**, frequenza di riferimento **144,360 MHz** in 2 m e **50,260 MHz** in 6 m (FT8 usato in alcune attività). Schema tradizionale: i due corrispondenti trasmettono su periodi alternati (uno sui periodi pari, l'altro sui dispari) secondo accordo, di norma con periodi da 15 s.
- Potenze: in Italia il limite per la stazione di radioamatore (autorizzazione generale, quadro MIMIT) è in genere **500 W PEP** in HF/VHF/UHF (con valori inferiori per alcune bande/classi e potenze maggiori solo con specifica autorizzazione). Verificare sempre l'autorizzazione e i limiti di banda vigenti.

### EME (Earth-Moon-Earth, rimbalzo lunare)
Si usa la Luna come riflettore passivo. Attenuazione di tratta enorme: ~252 dB su 144 MHz, ~261 dB su 432 MHz e ~271 dB in banda 23 cm (1296 MHz). A queste si aggiungono perdite per libration fading e per disallineamento di polarizzazione (rotazione di Faraday significativa in VHF, polarizzazione spaziale in UHF/SHF). Richiede antenne ad alto guadagno (cortine di Yagi, parabole), preamplificatori a bassissima cifra di rumore (LNA) e potenza elevata. Bande tipiche: 144, 432, 1296 MHz e superiori.
- Software standard: **WSJT-X** con i modi **Q65** (e JT65 legacy). Pianificazione: finestra di comune visibilità della Luna (common window) tra i due corrispondenti; perigeo per attenuazione minima e degradazione (cielo freddo) favorevole.
- Riferimenti operativi e tecnici: comunità EME, articoli e documentazione (es. K1JT / Joe Taylor), liste di sked e logger dedicati.

### Tabella riassuntiva

| Modo | Bande tipiche | Distanza | Stagione/Trigger | Modo audio/digitale |
|------|---------------|----------|------------------|---------------------|
| Sporadic E | 50, 144 MHz | 600-2300 km (singolo hop) | mag-ago (sec. dic-gen) | SSB/CW/FT8 |
| Tropo/condotti | 144 MHz - 10 GHz | 300-2000 km | alta pressione/inversioni | SSB/CW |
| Aurora | 50, 144 MHz | variabile (verso Nord) | Kp >= 5 | CW preferito |
| Meteor scatter | 50, 144 MHz | 600-2200 km | sciami meteorici | MSK144 |
| EME | 144 MHz - SHF | globale | comune visibilità Luna | Q65/JT65 |

Nota: limiti di potenza, segmenti di banda e condizioni d'uso in Italia vanno verificati sulla normativa vigente (**MIMIT** - autorizzazione generale per il servizio di radioamatore) e sul **bandplan IARU R1** recepito da **ARI**; i dati di propagazione e le previsioni si consultano su fonti dedicate (NOAA SWPC, dxmaps.com, dxinfocentre.com).

## Satelliti radioamatoriali: QO-100, GreenCube, SO-50, ISS e tecniche operative

I satelliti amatoriali si dividono in **LEO** (orbita bassa, ~400-800 km, passaggi di 5-15 min, soggetti a forte Doppler) e **geostazionari** (QO-100, sempre visibile, niente Doppler né tracking di puntamento).

### QO-100 / Es'hail-2 (geostazionario, 25,5° E)
Primo transponder amatoriale geostazionario, visibile da tutta l'Italia con elevazione di circa 26-31° (azimut SSE, verso ~140-145°; antenne ferme, niente inseguimento). A bordo del satellite Es'hail-2 ci sono due transponder amatoriali (gestiti da AMSAT-DL / Qatar Amateur Radio Society):
- **NB (Narrow Band)**: SSB/CW/digimode a banda stretta (250 kHz). Uplink **2400,050-2400,300 MHz** (banda 13 cm, modo uplink **S**, 2,4 GHz). Downlink **10489,550-10489,800 MHz** (banda 3 cm, modo downlink **S** / X, 10 GHz). È un transponder **lineare NON invertente**: la USB in uplink resta USB in downlink e lo spettro **non** è specchiato.
- **WB (Wide Band)**: DATV (DVB-S2/S2X). Uplink **2401,5-2409,5 MHz** / Downlink **10491-10499 MHz**.

Setup tipico NB: TX 2,4 GHz (es. Adalm-Pluto + PA ~2-5 W) verso antenna a elica/patch posta sul feed offset della parabola; RX 10,489 GHz con LNB PLL universale (modificato con riferimento esterno 25 MHz o TCXO per la stabilità) e SDR (RTL-SDR/Pluto). Il **beacon PSK inferiore (lower beacon) a 10489,500 MHz** marca il bordo inferiore del transponder NB e serve come riferimento per centrare/tarare la frequenza; sono presenti anche un beacon CW e un beacon PSK superiore (~10489,800 MHz). Importante: uplink e downlink si lavorano simultaneamente in **full-duplex** (ti puoi riascoltare in tempo reale e centrarti sul tuo segnale).

### GreenCube / IO-117
CubeSat italiano (Sapienza Università di Roma) in orbita **MEO ~5900 km**: finestre di visibilità molto lunghe (anche >1 ora) e ampia copertura. Opera un **digipeater a pacchetto** (store-and-forward / packet QSO) su **435,310 MHz** (banda 70 cm, modo U), con uplink e downlink **sulla stessa frequenza** (half-duplex). Modulazione **GMSK 1k2**, protocollo gestito da software dedicato (es. terminale GreenCube, SatNOGS). Doppler significativo (banda 70 cm) da correggere.

### SO-50 (SaudiSat 1C)
FM repeater LEO classico, ideale per i principianti con un HT.
- **Uplink 145,850 MHz** (FM, banda 2 m / modo V). Per trasmettere serve il **subtono CTCSS 67,0 Hz**; il timer dell'audio (~10 min) va prima "armato" inviando una volta un tono **74,4 Hz**.
- **Downlink 436,795 MHz** (banda 70 cm / modo U).

È quindi un satellite **modo V/U** (uplink V, downlink U). Antenna tipica: Yagi portatile a mano (es. Arrow/Elk). Essendo FM, una sola stazione alla volta (effetto cattura): disciplina e QSO brevi.

### ISS (Stazione Spaziale Internazionale)
- **Cross-band repeater FM**: uplink **145,990 MHz** (CTCSS 67,0 Hz), downlink **437,800 MHz** (modo V/U).
- **APRS / packet (1k2 AFSK)**: **145,825 MHz** simplex (up e down sulla stessa frequenza).
- **SSTV** e contatti scolastici **ARISS**: downlink in FM su **145,800 MHz** (banda 2 m); la SSTV usa tipicamente il modo **PD120**.

### Effetto Doppler
Δf = f · (v/c). In 70 cm (~436 MHz) lo shift raggiunge **±9-10 kHz** al passaggio; in 2 m (~145 MHz) circa **±3,5 kHz**. La frequenza scende durante il passaggio (da alta a bassa, AOS→LOS, con un attraversamento allo zenit/TCA). Si corregge agendo sul downlink e/o sull'uplink. Per gli FM (SO-50, ISS repeater) basta una correzione a passi sull'uplink; per SSB/CW serve correzione continua. Software come **SatPC32, Gpredict, Look4Sat** pilotano l'RTX via CAT con Doppler automatico.

### Modi e tracking
Nomenclatura di banda (lettere AMSAT/IARU):
- **H** = 21 MHz, **A** = 28-29 MHz (10 m), **V** = 144 MHz (2 m), **U** = 432/435 MHz (70 cm), **L** = 1,2-1,3 GHz (23 cm), **S** = 2,4 GHz (13 cm), **S2** = 3,4 GHz (9 cm), **C** = 5,6 GHz, **X** = 10 GHz (3 cm).

La sigla "U/V" indica **uplink U, downlink V**; "V/U" indica uplink V, downlink U. Per il tracking servono gli **elementi orbitali Kepleriani/TLE** aggiornati (fonti: Celestrak, AMSAT).

**Verifica sempre frequenze, stato e TLE su fonti ufficiali**: AMSAT (amsat.org), AMSAT-DL (per QO-100), AMSAT-Italia, bandplan **IARU R1** e, per gli aspetti normativi italiani (potenze, autorizzazioni), **MIMIT** e ARI. In Italia la potenza è regolata dall'autorizzazione generale: tipicamente fino a **500 W** per i titolari di patente di classe A nelle bande consentite (limiti inferiori su alcune bande e per la classe B); rispetta i limiti di banda e di potenza vigenti. Le frequenze dei singoli satelliti possono cambiare (commutazioni di transponder, fine vita operativa): non operare senza conferma aggiornata.

## Antenne HF: tipologie, parametri e formule

### Parametri fondamentali
- **Impedenza**: il dipolo a mezz'onda in spazio libero ha ~73 Ω (resistiva alla risonanza); nella pratica, a quote reali, l'impedenza al punto di alimentazione varia tipicamente tra ~50 e 75 Ω in funzione di altezza dal suolo e ambiente. Si adatta bene a cavi 50 Ω (RG-58, RG-213) o 75 Ω (RG-11).
- **Guadagno dBi vs dBd**: dBi = guadagno rispetto al radiatore isotropo; dBd = rispetto al dipolo a mezz'onda di riferimento. Relazione: **dBi = dBd + 2,15**. Quindi un dipolo ha per definizione 0 dBd = 2,15 dBi.
- **Polarizzazione**: orizzontale (dipolo, Yagi, quad montati in orizzontale) o verticale (verticale, ground plane). In HF la propagazione ionosferica ruota/altera la polarizzazione (l'onda riflessa arriva con polarizzazione casuale), quindi tra stazioni in skip la concordanza è poco rilevante; conta invece per onda diretta, ground wave e NVIS, dove le antenne dovrebbero idealmente condividere la stessa polarizzazione.
- **Lobi**: il dipolo a mezz'onda irradia con massimo ortogonale al filo (diagramma a "8" nel piano orizzontale); la Yagi concentra l'energia in un lobo frontale con rapporto fronte/retro (F/B) tipico di 15-25 dB.

### Formule di lunghezza (l in metri, f in MHz)

| Antenna | Formula | Note |
|---|---|---|
| Lunghezza d'onda λ | l = 300 / f | in spazio libero |
| Dipolo λ/2 | **l = 142,5 / f** | lunghezza totale (fattore ~0,95 di λ/2) |
| Braccio dipolo | **l = 71,25 / f** | per lato (metà del totale) |
| Verticale λ/4 | **l = 71,25 / f** | richiede piano di terra/radiali |
| Onda piena (loop quad) | l ≈ 306 / f | perimetro |

Il fattore **142,5** (≈ 0,95 × 150) tiene conto dell'accorciamento (~5%) dovuto al rapporto lunghezza/diametro del conduttore e all'effetto di estremità (end effect), rispetto a λ/2 teorico = 150/f. È sempre buona pratica tagliare leggermente lungo, poi accorciare misurando il ROS. Il valore esatto dipende dal filo e dalla quota: le formule danno solo un punto di partenza.

### Tipologie principali
- **Dipolo a mezz'onda**: antenna di riferimento. A 7,1 MHz → 142,5/7,1 ≈ **20,07 m** totali (bracci ~10,03 m ciascuno). Alimentazione al centro, ~50-73 Ω. Altezza ≥ λ/2 dal suolo per buon angolo di lancio verso il DX; a bassa quota (≤ ~0,2 λ) lavora in regime NVIS (irradiazione quasi verticale, ottima per collegamenti regionali entro qualche centinaio di km).
- **Verticale λ/4 / Ground plane**: radiatore λ/4 più radiali (piano di terra). Con 4 radiali inclinati a ~45° l'impedenza al punto di alimentazione sale dai ~36 Ω teorici verso ~50 Ω, facilitando l'adattamento al cavo. Basso angolo di irradiazione, buona per il DX; richiede buona terra o un sistema di radiali (per verticali montate a terra servono molti radiali, 16-32 o più, per ridurre le perdite a terra).
- **Yagi**: antenna direttiva con riflettore + radiatore (driven element) + uno o più direttori. Una 3 elementi tipica fornisce ~6-8 dBd di guadagno. Comune in VHF/UHF e in HF sulle bande alte (20-10 m). Richiede boom robusto e di norma un rotore per l'orientamento.
- **Quad**: antenna a loop (elementi a onda piena, perimetro ~1 λ) montati su boom; rispetto a una Yagi di pari numero di elementi offre tipicamente ~1-2 dB in più e spesso minore rumore captato.
- **Loop magnetico**: antenna piccola (circonferenza ≈ 1/10 di λ o meno), Q molto elevato, banda passante strettissima, accordo critico tramite condensatore variabile; ottima in spazi ridotti e per ridurre il rumore in ricezione. Richiede la ri-sintonizzazione del condensatore a ogni cambio di frequenza, anche piccolo. Attenzione: ai capi del condensatore sono presenti tensioni RF molto elevate.
- **G5RV**: dipolo di **31,1 m** (102 piedi) alimentato al centro tramite uno spezzone di linea bilanciata (matching/feeder section) di ~**10,36 m** (34 piedi) a ~450 Ω, poi coassiale; multibanda con accordatore (tuner). Non è risonante "puro" su tutte le bande: nasce ottimizzata per i 20 m e copre più bande con tuner.
- **Long wire**: filo di lunghezza maggiore di λ (per definizione almeno 1 λ), alimentato in fondo (end-fed) tramite tuner/unun; multibanda, diagramma con lobi multipli che si moltiplicano e diventano più appuntiti all'aumentare della lunghezza in λ. Economica; conviene una buona terra/contrappeso lato alimentazione.

### Procedura di taglio e taratura del dipolo
1. Calcola l = 142,5/f e taglia ogni braccio circa 3-5% più lungo del valore teorico (lascia margine per la sintonia).
2. Installa l'antenna nella posizione definitiva: quota dal suolo e ambiente circostante spostano la frequenza di risonanza.
3. Misura il ROS/risonanza con analizzatore d'antenna (es. NanoVNA, RigExpert) a bassa potenza.
4. Se la risonanza cade sotto la frequenza target, l'antenna è troppo lunga: accorcia simmetricamente entrambi i lati di pochi cm per volta (accorciare alza la frequenza di risonanza). Se è sopra il target, l'antenna è troppo corta.
5. Verifica ROS ≤ 1,5:1 sul segmento di banda d'interesse; usa un balun corrente 1:1 al centro per disaccoppiare e ridurre le correnti di modo comune sulla guaina del cavo.

### Bande HF radioamatoriali in Italia (IARU Region 1) e riferimenti
Principali bande HF in Italia (sottoposte a condizioni di licenza; verificare sempre il piano vigente):

| Banda | Gamma indicativa (MHz) |
|---|---|
| 160 m | 1,810 - 1,850 |
| 80 m | 3,500 - 3,800 |
| 40 m | 7,000 - 7,200 |
| 30 m | 10,100 - 10,150 (solo CW/dati, no fonia) |
| 20 m | 14,000 - 14,350 |
| 17 m | 18,068 - 18,168 |
| 15 m | 21,000 - 21,450 |
| 12 m | 24,890 - 24,990 |
| 10 m | 28,000 - 29,700 |

I segmenti CW si trovano in genere all'inizio di ciascuna banda, seguiti da dati e fonia, secondo il bandplan IARU Region 1.

### Note normative (Italia) e fonti
- I limiti di potenza, le bande assegnate e le condizioni operative in Italia sono definiti dalla normativa di settore (oggi **MIMIT** - Ministero delle Imprese e del Made in Italy, ex MISE) e dal **PNRF** (Piano Nazionale di Ripartizione delle Frequenze). Per i radioamatori italiani il riferimento è il Codice delle comunicazioni elettroniche e relativi allegati.
- A titolo indicativo, in Italia la potenza massima per la patente/autorizzazione ordinaria è dell'ordine di alcune centinaia di watt (verificare il valore esatto e le eventuali classi/condizioni vigenti, poiché soggetti ad aggiornamento normativo). Vanno inoltre rispettati i limiti di esposizione ai campi elettromagnetici.
- Per il bandplan operativo di dettaglio fare riferimento a **IARU Region 1** e all'**ARI** (Associazione Radioamatori Italiani).
- I dati di impedenza e guadagno reali dipendono da quota, suolo e ambiente: confermare sempre con misura strumentale e, se possibile, con simulazione (es. modelli basati su NEC).

### Promemoria operativi utili
- **Alfabeto fonetico ICAO/NATO**: Alpha, Bravo, Charlie, Delta, Echo, Foxtrot, Golf, Hotel, India, Juliett, Kilo, Lima, Mike, November, Oscar, Papa, Quebec, Romeo, Sierra, Tango, Uniform, Victor, Whiskey, X-ray, Yankee, Zulu.
- **Codici Q comuni**: QRZ? = "chi mi chiama?"; QRM = disturbi/interferenze da altre stazioni; QRN = disturbi atmosferici/statici; QRP = ridurre potenza / bassa potenza; QRO = aumentare potenza / alta potenza; QSB = evanescenza (fading) del segnale; QSL = confermo/conferma di ricezione; QSY = cambio frequenza; QTH = località/posizione; QRT = cessare le trasmissioni; QRV = sono pronto.

### Conversioni dB / potenza (utili per stimare guadagni e perdite)
- **+3 dB** ≈ raddoppio della potenza; **-3 dB** ≈ dimezzamento.
- **+6 dB** ≈ ×4; **+10 dB** = ×10; **+20 dB** = ×100.
- Formula: dB = 10 · log₁₀(P2/P1). Esempio: da 5 W a 50 W = +10 dB; da 100 W a 400 W = +6 dB.

## Linee di trasmissione e adattamento

### Cavo coassiale 50 ohm e perdite
Lo standard radioamatoriale è il cavo da 50 ohm (i ricetrasmettitori hanno uscita 50 ohm). Il 75 ohm è tipico TV/SAT. L'attenuazione cresce con la frequenza (effetto pelle, in prima approssimazione proporzionale alla radice della frequenza) ed è proporzionale alla lunghezza. Valori puramente indicativi di attenuazione in dB/100 m — verificare SEMPRE il datasheet del produttore (es. Messi & Paoloni, Times Microwave, SSB-Electronic), perché variano per lotto, costruttore e temperatura:

| Cavo | 14 MHz | 144 MHz | 432 MHz | 1296 MHz |
|------|--------|---------|---------|----------|
| RG-58 | ~3 dB | ~11 dB | ~22 dB | ~45 dB |
| RG-213 | ~1,8 dB | ~7 dB | ~13 dB | ~25 dB |
| Ecoflex 10 / LMR-400 | ~1,1 dB | ~4 dB | ~7 dB | ~13 dB |
| Ecoflex 15 / LMR-600 | ~0,8 dB | ~2,8 dB | ~5 dB | ~9 dB |

Regola pratica: 3 dB = metà potenza persa; 6 dB = un quarto; 10 dB = un decimo. In UHF/SHF usare cavi a bassa perdita e tratte corte (in microonde conviene portare l'apparato/preampli vicino all'antenna). La perdita reale aumenta ulteriormente con ROS elevato, perché l'onda riflessa percorre il cavo una seconda volta.

### ROS/SWR, return loss, coefficiente di riflessione
- ROS (SWR) = (1 + |Γ|) / (1 − |Γ|), dove Γ è il coefficiente di riflessione, con |Γ| = |Z_carico − Z_linea| / |Z_carico + Z_linea|. ROS 1:1 = adattamento perfetto.
- Coefficiente di riflessione: |Γ| = (ROS − 1) / (ROS + 1).
- Return Loss (dB) = −20·log₁₀|Γ| (valore positivo: più alto = meglio adattato).
- Potenza riflessa = |Γ|² · potenza diretta.

| ROS | Γ | Return Loss | Pot. riflessa |
|-----|------|-------------|---------------|
| 1,0 | 0 | ∞ | 0% |
| 1,5 | 0,20 | 14,0 dB | 4% |
| 2,0 | 0,33 | 9,5 dB | 11% |
| 3,0 | 0,50 | 6,0 dB | 25% |

In pratica si mira a ROS ≤ 1,5 (return loss ≥ 14 dB). Molti apparati riducono automaticamente la potenza (foldback/ALC di protezione) oltre ROS ~2:1 a salvaguardia dello stadio finale a stato solido.

### Come misurare il ROS — procedura
1. Apparato in modo a portante costante (CW, FM, oppure AM con portante o RTTY), a bassa potenza (5–10 W).
2. Inserire il rosmetro/wattmetro direzionale (es. Bird 43, Daiwa, MFJ) tra TX e cavo d'antenna, rispettando il verso FWD→antenna.
3. Misurare potenza diretta (FWD) e riflessa (REF); il ROS si legge sullo strumento o si calcola da FWD e REF.
4. In alternativa usare un analizzatore d'antenna / VNA (NanoVNA, RigExpert, MFJ-259/269): collegato all'ingresso linea, dà ROS, impedenza R+jX e return loss su tutta la banda — strumento preferibile perché non richiede di trasmettere a piena potenza ed evidenzia la risonanza.
5. Cercare il punto di minimo ROS (frequenza di risonanza) e regolare la lunghezza/elementi d'antenna: se il minimo è a frequenza troppo bassa l'antenna è lunga (accorciare), se troppo alta è corta (allungare). Promemoria: dipolo L(m) ≈ 142,5/f(MHz); verticale a 1/4 d'onda ≈ 71,25/f(MHz); λ ≈ 300/f(MHz).

### Balun e unun
- BALUN (BALanced-UNbalanced): collega una linea sbilanciata (coax) a un carico bilanciato (dipolo, delta loop, yagi). Evita correnti di modo comune sulla calza esterna e la conseguente distorsione del lobo di radiazione e RF in stazione.
- UNUN (UNbalanced-UNbalanced): adatta impedenze tra carichi entrambi sbilanciati (es. antenne verticali, end-fed).
- Rapporti comuni (rapporto di impedenza, = quadrato del rapporto spire):
  - 1:1 (balun di corrente/choke, per dipoli ~50–75 ohm)
  - 4:1 (≈200→50 ohm, dipoli ripiegati/folded, OCF-Windom)
  - 9:1 (≈450→50 ohm, end-fed random/long wire)
  - 49:1 (per EFHW, end-fed half-wave, da ≈2450→50 ohm)
- Il balun di corrente (choke/current balun) si può realizzare avvolgendo il coax su un nucleo in ferrite. Indicativamente: mix 31 per HF basse, mix 43 per HF alte/VHF (verificare l'impedenza di modo comune utile nella banda d'interesse).

### Accordatore d'antenna (ATU)
L'ATU NON "accorda l'antenna": trasforma l'impedenza vista dal TX a ~50 ohm, presentando al finale un carico adattato e proteggendolo. Il disadattamento e le relative perdite restano sul tratto di cavo a valle dell'ATU (verso l'antenna). Tipi: manuale a L o a T (es. circuito a T tipo MFJ), automatico interno al ricetrans, oppure automatico esterno posto vicino all'antenna (LDG, Icom AH-4/AH-705) — soluzione preferibile perché riduce le perdite sul coax disadattato. Procedura tipica di un auto-tuner: trasmettere ~10 W in CW, premere TUNE, attendere il latch dei relè e verificare il ROS finale ≤ 1,5.

Nota normativa (Italia): i numeri di attenuazione e impedenza variano per lotto, costruttore e temperatura — consultare i datasheet ufficiali. Per potenze e bande in Italia fare riferimento al Piano Nazionale di Ripartizione delle Frequenze (PNRF) e alla normativa del MIMIT (Ministero delle Imprese e del Made in Italy, ex MISE) e al Codice delle Comunicazioni Elettroniche: la patente/autorizzazione di classe A (ordinaria) consente fino a 500 W PEP in HF, mentre la classe B (ridotta) è limitata a 10 W. Utile anche il bandplan IARU Region 1 e la documentazione ARI.

## Apparati e stazione: ricetrasmettitori, amplificatori, potenza e misure

### Ricetrasmettitori (RTX)
- **HF**: 1,8–30 MHz (bande 160/80/40/30/20/17/15/12/10 m). Modi: SSB, CW, FT8/FT4, RTTY, AM, FM (FM ammessa solo nella porzione alta dei 10 m, ~29,3–29,7 MHz).
  - Convenzione banda laterale: **LSB sotto i 10 MHz** (160/80/40 m), **USB sopra i 10 MHz** (20/17/15/12/10 m). I 30 m (10,1 MHz) sono di fatto riservati a CW e modi digitali (no fonia per band plan IARU).
- **VHF/UHF**: 2 m (**144–146 MHz** in IARU R1) e 70 cm (**430–440 MHz** in IARU R1; in Italia uso tipico 430–440 MHz). Modi: FM, SSB/CW (porzione bassa di banda, "weak signal"), DMR/D-STAR/C4FM.
- Parametri chiave: sensibilità (es. ~0,16 µV per 10 dB S/N in SSB), filtri di media frequenza / **roofing filter** (es. 3 kHz SSB / 500 Hz CW / 250 Hz CW stretto), reiezione immagine, gamma dinamica e IP3.

### Potenza e limiti (Italia, IARU Regione 1)
La potenza si esprime in **PEP** (Peak Envelope Power, potenza di picco dell'inviluppo). I limiti italiani dipendono dalla classe di autorizzazione e dalla banda e sono fissati dalla normativa nazionale (Codice delle comunicazioni elettroniche, d.lgs. 259/2003 e s.m.i.) sotto la competenza del **MIMIT** (ex MISE). Valore di riferimento storico/tipico per il radioamatore "ordinario": **fino a 500 W PEP** (limiti ridotti possono applicarsi a determinate bande, sub-bande o per la classe con esame ridotto).

**Attenzione a non confondere il radiantismo con la CB (Citizen's Band)**: la CB opera sui 27 MHz con apparati e limiti propri (tipicamente **4 W AM/FM, 12 W PEP SSB**) e non rientra nelle bande radioamatoriali. I massimali radioamatoriali variano per banda e normativa vigente — **verificare sempre** il **Piano Nazionale di Ripartizione delle Frequenze (PNRF)**, i decreti MIMIT applicabili e la documentazione **ARI**, poiché soggetti ad aggiornamenti.

Relazione potenza/modo: in **SSB** il riferimento è il PEP (la potenza media è molto inferiore al picco e dipende dal contenuto vocale e dalla compressione); in **CW**, **FM** e in generale nei modi a inviluppo costante (RTTY/PSK a portante piena, FT8) la potenza media coincide sostanzialmente con il PEP — da cui il maggiore stress termico sul finale.

### Amplificatori lineari
Si inseriscono tra RTX (pilotaggio tipico 50–100 W) e antenna. Tecnologie: valvolari (es. **GU-74B**, **GS-35B**, **3-500Z**) o a stato solido (**LDMOS**, es. **BLF188XR**). Regole operative:
1. Adattare il carico: **ROS (SWR) ≤ 1,5:1** prima di trasmettere (preferibilmente con accordatore/antenna risonante).
2. Pilotare con la potenza minima necessaria; non superare il drive massimo dichiarato (rischio di overdrive, distorsione e splatter).
3. Rispettare il **duty cycle**: i modi a portante continua (FT8/RTTY/FM) stressano molto il finale — ridurre la potenza (indicativamente ~50% o secondo le specifiche del costruttore).
4. Lasciare riscaldare i valvolari (filamento) per il tempo prescritto prima del TX; sequenziare correttamente PTT/QSK.

### Alimentatori
Gli RTX a stato solido richiedono in genere **13,8 V CC**. Dimensionare la corrente: un VHF da 50 W FM assorbe ~10–11 A; un HF da 100 W fino a **~22–25 A** in picco. Preferire alimentatori **switching** (leggeri, ma attenzione alla RFI) o **lineari** (più pesanti, minor rumore RF). Margine consigliato: **+20%** sulla corrente di picco; curare massa e filtraggio.

### S-meter (unità S e dB)
Scala di riferimento IARU per **HF**: **S9 = −73 dBm** (= 50 µV su 50 Ω). Convenzione: **1 punto S = 6 dB**.

| Unità S | dBm (HF) | µV (50 Ω) |
|---|---|---|
| S1 | −121 | 0,2 |
| S5 | −97 | 3,2 |
| S9 | −73 | 50 |
| S9+20 | −53 | 500 |
| S9+40 | −33 | 5000 |

In **VHF/UHF** lo standard IARU è **S9 = −95 dBm** (≈ 0,1 µV su 50 Ω). Sopra S9 si legge "S9 più X dB" (es. rapporto "59+20"). Nota: la taratura reale degli S-meter è spesso imprecisa e non lineare — usare come indicazione relativa.

### Microfoni e fonia
- **Dinamici** (robusti, classici da palmo) vs **a condensatore/electret** (più sensibili, tipici da tavolo, richiedono alimentazione/bias).
- Impostare **MIC GAIN** e compressore (PROC/COMP) controllando l'**ALC**: deve restare nella zona indicata, senza saturare (saturazione → distorsione e **splatter** sulle frequenze adiacenti).
- Trasmissione tramite **PTT** sul microfono o **VOX** (commutazione vocale).

### Manipolatori e keyer
- **Tasto verticale** (straight key): manuale, ritmo libero.
- **Paddle** + **keyer elettronico** (modalità Iambic A/B): genera punti e linee automatici.
- Velocità in **WPM** (parole/minuto); riferimento **PARIS**: durata_punto(ms) = **1200 / WPM**. Es. 20 WPM → punto = 60 ms.
- Regolare **weight/ratio** (rapporto standard **linea:punto = 3:1**) e la spaziatura tra elementi/lettere/parole.

Per regolamenti, bande e potenze aggiornate consultare **MIMIT** (PNRF e decreti), **ARI**, il **band plan IARU Region 1** e **AMSAT** per i satelliti.

## Messa a terra, EMC/RFI, sicurezza: terra RF, soppressione disturbi, esposizione RF, fulmini, alta tensione

### Terra di radiofrequenza (RF ground)
Distinguere tre funzioni di terra, da non confondere: terra di sicurezza/protezione (PE, conduttore verde-giallo), terra di scarica fulmini (LPS) e terra di RF. La terra RF serve a evitare RF "che torna in shack" (microfono che "morde", tastiera che si pianta, bruciore sui metalli). Un picchetto interrato non è una terra RF efficace: a HF il filo di discesa è lungo elettricamente (la sua reattanza vanifica la connessione a massa).
- Usare radiali / contrappesi tagliati a λ/4. Lunghezza elettrica teorica λ/4 (m) ≈ 71,25 / f(MHz); applicando un velocity factor di ~0,95 per filo isolato: lunghezza (m) ≈ 67,7 / f(MHz). Es. su 14,2 MHz → ~5,02 m (teorico) ≈ 4,77 m (con VF 0,95).
- Per stazioni in appartamento, un piano di terra artificiale / accordatore di contrappeso (tipo MFJ-931 "artificial RF ground") o radiali multipli risolve meglio del solo picchetto.
- Collegare tutti i telai con treccia piatta larga (bassa induttanza), non filo tondo. Adottare una stella unica (single-point ground) ed evitare anelli di massa (ground loop).

### Soppressione disturbi (EMC/RFI)
- Ferriti: per RFI in uscita su cavi (alimentazione, USB, audio, controllo) usare nuclei in mix 31 (ottimo ~1–30 MHz, alta impedenza alle HF basse) oppure mix 43 (ottimo ~25–300 MHz, VHF). Avvolgere alcune spire del cavo sul toroide (tipicamente 5–7) per aumentare l'impedenza di modo comune; il numero ottimale dipende da frequenza e dimensione del nucleo.
- Choke balun 1:1 di modo comune all'alimentazione dell'antenna: es. ~10–12 spire di RG-316/RG-400 su un FT240-31 (per HF). Per le VHF preferire mix 43 e meno spire.
- Disturbi in ingresso (RX): identificare la fonte (alimentatori switching, impianti fotovoltaici/inverter, PLC, lampade e driver LED, caricabatterie). Spegnere i carichi uno a uno per localizzarli. Per gli inverter FV e gli apparati industriali valgono i limiti di emissione EN 55011 / CISPR 11; le interferenze persistenti vanno segnalate (compatibilità elettromagnetica) anche all'Ispettorato territoriale del MIMIT.
- Filtri di rete e capacità di bypass (condensatori di classe X tra fase/neutro e Y verso terra), separazione dei cavi RF dai cavi dati/segnale.

### Esposizione ai campi RF (limiti Italia)
Riferimento normativo: Legge quadro 36/2001 e DPCM 8/7/2003 ("Fissazione dei limiti di esposizione, dei valori di attenzione e degli obiettivi di qualità... tra 100 kHz e 300 GHz"). Il Codice delle comunicazioni elettroniche è il D.Lgs. 259/2003 (aggiornato dal D.Lgs. 207/2021 e dal D.Lgs. 48/2024) — NB: non esiste un "D.Lgs. 159/2024" in materia. Valori per la popolazione (banda ~100 kHz–300 GHz, valori efficaci):
- Limite di esposizione del campo elettrico E: 20 V/m fino a 3 GHz (40 V/m sopra 3 GHz).
- Valore di attenzione e obiettivo di qualità: 6 V/m (luoghi a permanenza non inferiore a 4 ore/giorno e aree intensamente frequentate), mediato su qualsiasi intervallo di 6 minuti.
- Per i radioamatori l'obbligo di valutazione/comunicazione e la relativa modulistica dipendono dalla potenza, dal guadagno d'antenna e dalla situazione installativa; le soglie e le procedure variano a livello regionale (ARPA) e secondo le indicazioni MIMIT. VERIFICARE su MIMIT e ARPA regionale prima di installare.
- Calcolo della distanza di sicurezza (campo lontano, antenna isotropa equivalente). Densità di potenza: S = (P·G) / (4·π·d²). In termini di campo E: E = √(30·P·G) / d, da cui d = √(30·P·G) / E. Es. P = 100 W, G = 2 (numerico, lineare), limite 6 V/m → d = √(30·100·2) / 6 = √6000 / 6 ≈ 77,46 / 6 ≈ 12,9 m. Considerare il duty cycle del modo (CW/SSB ~20–50% medio, FM/RTTY/digitali a portante continua ~100%) e, se rilevante, il fattore di occupazione temporale.

### Protezione dai fulmini
- Sezionatore/staccatore d'antenna fisico quando la stazione è inattiva o in arrivo di temporali; non basta lo strumento di SWR né lo spegnimento del TX.
- Scaricatori (arrestor) a gas (gas-tube) su ogni linea coassiale, montati su una barra/pannello di terra unico all'ingresso dell'edificio (single-point entry panel).
- Dispersori (picchetti) ≥2 m, più picchetti collegati tra loro, resistenza di terra idealmente <10 Ω. Conduttore di terra in rame con sezione adeguata (≥16 mm² per i collegamenti di protezione/equipotenziali; verificare CEI EN 62305 per i conduttori di calata dell'LPS).
- Equipotenzializzare torre, rotore, schermi dei coassiali e PE dell'edificio verso lo stesso nodo di terra. Riferimento: serie CEI EN 62305 (protezione contro i fulmini).

### Alta tensione (amplificatori valvolari)
- Tensioni anodiche da ~1 a 4 kV (e oltre): potenzialmente letali. Prevedere interlock sul coperchio, resistori di bleeder per scaricare i condensatori di filtro, e attendere comunque verificando con voltmetro prima di toccare qualsiasi parte.
- Regola "una mano in tasca", calzature isolanti, pavimento asciutto, mai operare da soli. Scaricare manualmente i condensatori di filtro con un resistore montato su asta/bastone isolante, collegato a massa, prima di intervenire.

Fonti da consultare per i dati variabili nel tempo: MIMIT (autorizzazioni, classi e limiti di potenza — es. 500 W PEP classe A, 50 W classe B per f ≥ 30 MHz; Allegato n. 26 al D.Lgs. 259/2003), ARPA regionale (campi EM e DPCM 8/7/2003), ARI, IARU Region 1 (band plan), normativa serie CEI EN 62305 e CISPR 11 / EN 55011.

## DXing: caccia al DX, DX cluster, split, pile-up e gestione QSL

Il **DXing** è la ricerca di collegamenti con stazioni lontane o rare (DX = distanza). Obiettivi tipici: nuove **entità DXCC** (circa 340 attive; la DXCC List è gestita dall'ARRL) e premi come DXCC, WAZ, WAS, WPX, IOTA, spesso inseguiti durante le spedizioni (DXpedition).

### DX cluster e spotting
Il **DX cluster** è una rete che condivide "spot": chi sente una stazione rara la segnala in tempo reale. Formato spot tipico:
`DX de IK2XYZ: 14195.0 3B7M up 5 CW` → lo spotter IK2XYZ ha sentito 3B7M (St. Brandon, gruppo Agalega & St. Brandon) su 14195.0 kHz, che lavora in split "up 5" (ascolta 5 kHz sopra la propria frequenza di trasmissione).

Nota sul modo: nello spot l'ultimo campo indica il modo (es. CW, SSB, FT8). In SSB sui 20 m si usa per convenzione **USB** (LSB è riservata alle bande basse 160/80/40 m); fai attenzione perché alcuni spot riportano il modo in modo impreciso.

- Accesso via Telnet (es. cluster ARI/DXSpider), web (DX Summit, HamAlert) o integrato nel log (Log4OM, N1MM+, DXLab).
- Utile incrociare con la **RBN** (Reverse Beacon Network), basata su skimmer CW/digitali, e con i cluster aggregati agli skimmer.
- Propagazione: verifica con previsioni (es. VOACAP) e con gli indici **SFI** (Solar Flux Index), **A** e **K** pubblicati da NOAA/SWPC.

### Split: cos'è e perché
In split la DX **trasmette su una frequenza** e **ascolta su un'altra**, per non essere coperta dalla folla che chiama. "Up 5/10" o "QSX 14200" indicano dove la DX ascolta.

Procedura passo-passo (VFO separati, tasto SPLIT del transceiver):
1. Sintonizza VFO A sulla frequenza di trasmissione della DX (es. 14195.0).
2. Attiva SPLIT; imposta VFO B nella finestra d'ascolto (es. 14200–14205).
3. **Ascolta prima** chi viene chiamato e dove: capisci se la DX sale o scende progressivamente in frequenza, o se resta ferma.
4. Chiama dove la DX sta effettivamente raccogliendo, non necessariamente sull'ultimo QSO.

### Gestione del pile-up
- Manda il **nominativo completo una volta**, con fonetica ITU/NATO (Alfa, Bravo, Charlie...), poi ascolta.
- Non chiamare se la DX dà un parziale (es. "IK2? only" oppure "...XYZ?"): sta richiamando una sola stazione.
- In CW invia alla velocità della DX; in **FT8/FT4** usa la modalità **Fox/Hound** (tu sei Hound) per le DXpedition: gli Hound chiamano inizialmente sotto 1000 Hz e il software, sotto controllo del Fox, gestisce automaticamente lo split spostando le stazioni agganciate sopra 1000 Hz.
- Potenza: usa il minimo necessario. In Italia il limite di potenza per la **classe A** (patente ordinaria, ex licenza completa) è **500 W** di potenza fornita all'antenna (PEP, output), mentre la **classe B** è limitata a **10 W**. Verifica condizioni, bande e limiti aggiornati nel Piano Nazionale di Ripartizione delle Frequenze (PNRF) e presso il **MIMIT**. Esagerare con la potenza non vince il pile-up: contano tempismo e frequenza giusta.

### Conferme: QSL e sistemi elettronici

| Sistema | Come funziona | Note |
|---|---|---|
| **QSL cartacea** | Cartolina via posta o **bureau** | Bureau ARI economico ma lento (mesi/anni); diretta con SAE e affrancatura di ritorno tramite **green stamp** (1–2 USD). Gli **IRC** sono di fatto dismessi (ultimi coupon scaduti nel 2025) |
| **QSL manager** | Terzo che gestisce le QSL della DX (indicato come "via XX") | Cerca il manager su **QRZ.com** o nei database (es. Club Log) |
| **LoTW** (Logbook of The World, ARRL) | Conferme digitali firmate con certificato | Valido per **DXCC, WAS, VUCC** (ARRL) e, tramite accordo con CQ, per **CQ WAZ e CQ WPX**; richiede certificato ARRL gratuito |
| **eQSL** | Conferma elettronica immediata | Valido per i premi **eQSL** (es. eAward/DXCC di eQSL) e alcuni terzi; **non valido per il DXCC ARRL** |
| **OQRS** (Online QSL Request System, Club Log) | Richiesta QSL online, diretta o via bureau | Standard nelle DXpedition moderne; spesso con donazione facoltativa |

**Buone pratiche QSL:** indica sempre data e ora in **UTC**, banda o frequenza, modo e RST. Per LoTW carica l'**ADIF** esportato dal log e firmato con TQSL; il match con la controparte è automatico. Per IOTA usa **iota.world**; per i diplomi ARI consulta **ari.it**.

> Dati su bande, potenze e procedure possono cambiare: verifica sempre presso **MIMIT**, **ARI**, **IARU Region 1** e i siti ufficiali **ARRL**/**Club Log**.

## Contest e diplomi radioamatoriali

### Contest: tipi e scambi tipici
Un contest premia il numero di collegamenti (QSO) validi in un tempo dato. Lo **scambio** (exchange) varia per regolamento:
- **RS(T) + numero progressivo**: tipico SSB/CW (es. ARI International DX Contest, dove le stazioni italiane passano RS(T) + sigla della provincia, es. "59 MI").
- **RS(T) + zona CQ**: CQ WW DX Contest. L'Italia peninsulare e le isole italiane sono in **zona CQ 15** (continente europeo, zona 28 ITU); la Sardegna (IS0) è in **zona CQ 33** (e zona ITU 28). Attenzione: la zona CQ 33 è africana per la geografia delle zone CQ, ed è il motivo per cui IS0 vale come moltiplicatore distinto.
- **RS(T) + numero progressivo (CQ WPX)**: il CQ WPX premia i **prefissi unici** (es. IK2, I2, IZ8...) come moltiplicatori; lo scambio è RS(T) + nr progressivo, **non** la zona ITU.
- **RS(T) + nr + locatore (QTH locator Maidenhead)**: contest VHF/UHF e superiori (es. ARI VHF, contest IARU VHF), scambio del tipo "59 001 JN45" (la maggior parte dell'Italia ricade nei quadranti **JN**, es. JN45 area lombarda, JN61 area di Roma).

**Bande e modi**: in HF i contest usano tipicamente le bande "tradizionali" 1,8 / 3,5 / 7 / 14 / 21 / 28 MHz (le bande WARC 10 / 18 / 24 MHz sono per regolamento **escluse** dai contest); in VHF/UHF 50 / 144 / 432 MHz. Rispettare il **band plan IARU Regione 1** (segmenti CW, digitali e fonia, finestre DX e centri di attività) e i limiti di potenza italiani.

**Potenza in Italia (MIMIT)**: il valore di riferimento per le stazioni ordinarie è **500 W** di potenza (riferita all'uscita dell'apparato / fornita all'antenna, **non** EIRP); esistono classi/autorizzazioni con limiti inferiori (es. 10 W per attività iniziali/temporanee). Verificare sempre l'autorizzazione generale e il piano frequenze vigente presso il **MIMIT**.

**Punteggio**: tipicamente *Punti QSO × Moltiplicatori*. I moltiplicatori sono entità/zone/prefissi/locatori unici, di norma conteggiati per banda.

### Strategie operative
- **Run vs S&P**: il *run* (chiamare CQ tenendo una frequenza propria) massimizza il rate quando si è ben sentiti; il *Search & Pounce* (cercare le stazioni e chiamarle) serve soprattutto per raccogliere moltiplicatori.
- **Propagazione e orari**: di giorno privilegiare le bande alte (21/28 MHz, e 14 MHz) per il lungo raggio, di notte le bande basse (3,5/1,8 MHz). Consultare le previsioni propagative: numero di macchie solari (numero di Wolf / SSN), flusso solare a 10,7 cm (SFI) e indici geomagnetici **K/A**.
- **Dupe check** con il log elettronico (es. N1MM Logger+, DXLog, SD) per evitare doppioni.
- **Invio log**: di norma in formato **Cabrillo**, entro i giorni previsti dal regolamento del singolo contest.

### Diplomi principali (requisiti)

| Diploma | Ente | Requisito base |
|---|---|---|
| **DXCC** | ARRL | 100 entità DXCC confermate (su ~340 entità attive) |
| **WAS** | ARRL | Tutti i 50 stati USA confermati |
| **WAC** | IARU (rilasciato da ARRL/altre società) | Tutti i 6 continenti confermati |
| **WAE** | DARC | Collegamento dei paesi della lista WAE Europa (entità europee, parzialmente diverse dal DXCC) |
| **IOTA** | RSGB / IOTA Ltd | "Islands On The Air": 100 gruppi di isole confermati per il certificato base |
| **SOTA** | SOTA MT | "Summits On The Air": attivatori e cacciatori; 1000 punti come attivatore = "Mountain Goat", 1000 punti come cacciatore = "Shack Sloth" |
| **POTA** | POTA LLC | "Parks On The Air": per l'attivatore servono almeno **10 QSO** per validare l'attivazione di un parco |
| **WWFF** | WWFF | "World Wide Flora & Fauna": **44 QSO** validi per attivare un'area protetta |

**Note operative diplomi**:
- **DXCC**: conferme via **QSL cartacea** o **LoTW** (Logbook of The World, ARRL). Disponibili endorsement per banda e per modo (CW, fonia, digitale), oltre alle varianti del diploma (Mixed, Phone, CW, 5BDXCC, ecc.).
- **IOTA**: ogni gruppo di isole ha un riferimento (es. **EU-025** = Sicilia). Gestione collegamenti e conferme su iota-world.org (sistema QSL/match elettronico).
- **SOTA/POTA/WWFF**: si caricano i log sui rispettivi siti; il **chaser** (cacciatore) e l'**activator** (attivatore) ottengono punti distinti. Frequenze tipiche di chiamata (centri di attività, da usare nel rispetto del band plan e dei segmenti QRP): **7,030 / 14,060 MHz in CW**, **7,090 / 14,285 MHz in SSB**, e in VHF **144,300 MHz SSB** / **145,500 MHz FM** (canale di chiamata FM).

### Verifica dati
Requisiti, liste, frequenze e punteggi cambiano nel tempo: consultare sempre le fonti ufficiali — **ARRL** (DXCC/WAS/WAC), **RSGB / IOTA Ltd** (iota-world.org), **sota.org.uk**, **parksontheair.com**, **wwff.co**, **DARC** (WAE), **ARI** per i contest e i diplomi nazionali, e il **MIMIT** per frequenze e potenze autorizzate in Italia.

## Maidenhead Locator: struttura, conversione, distanza e azimuth

Il **Maidenhead Locator System** (o QTH Locator) codifica una posizione geografica in una stringa alfanumerica. Fu ideato dal gruppo di lavoro VHF della IARU Regione 1 e adottato nel 1980, durante una riunione tenutasi a **Maidenhead, nel Kent (Inghilterra)** — da cui il nome. È lo standard per contest VHF/UHF/SHF, EME, meteor scatter e collegamenti via satellite.

### Struttura del locatore
La stringa alterna coppie di lettere e cifre, dalla risoluzione più grossolana alla più fine. Ogni coppia contiene **prima il carattere di longitudine, poi quello di latitudine**:

| Livello | Caratteri | Esempio | Passo longitudine | Passo latitudine |
|---|---|---|---|---|
| Campo (field) | 2 lettere A–R | JN | 20° | 10° |
| Quadrato (square) | 2 cifre 0–9 | 61 | 2° | 1° |
| Sottoquadrato (subsquare) | 2 lettere a–x | fm | 5′ (0,08333°) | 2,5′ (0,04167°) |
| Estensione | 2 cifre 0–9 | (8 char) | 30″ | 15″ |

Esempio: **JN61fm**. Sei caratteri costituiscono il locatore standard. Nota: le lettere di campo arrivano fino alla **R** (18 valori → 18 × 20° = 360° di longitudine e, per la latitudine, 18 × 10° = 180°); le lettere di sottoquadrato vanno da **a** a **x** (24 valori). L'origine è all'**anti-meridiano nell'emisfero sud** (180° O, 90° S), quindi i valori crescono verso Est e verso Nord.

### Conversione lat/lon → locatore (6 caratteri)
Con longitudine λ e latitudine φ in gradi decimali (Est e Nord positivi):
1. λ′ = λ + 180 ; φ′ = φ + 90
2. **Campo**: lon = `A` + int(λ′/20) ; lat = `A` + int(φ′/10)
3. **Quadrato**: lon = int((λ′ mod 20)/2) ; lat = int(φ′ mod 10)
4. **Sottoquadrato**: lon = `a` + int((λ′ mod 2)/(2/24)) ; lat = `a` + int((φ′ mod 1)/(1/24))

Verifica inversa — angolo SW del sottoquadrato JN61fm = 41,5° N, 12,4167° E; **centro** del sottoquadrato (aggiungendo mezzo passo, cioè +1,25′ lat e +2,5′ lon) ≈ **41,521° N, 12,458° E**. Per i calcoli di distanza/azimuth si usa sempre il centro.

### Distanza e azimuth tra due locatori
1. Converti entrambi i locatori al **centro** del sottoquadrato (lat/lon decimali).
2. Distanza great-circle. La formula seguente è la **legge sferica dei coseni** (semplice ma con perdita di precisione su distanze brevi; per QRB ravvicinati è preferibile la vera **haversine**), con R = 6371 km:
   - d = R · arccos( sin φ₁ · sin φ₂ + cos φ₁ · cos φ₂ · cos(λ₂ − λ₁) )
   - Haversine (più robusta): a = sin²(Δφ/2) + cos φ₁ · cos φ₂ · sin²(Δλ/2) ; d = 2R · atan2(√a, √(1−a))
   - Gli angoli vanno espressi in radianti.
3. Azimuth iniziale (bearing) dalla stazione 1 verso la 2:
   - θ = atan2( sin(Δλ) · cos φ₂ , cos φ₁ · sin φ₂ − sin φ₁ · cos φ₂ · cos Δλ ), con Δλ = λ₂ − λ₁, normalizzato a 0°–360°.

L'azimuth fornisce il puntamento dell'antenna per tropo/MS/EME terrestre; il **QRB** (distanza) determina i punti nei contest VHF (tipicamente **1 punto/km** nei contest IARU R1, ma **verifica sempre il regolamento** ARI/IARU della prova specifica).

### Campi italiani JN e JM
L'Italia è coperta principalmente dal campo **JN** (longitudine 0°–20° E, latitudine 40°–50° N), che comprende Nord e Centro fino circa al parallelo 40° N. La **Sicilia, la Sardegna meridionale e le isole minori del Sud** (latitudine < 40° N) ricadono nel campo **JM** (longitudine 0°–20° E, latitudine 30°–40° N). Il confine JN/JM corre lungo il **parallelo 40° N**.

Esempi (locatore a 6 caratteri):
- Milano **JN45**ol
- Bologna **JN54**ql
- Roma **JN61**fv
- Cagliari **JM49**nf (sotto i 40° N → JM, **non** JN)
- Palermo **JM68**qc (tutta la Sicilia è in JM, essendo sotto i 40° N)
- Lampedusa **JM65**hm
- Pantelleria **JM56**xt (non JM67)

### Note operative
- Usa sempre 6 caratteri nei log/contest VHF; 4 caratteri sono troppo grossolani per un QRB attendibile.
- Attenzione all'ordine longitudine-latitudine e all'uso del **centro** del sottoquadrato per i calcoli.
- Tool affidabili per la conversione: funzioni integrate nei software di logging, siti come QRZ.com o i calcolatori IARU; verifica le coordinate con un GPS reale.
- Le bande e i punteggi dei contest cambiano: consulta i regolamenti ufficiali **ARI** (contest VHF nazionali) e **IARU Region 1** per le regole aggiornate. Per le allocazioni di frequenza in Italia il riferimento normativo è il **MIMIT** (Piano Nazionale di Ripartizione delle Frequenze, PNRF).

## Elettronica e misure per radioamatori

### Legge di Ohm e potenza
Relazioni fondamentali (corrente continua o valori efficaci RMS):
- V = I × R
- I = V / R
- R = V / I

Potenza:
- P = V × I = I² × R = V² / R

Esempio: un finale alimentato a 13,8 V che assorbe 22 A in trasmissione consuma P = 13,8 × 22 = 303,6 W (potenza in ingresso DC; la potenza RF in uscita è inferiore per via del rendimento dello stadio finale).

### Decibel
Il decibel è un rapporto logaritmico (un decimo di bel).
- Rapporto di potenza: dB = 10 × log₁₀(P₂ / P₁)
- Rapporto di tensione (a parità di impedenza): dB = 20 × log₁₀(V₂ / V₁)

Valori utili da memorizzare:

| Rapporto potenza | dB |
|---|---|
| 2× | +3,01 dB (≈ +3) |
| 4× | +6,02 dB (≈ +6) |
| 8× | +9,03 dB (≈ +9) |
| 10× | +10 dB |
| 100× | +20 dB |
| 1000× | +30 dB |
| 0,5× | -3,01 dB (≈ -3) |

Regola pratica: ogni +3 dB raddoppia la potenza, ogni +10 dB la decuplica. I decibel si sommano: +6 dB = +3 +3 (cioè 2× × 2× = 4×).

Unità assolute:
- dBm = 10 × log₁₀(P / 1 mW) — riferimento 1 mW.
- dBW = 10 × log₁₀(P / 1 W) — riferimento 1 W. Relazione: dBW = dBm − 30.

Antenne (guadagno):
- dBi = guadagno rispetto al radiatore isotropico ideale.
- dBd = guadagno rispetto al dipolo a mezz'onda in spazio libero.
- Conversione: dBi = dBd + 2,15 (il dipolo ha 2,15 dBi di guadagno rispetto all'isotropico).

### Conversione watt ↔ dBm
- dBm = 10 × log₁₀(P_W × 1000) = 10 × log₁₀(P_W) + 30
- P_W = 10^((dBm − 30) / 10)

| Potenza | dBm |
|---|---|
| 1 mW | 0 dBm |
| 10 mW | +10 dBm |
| 1 W | +30 dBm |
| 5 W (palmare VHF/UHF) | +37 dBm (≈ +36,99) |
| 100 W | +50 dBm |
| 500 W | +57 dBm (≈ +56,99) |
| 1000 W | +60 dBm |

Nota normativa: i limiti di potenza in Italia dipendono dalla banda e dal tipo di autorizzazione e vanno verificati sulla normativa vigente del MIMIT (ex MISE) e sul Piano nazionale di ripartizione delle frequenze (PNRF), perché soggetti ad aggiornamenti. In via indicativa, per la patente/autorizzazione generale ordinaria il limite tipico è dell'ordine di 500 W in molte bande HF, con valori inferiori in alcune bande (ad es. limiti più bassi su 50 MHz, 70 MHz e sulle bande LF/MF come 137 kHz e 472 kHz). Attenzione: IARU e ARI sono organizzazioni associative e non emettono "bandi" di potenza; i limiti sono fissati dalla normativa statale.

### Impedenza e reattanza
L'impedenza Z è la "resistenza" in regime alternato: Z = R + jX (componente resistiva R + reattanza X).
- Reattanza induttiva: X_L = 2 × π × f × L (cresce con la frequenza).
- Reattanza capacitiva: X_C = 1 / (2 × π × f × C) (diminuisce con la frequenza).

Esempio: a 7,1 MHz una induttanza di 1 µH presenta X_L = 2 × π × 7,1×10⁶ × 1×10⁻⁶ ≈ 44,6 Ω.

Risonanza serie/parallelo quando X_L = X_C: f = 1 / (2 × π × √(L×C)).

L'impedenza standard di apparati, cavi coassiali e antenne in HF/VHF/UHF è 50 Ω.

### Formule rapide per antenne
Frequenza f in MHz, lunghezze in metri:
- Lunghezza d'onda: λ = 300 / f
- Dipolo a mezz'onda (con fattore di accorciamento ≈ 0,95): L ≈ 142,5 / f
- Verticale a quarto d'onda: L ≈ 71,25 / f

### Rapporto d'onda stazionaria (ROS / SWR)
Misura l'adattamento tra linea (50 Ω) e carico.
- Coefficiente di riflessione: Γ = (Z_L − Z₀) / (Z_L + Z₀)
- ROS = (1 + |Γ|) / (1 − |Γ|)

| Z carico resistivo (su 50 Ω) | ROS |
|---|---|
| 50 Ω | 1,0 : 1 |
| 75 Ω | 1,5 : 1 |
| 100 Ω | 2,0 : 1 |
| 150 Ω | 3,0 : 1 |
| 25 Ω | 2,0 : 1 |

Nota: il ROS dipende dal rapporto tra le impedenze; sia 100 Ω sia 25 Ω su 50 Ω danno ROS 2,0 : 1.

Potenza riflessa (frazione della potenza incidente): ROS 1,5 riflette circa il 4%, ROS 2,0 circa l'11%, ROS 3,0 circa il 25%.

Procedura di misura con rosmetro/accordatore:
1. Inserire il rosmetro tra TX e antenna, il più vicino possibile all'apparato (o all'ingresso della linea).
2. Selezionare la banda e una frequenza centrale.
3. Trasmettere a bassa potenza con portante stabile (CW o AM/FM, 5-10 W), con emissione che non disturbi altri utenti.
4. Leggere il ROS; ripetere ai bordi banda per valutare la larghezza di banda dell'antenna.
5. Regolare la lunghezza/gli elementi dell'antenna (non l'accordatore) per minimizzare il ROS reale al punto di alimentazione.

Linea guida pratica: ROS ≤ 1,5 ottimo, ≤ 2,0 accettabile; molti finali a stato solido riducono automaticamente la potenza (foldback) sopra 2,0-3,0 per protezione. Verificare sempre la specifica del proprio apparato sul manuale del costruttore.

## Reti e modi voce digitali: ripetitori, EchoLink, DMR, D-STAR, C4FM/Fusion, hotspot, APRS ed emergenza

### Ripetitori FM (shift e toni)
In Italia (piano di banda IARU Region 1) i ripetitori usano shift standardizzati:
- **VHF (banda 2 m, 145 MHz)**: shift **−600 kHz**. La RTX **trasmette 600 kHz sotto** la frequenza di uscita del ripetitore (cioè sotto la frequenza che si ascolta). Gli ingressi sono nel segmento **145,000–145,1875 MHz** e le uscite in **145,600–145,7875 MHz** (canalizzazione tipica 12,5 kHz).
- **UHF (banda 70 cm, 430 MHz)**: shift **−1,6 MHz**. Ingressi tipici **431,xxx MHz**, uscite **438,xxx MHz** (canalizzazione 12,5/25 kHz). (Nota: lo shift di −7,6 MHz NON è previsto dal piano italiano; in altre Regioni IARU si usano valori diversi, es. −5 MHz in R2.)

Per accedere serve quasi sempre un **subtono CTCSS** (es. **67,0 / 88,5 / 100,0 / 123,0 Hz**); il valore è specifico del singolo ponte. Procedura: imposta la frequenza d'uscita, attiva lo shift (RTX) e il CTCSS, premi PTT lasciando un attimo prima di parlare e attendendo la "coda" del ripetitore, e usa il **nominativo (callsign)** all'inizio e alla fine del QSO.

### EchoLink
VoIP che collega RTX/ponti/PC via Internet. Registrazione su **echolink.org** con **validazione della licenza** (occorre fornire copia dell'autorizzazione/patente). Si compone il **nodo** in DTMF: il **numero di nodo** (variabile, fino a più cifre, es. nodo del ripetitore o della conferenza), **#** per disconnettere, **08** per random link (collegamento casuale), ***** per richiedere informazioni/stato del nodo. I comandi DTMF esatti possono variare in base alla configurazione del nodo/conferenza; consultare l'help del singolo nodo. Tipici nodi italiani sono associati a ponti e conferenze locali.

### DMR (Brandmeister / DMR-MARC)
Standard ETSI a **TDMA su 2 time slot** (canale a 12,5 kHz che porta 2 comunicazioni). Parametri da configurare nel **codeplug**:
- **Color Code** (0–15, deve coincidere con quello del ripetitore).
- **Time Slot 1 o 2**.
- **Talkgroup (TG)**: su Brandmeister, in Italia **TG 222** (nazionale), **TG 2221–2228** regionali (verificare l'assegnazione sul portale **brandmeister.network**), **TG 9** locale (solo sullo slot/ponte in uso), **TG 91** mondiale, **TG 92** Europa.
Il **DMR ID** personale si richiede su **radioid.net** (gratuito, una sola volta, legato al nominativo). I TG si attivano in modo **dinamico** premendo il PTT sul TG desiderato, oppure si impostano come **statici** dalla dashboard dell'hotspot/SelfCare Brandmeister.

### D-STAR
Standard sviluppato in ambito JARL e diffuso da ICOM; vocoder **AMBE**. Reti: **REF** (D-Plus), **XRF/DCS** (DExtra/D-Plus alternativi), **XLX** (multiprotocollo). Campi di routing **UR / RPT1 / RPT2**:
- **UR** = comando di routing/linking (es. `REF030CL` per linkare il reflector REF030 modulo C; `       U` — sette spazi seguiti da `U` — per fare unlink).
- **RPT1** = ripetitore/modulo locale (es. `IXxxx  B`).
- **RPT2** = gateway, con `G` nell'ottava posizione (es. `IXxxx  G`).

### C4FM / System Fusion (Yaesu)
Modalità **DN** (V/D, voce + dati a velocità ridotta) e **VW** (Voice Wide, voce a banda piena). Rete **WIRES-X** con **room** numerate. I ponti Fusion supportano spesso anche FM analogico tramite **AMS** (Automatic Mode Select), che commuta automaticamente tra C4FM e FM. Vocoder **AMBE+2**.

### Hotspot
Dispositivi (Pi-Star / WPSD su Raspberry Pi + scheda **MMDVM**, es. **ZUMspot, Jumbospot**) per accesso ai modi digitali con bassa potenza (**~10 mW**) su frequenza **simplex** scelta in un segmento libero (es. **434,xxx MHz** o **438,xxx MHz**, evitando ingressi/uscite ponti e la frequenza APRS 144,800). Multimodo: DMR, D-STAR, YSF (Fusion), NXDN, P25, M17. Configurazione via interfaccia web Pi-Star (Configuration → MMDVMHost), inserendo nominativo, DMR ID, frequenza e reti.

### APRS
Packet **AX.25** a **1200 baud** (AFSK in VHF). Frequenza primaria in **IARU Region 1 / Italia: 144,800 MHz**. SSID convenzionali comuni: **-9** stazione mobile/veicolo, **-7** palmare (HT), **-5** smartphone/altri client IP, **-1/-2** digipeater/igate fissi. I **digipeater** (path tipico **WIDE1-1**, **WIDE2-1**) ritrasmettono i pacchetti, mentre gli **i-gate** li inoltrano ad **APRS-IS** (Internet); le posizioni si visualizzano su **aprs.fi**.

### Radiantismo di emergenza ed ARI
L'**ARI** (Associazione Radioamatori Italiani) coordina **ARI-RE** (Radioamatori per l'Emergenza), in convenzione con il **Dipartimento della Protezione Civile**. In emergenza si privilegiano frequenze di chiamata/coordinamento e procedure di rete gestite da una stazione di **net control**. Le frequenze operative e i protocolli sono definiti dai piani locali/nazionali ARI-RE. Vanno ricordate le procedure di traffico (prowords, prosegni Morse, uso dell'alfabeto fonetico NATO/ICAO per lo spelling dei nominativi) e l'uso disciplinato del canale.

> **Verifica sempre** i dati variabili (frequenze ponti, CTCSS, TG, normativa potenze/bande) su: **MIMIT** (normativa e PNRF), **ARI** (ari.it), **radioid.net**, **brandmeister.network**, **IARU Region 1** e **aprs.fi**. Le **potenze massime** e i **segmenti di banda** in Italia sono fissati dal **PNRF** e dalla normativa **MIMIT** (per i radioamatori la potenza è tipicamente espressa in p.e.p.; consultare i limiti per classe/banda nella versione vigente del provvedimento).

## Cultura, galateo e storia: codice di condotta, galateo in banda e glossario

### Codice di condotta (Ham Spirit)
Il radioamatore italiano si ispira all'**Amateur's Code** di Paul M. Segal (W9EEA, 1928): è *cavaliere/considerato* (considerate), *leale* (loyal), *progressista* (progressive), *amichevole* (friendly), *equilibrato* (balanced) e *patriottico* (patriotic). Principi pratici: ascoltare prima di trasmettere, non interferire mai volontariamente, usare la **minima potenza necessaria** alla comunicazione. Questo principio è sancito dal Regolamento Radio ITU per il servizio di radioamatore (articolo 25 — *Amateur services*) e ribadito nella normativa italiana (Codice delle Comunicazioni Elettroniche, D.Lgs. 259/2003 e successive modifiche, con i relativi allegati sui radioamatori). Fornire assistenza nelle comunicazioni di emergenza ha sempre priorità assoluta.

> Nota: i sei aggettivi del codice sono cinque "virtù" più il richiamo al patriottismo nella formulazione originale; le traduzioni italiane variano leggermente ma il senso è quello sopra.

### Galateo in banda (operating practice)
Procedura passo-passo per iniziare un QSO:
1. **Ascolta** la frequenza per almeno 15-30 secondi.
2. Chiedi: *"È libera la frequenza? Qui IZ0XXX"* (in inglese: *"Is this frequency in use? This is IZ0XXX"*). Attendi una risposta.
3. Se libera, **chiama CQ**: *"CQ CQ CQ qui India Zulu Zero X-ray X-ray X-ray, in ascolto"* (in fonia internazionale il nominativo va scandito con l'alfabeto fonetico ICAO/NATO).
4. Quando rispondi a una chiamata, dai **prima il nominativo dell'altra stazione, poi il tuo** (es. *"IK0YYY qui IZ0XXX"*).

Regole chiave:
- Identificarsi con il **proprio nominativo** all'inizio e alla fine del collegamento, e a intervalli regolari durante i QSO lunghi (buona prassi; per gli obblighi vigenti consultare il MIMIT — Ministero delle Imprese e del Made in Italy, ex MISE).
- Lasciare **pause** tra le trasmissioni in SSB/FM per consentire inserimenti (break) o eventuali chiamate di emergenza.
- Non occupare la frequenza di chi sta già operando; rispettare i **band plan IARU Regione 1** (l'Italia appartiene alla Regione 1). Esempi sui 20 m: centro di attività **CW QRP ~14.060 MHz**, frequenza di chiamata **FT8 14.074 MHz**, centro di attività **SSB DX ~14.195 MHz**; verificare sempre l'edizione aggiornata del band plan su iaru-r1.org.
- In FM su ripetitore: attendere la fine della coda/"beep" prima di rispondere e lasciare pause per consentire al ripetitore di rilasciare (e per far entrare altre stazioni o un break).

### Alfabeto fonetico (ICAO/NATO)
A Alfa · B Bravo · C Charlie · D Delta · E Echo · F Foxtrot · G Golf · H Hotel · I India · J Juliett · K Kilo · L Lima · M Mike · N November · O Oscar · P Papa · Q Quebec · R Romeo · S Sierra · T Tango · U Uniform · V Victor · W Whiskey · X X-ray · Y Yankee · Z Zulu.
Cifre: 0 Zero · 1 One · 2 Two · 3 Three · 4 Four · 5 Five · 6 Six · 7 Seven · 8 Eight · 9 Nine (in fonia ham spesso pronunciate "niner" per il 9).

### Significato di 73 e 88
Numeri derivati dai codici telegrafici dell'era del telegrafo (in particolare il **Phillips Code**, codificato/pubblicato nel 1879 da Walter P. Phillips; molti numeri-saluto circolavano già prima):
- **73** = "distinti saluti / cordiali saluti" (best regards). È già plurale nel significato: si dice *"73"*, **non "73s"**.
- **88** = "baci e abbracci" (love and kisses), usato tipicamente verso una persona cara/familiare.
Non confonderli: 73 è il saluto cordiale standard, 88 è affettuoso.

### Gergo comune e Codice Q
| Termine | Significato |
|---|---|
| QSO | collegamento/contatto radio |
| QRZ? | chi mi chiama? |
| QTH | località/posizione |
| QSL | conferma ricezione / cartolina di conferma |
| QRM | interferenza causata dall'uomo (altre stazioni) |
| QRN | disturbo atmosferico/statico (rumore naturale) |
| QSB | evanescenza del segnale (fading) |
| QSY | cambio frequenza |
| QRP / QRO | bassa potenza / alta potenza |
| QRT / QRV | cesso la trasmissione / sono pronto |
| OM / YL / XYL | radioamatore (Old Man) / operatrice o giovane donna (Young Lady) / moglie del radioamatore (eX-Young Lady) |
| rapporto RST | Readability 1-5, Strength 1-9, Tone 1-9 (il Tone si usa solo in CW; in fonia si dà solo RS) |
| Roger / Copiato | ricevuto e compreso |
| break / break-in | richiesta di inserimento nel QSO |

### Formule utili
- **Dipolo a mezz'onda** (lunghezza totale, m): L ≈ **142,5 / f(MHz)** (fattore di velocità ~0,95 incluso).
- **Verticale a quarto d'onda** (m): L ≈ **71,25 / f(MHz)**.
- **Lunghezza d'onda nel vuoto** (m): λ = **300 / f(MHz)**.
- **Conversioni dB ↔ potenza**: +3 dB ≈ ×2 della potenza; +10 dB = ×10; +6 dB ≈ ×4; +20 dB = ×100. (Es.: da 5 W a 50 W = +10 dB; da 100 W a 400 W = +6 dB.)
- **dBm**: 0 dBm = 1 mW; 30 dBm = 1 W; 60 dBm = 1 kW.

### Normativa italiana (cenni)
- Autorità competente: **MIMIT** (ex MISE) per autorizzazioni, nominativi e uso dello spettro.
- Limiti di potenza (potenza media all'uscita dell'apparato), come da quadro autorizzatorio vigente: tipicamente fino a **500 W** per i titolari di patente/autorizzazione di classe piena (con possibili autorizzazioni speciali fino a 1 kW per attività particolari), **10 W** per le autorizzazioni di classe ridotta/principianti. *I valori e le condizioni esatte vanno verificati sulla normativa MIMIT aggiornata e sull'autorizzazione individuale.*
- Va sempre usata la **minima potenza necessaria**.

### Breve storia
- **1895**: Guglielmo Marconi realizza le prime trasmissioni radio sperimentali a distanza.
- **1925** (Parigi): fondazione della **IARU** (International Amateur Radio Union).
- **1927** (Conferenza Radiotelegrafica Internazionale, Washington): regolamentazione internazionale e assegnazione dei blocchi di prefissi; all'Italia spettano i prefissi con lettera iniziale **I**.
- **1927**: nasce l'**ARI** (Associazione Radioamatori Italiani), tuttora società nazionale aderente alla IARU per l'Italia.
- Prefissi italiani tipici: **I, IZ, IW, IK, IU, IO/IQ** (speciali/club), ecc.; il nominativo si chiama *call sign*.

### Glossario essenziale
- **DX**: collegamento a lunga distanza (DX = distante).
- **Pile-up**: molte stazioni che chiamano contemporaneamente una stazione rara/ricercata.
- **Split**: trasmettere e ricevere su frequenze diverse (tipico nelle DXpedition).
- **Contest**: gara radioamatoriale.
- **Ragchew**: chiacchierata informale e prolungata.
- **Elmer**: radioamatore esperto che fa da mentore ai principianti.
- **Eyeball QSO**: incontro di persona tra radioamatori.
- **DXpedition**: spedizione per attivare un'entità rara.
- **APRS**: sistema di posizionamento/telemetria via packet radio.

Per dati ufficiali e aggiornati: **MIMIT** (autorizzazioni, nominativi, frequenze), **ARI** (ari.it), **IARU R1** (band plan, iaru-r1.org), **AMSAT** (satelliti radioamatoriali).

## Prima installazione della stazione: posto, alimentazione, coassiale e connettori

### Scelta del posto
Collocate la stazione vicino a una parete esterna per accorciare la discesa d'antenna. Prevedete un piano stabile, ventilazione per ricetrasmettitore e alimentatore, e una presa di terra dedicata. Tenete il PC e l'alimentatore switching almeno 50-80 cm dal RTX per ridurre il rumore (QRM). Lasciate spazio dietro per i connettori senza piegare i cavi a meno di 5x il loro diametro.

### Alimentazione 12V / PSU
Un RTX HF da 100 W assorbe circa 20-22 A in trasmissione: scegliete un alimentatore da almeno 25-30 A continui (non di picco). Tensione tipica 13,8 V. Preferite alimentatori lineari o switching con buona schermatura. Usate cavo rosso/nero da almeno 4 mm² (AWG 12) per correnti fino a 25 A, e 6 mm² oltre. Inserite un fusibile su entrambi i poli vicino all'alimentatore (es. 30 A). Rispettate la polarità: rosso = +, nero = -. Errore comune: cavi sottili che causano cadute di tensione e protezione ALC/SWR anomala.

### Cablaggio coassiale
Per HF usate RG-213 o RG-8 (basse perdite); per tratte corte o portatile RG-58. Per VHF/UHF preferite cavi a bassa perdita tipo Aircell 7 o Ecoflex 10. Esempio: 30 m di RG-58 a 145 MHz perdono oltre 6 dB (più di metà potenza!), mentre Ecoflex 10 perde circa 2 dB. Sigillate le giunzioni esterne con nastro autoagglomerante + nastro PVC. Non schiacciate né piegate stretto il coassiale.

### Connettori PL259 (UHF) e N
PL259 fino a 150 MHz; connettore N (impermeabile, 50 ohm) per UHF/SHF e uso esterno. 

Saldatura del PL259: spelate la guaina 18-20 mm, sfilate la calza, spelate il dielettrico 5 mm. Avvitate il corpo sul cavo, saldate il conduttore centrale al pin e saldate la calza attraverso i 4 fori laterali con saldatore da almeno 60-80 W. Errore tipico: surriscaldare e fondere il dielettrico, causando corto.

Crimpatura (N o PL259 crimp): usate la pinza con esagono corretto per il cavo, infilate la ghiera prima, crimpate centrale e poi corpo. Verificate sempre con tester continuità centrale e isolamento centrale-calza.

### Errori da evitare
- Non alimentare prima di aver verificato la polarità.
- Non trasmettere senza antenna o carico fittizio.
- Misurate sempre il ROS (SWR) al primo collegamento: deve essere sotto 2:1.

## Troubleshooting della stazione: ricerca guasti passo-passo

Procedi sempre **dal semplice al complesso** e **isola un sottosistema alla volta** (alimentazione → RTX → cavo → antenna). Tieni a portata di mano un multimetro, un carico fittizio (dummy load) 50 Ω, un ROSmetro/wattmetro e un ricetrasmettitore di scorta o portatile per i confronti.

**Niente RX (non si sente nulla)**
1. Verifica volume, squelch, RF-gain, attenuatore e che non sia attivo MUTE o un filtro stretto.
2. Controlla che antenna/preamplificatore esterno siano alimentati e che lo splitter RX/TX sia in posizione giusta.
3. Tocca il puntale dell'antenna: se senti un fruscio/ronzio, il front-end vive. Niente rumore di fondo = problema in RX o cavo aperto.

**Niente TX (non emette)**
1. Riduci potenza a 5 W e prova su carico fittizio: se eroga, il guasto è nell'antenna/cavo.
2. Controlla PTT, microfono, modo (USB/LSB/FM corretti per la banda), funzione VOX/SEND e che il TX non sia in TX-inhibit.
3. Verifica blocco da ALC o protezione SWR: molti apparati riducono a zero la potenza con ROS > 3:1.

**ROS alto**
- ROS accettabile ≤ 1.5:1; intervieni oltre 2:1; sopra 3:1 l'apparato taglia potenza.
- Misura il ROS **al ricetrasmettitore** e poi all'antenna: se a TX su dummy load il ROS è 1:1, il problema è oltre (cavo/connettori/antenna).
- Cause tipiche: connettore PL ossidato o saldato male, cavo entrato in acqua, antenna fuori risonanza, radiali/piano di massa assenti. Riaccorcia/allunga l'antenna per centrare la frequenza.

**Segnale debole (ti ricevono male)**
- Confronta potenza erogata col wattmetro; controlla ALC e microfono gain.
- Cavo coassiale degradato: RG-58 a 28 MHz su 30 m può perdere oltre 3 dB. Misura la perdita o sostituiscilo con RG-213/Aircell.
- Cattiva messa a terra o connessioni intermittenti.

**Alimentatore che cade in TX**
- In TX a piena potenza un RTX da 100 W assorbe **20-22 A a 13.8 V**: usa un alimentatore da almeno 25-30 A.
- Tensione che crolla sotto 11 V = alimentatore sottodimensionato o cavi DC sottili/lunghi. Usa cavi ≥ 4 mm² e fusibili adeguati.

**Errori da evitare**: trasmettere senza carico o antenna; usare un solo strumento senza confronto; cambiare più cose insieme; ignorare i connettori (causa nº1 dei guasti); stringere troppo i PL danneggiando il dielettrico.

## Errori comuni dei principianti

### 1. Trasmettere senza ascoltare
L'errore più frequente. Prima di chiamare:
- **Ascolta almeno 15-30 secondi** sulla frequenza.
- Chiedi **"È libera la frequenza? IZxxxx"** (in CW: `QRL?`) due volte prima di trasmettere.
- Ricorda che potresti sentire solo metà di un QSO: l'altra stazione può essere fuori dalla tua propagazione.
- Mai chiamare un DX a raffica ("tail-ending") sopra altri: causa solo confusione.

### 2. Split sbagliato
Quando un DX lavora in **split** (es. annuncia "up 5"), trasmette su una frequenza e ascolta più in alto/basso.
- Errore classico: chiamarlo sulla **sua** frequenza di trasmissione. Lì non ti sente e disturbi tutti.
- Procedura corretta: VFO-A sulla frequenza del DX (ricezione), VFO-B spostato di +5 kHz per la tua trasmissione.
- "Up 5" significa **+5 kHz**, non +500 Hz. Verifica sempre dove il DX sta effettivamente pescando le stazioni prima di chiamare.

### 3. Overdrive e splatter del microfono
Parlare troppo forte o con guadagno mic eccessivo genera **splatter**: armoniche che invadono ±3-10 kHz disturbando i vicini di banda.
- Sintomo: ti dicono "audio distorto" o "stai allargando".
- Tieni il microfono a **5-8 cm** dalla bocca, parla con voce normale.

### 4. Regolazione ALC e mic gain
Procedura corretta in SSB:
1. Regola il **mic gain** finché, parlando normalmente, l'ALC tocca solo i picchi vocali.
2. L'indicatore **ALC deve restare nella zona consentita** (tipicamente fino a metà scala / ~5-10 unità sul bargraph del tuo apparato). Se l'ALC è costantemente "spalmato" al massimo, sei in overdrive.
3. La potenza di picco deve raggiungere il valore nominale (es. 100 W) **solo sui picchi**, non in modo continuo.

**Regola d'oro:** più mic gain ≠ più segnale utile. Oltre la soglia ALC ottieni solo distorsione e splatter, non maggiore portata.

### 5. Compressione (processore di fonia)
La compressione aumenta la potenza media e l'intelligibilità nel DX/pile-up.
- Imposta **5-10 dB** di compressione, **massimo 10-15 dB**.
- Errore: spingere a 20+ dB pensando di "urlare più forte" — risultato: audio gracchiante e splatter.
- Verifica sempre con un OM di fiducia o registrando il tuo audio monitor.

**Da evitare:** chiamare a casaccio nelle DX-pedition, lasciare il VOX troppo sensibile (chiavetta su rumori ambientali), e non identificarsi ogni 10 minuti come richiede la normativa.

## Regolazione e taratura pratica dell'antenna

### Misura con NanoVNA / analizzatore

1. **Calibrazione obbligatoria** (OPEN-SHORT-LOAD) sul connettore o all'estremità del cavo che userai. Senza calibrazione i dati non valgono nulla.
2. Imposta lo span sulla banda: es. 40 m → start 6.900, stop 7.300 MHz.
3. Leggi il **dip di risonanza**: il minimo della curva SWR (o di |S11| in dB). È lì che l'antenna risuona.
4. Annota frequenza del dip e valore minimo di SWR.

### Accorciare o allungare

Regola d'oro: **risonanza troppo bassa = elemento troppo lungo → accorcia. Risonanza troppo alta = elemento troppo corto → allunga.**

Formula pratica per stimare il taglio su un dipolo/filare:

ΔL (m) ≈ L × (f_attuale − f_desiderata) / f_desiderata

Esempio: dipolo 40 m, dip a 6.950 MHz, voglio 7.100. Lunghezza totale ~20 m → ΔL ≈ 20 × (6950−7100)/7100 ≈ −0,42 m. Accorcio ~21 cm **per lato** (metà per braccio). Taglia poco e rimisura: meglio due tagli da 10 cm che uno da 40.

Su verticali/stilo si agisce su stub o spuntando la punta; su Yagi si regola il radiatore, non gli elementi parassiti.

### Valori di riferimento

- SWR **≤ 1,5:1** ottimo, ≤ 2:1 accettabile (limite di molti finali a stato solido, che riducono potenza oltre).
- Larghezza di banda tipica di un dipolo HF: circa 2-3% della frequenza.
- Se l'SWR resta alto su tutta la banda anche spostando il dip → problema di **impedenza/altezza/balun**, non di lunghezza.

### Errori da evitare

- Misurare senza calibrare o con un cavo diverso da quello operativo.
- Tarare con l'antenna a terra o vicino a oggetti: misura sempre **in posizione definitiva**.
- Confondere SWR basso con antenna efficiente (un carico fittizio ha SWR 1:1 ma non irradia).
- Trasmettere a piena potenza dentro il NanoVNA: lo distrugge.

### ATU interno vs esterno

L'accordatore **non tara l'antenna**: maschera l'SWR verso il TX adattando l'impedenza.

- **ATU interno** (radio): tipicamente accorda fino a ~3:1, perfetto per piccoli aggiustamenti tra porzioni di banda.
- **ATU esterno** (anche al palo): gestisce 10:1 e oltre, ideale per antenne multibanda/filari lunghi. Posizionato vicino all'antenna riduce le perdite sul cavo disadattato.

Prima accorda l'antenna fisicamente (dip nella banda), poi usa l'ATU solo per il fine-tuning.

## Autocostruzione pratica: dipoli, verticali, balun/unun, choke, radials, attenuatori e dummy load

### Dipolo a mezz'onda
Lunghezza totale: **L (m) = 142,5 / f(MHz)**, ciascun braccio metà. Il fattore 142,5 (anziché 150) tiene conto del velocity factor del filo. Esempio per 7,1 MHz: L = 20,07 m, due bracci da 10,03 m. Usare filo di rame da 1,5–2,5 mm². **Tagliare sempre 3–5 cm più lungo per lato** e accorciare in fase di taratura, controllando il minimo SWR con analizzatore (RigExpert/NanoVNA). Se la risonanza è troppo bassa, accorciare; troppo alta, allungare. Altezza minima utile: λ/4 dal suolo.

### Verticale 1/4 d'onda con radials
Lunghezza elemento: **L (m) = 71,5 / f(MHz)**. Serve un piano di terra: minimo **4 radials elevati** sintonizzati (stessa lunghezza dell'elemento), oppure **16–32+ radials a terra** lunghi 0,15–0,2 λ (la quantità conta più della lunghezza precisa, per terra non vanno tagliati a risonanza). Errore tipico: pochi radials a terra → rendimento pessimo e SWR ingannevolmente basso per le perdite resistive.

### Balun e unun
- **Balun 1:1 current (choke)**: per alimentare un dipolo (carico bilanciato) con coassiale (sbilanciato). Realizzabile avvolgendo il coassiale su toroide **FT240-43**: in HF tipicamente **10–12 spire**. Blocca le correnti di guaina.
- **Balun 4:1**: per antenne con impedenza ~200 Ω (es. folded dipole). Voltage o Guanella su FT240-43.
- **Unun 9:1**: per long-wire/end-fed, da ~450 Ω a 50 Ω. Avvolgimento trifilare su toroide.

### Current choke (line isolator)
Da mettere all'alimentazione dell'antenna e/o all'uscita TX per eliminare RF sulla calza ("RF in shack", bruciori al microfono). Soluzione semplice ed efficace: **7–10 spire di coassiale su mix 31 o 43**.

### Dummy load (carico fittizio)
Resistenza **non induttiva da 50 Ω**. Per QRP: resistenze a film metallico in parallelo (es. 10×510 Ω = 51 Ω). Per potenze maggiori, resistenza tipo "Caddock"/MFJ in bagno d'olio minerale. Controllare SWR ≈ 1:1 su tutta la HF. **Mai usare resistenze a filo avvolto** (induttive).

### Attenuatori
A pi-greco o a T con resistenze non induttive. Esempi a 50 Ω: **3 dB** → serie 8,5 Ω, shunt 142 Ω; **6 dB** → serie 16 Ω, shunt 67 Ω; **10 dB** → serie 26 Ω, shunt 35 Ω; **20 dB** → serie 41 Ω, shunt 10 Ω. Utile per misure e per proteggere ricevitori SDR.

**Errori comuni**: dimenticare il velocity factor, mancanza di choke, radials insufficienti, resistenze induttive nel dummy load, taratura senza strumento.

## RFI domestica e convivenza: convivere con TV, PLC, router e impianti audio

L'interferenza a radiofrequenza (RFI) verso gli apparati domestici nasce quasi sempre da **correnti di modo comune** sul cavo coassiale, sui cordoni di alimentazione e sui cavi di segnale, non dalla potenza in sé. Prima di tutto: documenta il problema (banda, orario, apparato colpito) e verifica se l'interferenza sparisce abbassando la potenza o cambiando banda. Questo distingue un sovraccarico (front-end del TV) da un'irradiazione diretta.

### Diagnosi rapida
- **TV/decoder DVB-T2**: disturbo su 470-694 MHz tipicamente causato da armoniche o da intermodulazione nell'amplificatore d'antenna. Spesso il colpevole è proprio il preamplificatore TV mal filtrato, non il tuo TX.
- **Router/Wi-Fi e PLC (powerline)**: i PLC su 2-86 MHz sono notori disturbatori QRM in HF e ne ricevono altrettanto. Soluzione concreta: elimina i PLC e passa a cavo ethernet o fibra. Nessun filtro li rende davvero compatibili con l'HF.
- **Audio (ronzio/voce in altoparlanti)**: rettificazione RF negli stadi d'ingresso.

### Soluzioni efficaci
1. **Ferriti (clamp on)**. Usa materiale **mix 31** per 1-30 MHz e **mix 43** per 30-300 MHz. Non un solo anello: avvolgi il cavo 5-7 spire attraverso un toroide FT240-31 vicino al connettore dell'apparato disturbato. Un singolo clip da supermercato (spesso mix 61) in HF è quasi inutile.
2. **Choke di modo comune (current balun 1:1)** all'alimentazione dell'antenna: 10-12 spire di coassiale su FT240-31 o 18 perline su RG-303.
3. **Filtri di rete**: filtro EMI sulla 230 V dell'apparato sensibile e del TX. Per il TV, un filtro passa-alto coassiale che attenui sotto i 40 MHz protegge il front-end dalla tua HF.
4. **Ground loop**: il ronzio a 50/100 Hz nell'audio o le righe sullo schermo derivano da anelli di massa. Stabilisci un **single-point ground**, collega le masse di stazione a una barra comune e non duplicare i percorsi di terra. Per l'audio, un **isolatore galvanico/trasformatore di linea 1:1** sui segnali sbilanciati risolve definitivamente.

### Errori da evitare
- Non aggiungere terre multiple sperando di "scaricare meglio": crei più ground loop.
- Non confondere RFI in uscita (disturbi tuoi) con RFI in ingresso (PLC/switching).
- Non usare la ferrite sbagliata: mix 61 in HF non assorbe nulla.
- Conserva sempre prova scritta degli interventi: in caso di contenzioso col vicino, dimostra di aver applicato le buone pratiche EMC.

## Configurazione e logging software: ADIF, eQSL/LoTW/QRZ, CAT control, audio USB e calibrazione livelli

### CAT control
Il CAT (Computer Aided Transceiver) sincronizza frequenza e modo tra radio e software. In WSJT-X o Hamlib (rigctld), seleziona il modello esatto della radio, la porta seriale corretta (su Windows controlla Gestione Dispositivi, es. COM5) e il baud rate dichiarato nel manuale (tipicamente 4800, 9600, 19200, 38400 o 115200). Per gli apparati moderni USB usa spesso PTT via CAT; per radio con CAT su una porta e PTT su un'altra imposta PTT su RTS o DTR. Premi sempre "Test CAT" (deve diventare verde) e "Test PTT" prima di operare. Errore comune: due programmi che aprono la stessa COM contemporaneamente (porta occupata) — usa un solo client o un serial splitter.

### Audio USB e calibrazione livelli
Imposta il dispositivo audio USB della radio come Input e Output in WSJT-X. Regola il livello di ingresso così che la barra del rumore di fondo, ad antenna collegata, resti tra 30 e 50 dB (verde). Sotto 20 dB o sopra 70 dB perdi sensibilità. In trasmissione, parti col cursore Pwr al minimo e alza finché la potenza erogata raggiunge circa l'80-90% del massimo, poi riduci leggermente fino a non vedere più ALC (deve restare a zero o appena visibile). Errore grave: spingere l'audio fino a generare ALC, che produce splatter e segnali distorti, segnalati come "non decodificabili" o larghi sul waterfall.

### Sincronizzazione oraria
FT8 richiede orologio entro ±1 secondo (slot da 15 s). Usa Meinberg NTP o BktTimeSync su Windows; se i tuoi DT nei decode superano ±0,5 s, il PC è desincronizzato.

### ADIF e QSL elettroniche
Ogni QSO viene salvato in formato ADIF (.adi). Carica il log su:
- LoTW: serve certificato TQSL (tqsl.exe), firma il file .adi e ottieni un .tq8 da inviare. Conferme automatiche per i match.
- eQSL.cc: upload diretto del .adi, conferme immediate.
- QRZ.com Logbook: upload .adi o sincronizzazione via API key.

Consiglio: usa un logger unico (es. Log4OM, N1MM, ACLog) come fonte e abilita l'export/upload automatico verso LoTW/eQSL/QRZ per evitare doppioni e disallineamenti. Verifica sempre che banda, modo (FT8, non DATA generico), data UTC e RST siano corretti prima dell'upload, perché LoTW confronta questi campi per validare il match.

## Operatività portatile ed emergenza

### SOTA e POTA
- **SOTA** (Summits On The Air): attiva una cima, servono almeno **4 QSO validi** per assegnare i punti. Apparato e antenna devono stare entro la **activation zone** (25 m di dislivello sotto la vetta). Niente alimentazione da rete o veicolo.
- **POTA** (Parks On The Air): per validare l'attivazione bastano **10 QSO**; spotting su pota.app o tramite APRS/RBN.
- Frequenze QRP "di chiamata": **7.030, 14.060, 10.116, 21.060, 28.060 MHz** in CW; SSB porzioni QRP **7.090, 14.285, 21.285 MHz**.

### QRP
- Limite QRP: **5 W in CW/dati, 10 W PEP in SSB**. Con buona antenna e CW si fanno tranquillamente collegamenti intercontinentali.
- Modi efficienti: **CW e FT8** (FT8 lavora a -24 dB S/N). In SSB privilegia bande aperte e propagazione, non potenza.

### Antenne da campo
- **EFHW** (end-fed half-wave, unun 49:1): mezz'onda risonante, multibanda (40-20-15-10 m), ottima con un singolo palo da 6 m.
- **Dipolo lineare** o **inverted-V** (apex 7-9 m): semplice, efficiente, richiede balun 1:1.
- **Verticale con radiali**: utile vicino al mare per DX; servono **almeno 4 radiali**.
- Porta sempre **corda da paracadute, picchetti e un palo telescopico in fibra**. Mai tirare un filo su linee elettriche.

### Batterie LiFePO4
- Cella nominale **3,2 V**; pacco 4S = **12,8 V nominali (range 10,0-14,6 V)**. Per radio HF/QRP tipico **12,8 V 6-12 Ah**.
- Vantaggi: ~**2000-3000 cicli**, peso ridotto, scarica piatta.
- Usa **sempre un BMS** e un caricabatteria dedicato LiFePO4 (CC/CV, 14,2-14,6 V). Non caricare sotto **0 °C** (danno permanente). Errore frequente: usare un caricatore al piombo non compatibile.

### Pannelli solari
- Pannello **50-100 W** + **regolatore MPPT** (più efficiente del PWM, +15-30%). Stima: 100 W reali ~5-6 A in pieno sole.
- Tieni il pannello **lontano dall'antenna**: gli inverter/regolatori PWM generano QRM.

### Sicurezza in mobile ed emergenza
- In auto fissa l'apparato; non usare il microfono guidando se la legge lo vieta.
- Emergenze: **parola "MAYDAY"** e frequenze di soccorso/coordinamento locali; in Italia coordinamento con **Protezione Civile / radioamatori volontari**. Frequenza di chiamata 2 m **145.500 MHz**, calling 40 m SSB **7.110 MHz** circa.
- Tieni una **scheda con i tuoi dati, frequenze e contatti**, una torcia, e batteria di riserva. Comunica chiaro: nominativo, posizione, natura dell'emergenza, ripeti.
