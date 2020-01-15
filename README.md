# Blockchain1 (Hash generatorius)
Vilniaus universitetas

Pirmoji Blockchain užduotis

## Užduoties formuluotė

Sukurti maišos (*hash*) funkciją (*hash* kodų generatorių), kuris pasižymėtų šiais *hash* funkcijoms keliamais reikalavimais:

1. Maišos funkcijos įėjimas (angl. *input*) gali būti bet kokio dydžio simbolių eilutė (angl. *string*).
2. Maišos funkcijos išėjimas (angl. *output*) visuomet yra to paties fiksuoto dydžio rezultatas.
3. Maišos funkcija yra deterministinė, t. y., tam pačiam įvedimui (angl. *input*'ui) išvedimas (angl. *output*'as) visuomet yra tas pats.
4. Maišos funkcijos reikšmė/kodas (hash‘as) bet kokiai input reikšmėi yra apskaičiuojamas nesunkiai - efektyviai.
5. Iš funkcijos rezultato (*output*'o) praktiškai neįmanoma atgaminti įvedimo (*input*'o).
6. Praktiškai neįmanoma surasti tokių dviejų skirtingų argumentų (*input*'ų), kad jiems gautume tą patį *hash*'ą, t. y.,: *m1 != m2*, bet *h(m1) = h(m2)*.
7. Bent minimaliai pakeitus įvedimą, pvz.vietoj "Lietuva" pateikus "lietuva", maišos funkcijos rezultatas-kodas turi skirtis iš esmės.

## Įdiegimas (Unix kompiuteryje)

- `git clone https://github.com/vikuliukas/Blockchain_1uzd.git`
- `cd Blockchain_1uzd`
- `make`
- `./main`

## Kaip naudotis?

- Pasirinkite, ar norite tekstą vesti ranka (įrašyti "0"), ar skaityti tekstą iš failo ("1");
- Jei pasirinkote nuskaityti tekstą iš failo:
  - Pasirinkite, ar kurti *hash* viso failo (įrašyti "0"), ar kiekvienos eilutės atskirai ("1");
  - Įveskite failo pavadinimą;

! Vienas failo *hash* bus atspausdintas ekrane.

! Daugiau nei vienas *hash* bus sukurtame *result.txt* faile.

## *Hash* algoritmas

```c++
void hashAlgorithm( hash &key )
{   
    std::string copy = key.getFixedIn();
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    std::u32string input32 = converter.from_bytes(copy);

    unsigned long long int sum[5] = {1};
    int part = 1;
    int index = 1;
    for(char32_t &character : input32)
    {
        if(part == 1)
        {
            sum[0] = (index + index) * sum[0] + character;
        }

        if(part == 2)
        {
            sum[1] = (index + index) * sum[1] + character;
        }

        if(part == 3)
        {
            sum[2] = (index + index) * sum[2] + character;
        }

        if(part == 4)
        {
            sum[3] = (index + index) * sum[3] + character;
            part = 0;
        }

        part++;
        index++;
    }

    std::string hexa[5] = {""};

    for(int i = 0; i < 4; i++)
    {
        hexa[i] = inHexa(sum[i]);

        while(hexa[i].length() < 16)
        {
            hexa[i] += "0";
        }
    }

    std::string basehash = hexa[0] + hexa[1] + hexa[2] + hexa[3];
    std::string hashadd = hashAdd(basehash, key);
    key.setOut(hashadd);
}
```

### *Hash* algoritmo savybės:
- Tekstas paverčiamas į Unicode;

! Prie teksto pridedama simbolių, jei jis per mažas, kad susidarytų 64 simbolių ilgio *hash*.

- Gautas unicode paverčiamas į šešioliktainės sistemos simbolius;
- Kiekvienas turimas *hash* simbolis dar pakeičiamas pagal funckiją:

```c++
std::string hashAdd( std::string &basehash, hash &key )
{

    std::string copy = key.getIn();
    std::wstring_convert<std::codecvt_utf8_utf16<char32_t>,char32_t> converter;
    std::u32string input32 = converter.from_bytes(copy);

    std::string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";

    for(unsigned int i = 0; i < basehash.size(); i++)
    {
        unsigned long tempor = basehash[i];
        tempor = tempor + i;

        while(tempor > alphabet.size())
        {
            tempor = tempor - alphabet.size();
        }

        basehash[i] = alphabet[tempor];
    }

    return basehash;
}
```

## Testai

### 1 testas

- Bent du failai būtų sudaryti tik iš vieno, tačiau skirtingo, simbolio.

*test1_1.txt*

```A```

Rezultatas
```
Algorithm took 0.0000475000 second(s) to complete.
ryTv76vvWb8DdB03b1gg5g98g9hIJlcLLNflonPRiHiTTpMSMlmmUwoOqWYQY3y6
```

*test1_2.txt*

```1```

Rezultatas
```
Algorithm took 0.0000455000 second(s) to complete.
TU7T0w6V7 aBdB03b1gg5g98g9hIJlcLLNflonPRiHiTTpMSMlmmUwoOqWYQY3y6
```
### 2 testas

- Bent du failai būtų sudaryti iš daug visiškai skirtingų simbolių (> 10000 simbolių).

*test2_1.txt*

```
Rooms oh fully taken by worse do. Points afraid but may end law lasted. Was out laughter raptures returned outweigh.
Luckily cheered colonel me do we attacks on highest enabled. Tried law yet style child. Bore of true of no be deal.
Frequently sufficient in be unaffected. The furnished she concluded depending procuring concealed. But why smiling
man her imagine married. Chiefly can man her out believe manners cottage colonel unknown. Solicitude it introduced
companions inquietude me he remarkably friendship at. My almost or horses period. Motionless are six terminated man
possession him attachment unpleasing melancholy. Sir smile arose one share. No abroad in easily relied an whence lovers
temper by. Looked wisdom common he an be giving length mr. 
```

Rezultatas

```
Algorithm took 0.0000925000 second(s) to complete.
2zs71W39 8YXYyyz2FC2866aHhHkcCIjkfMNgHINrIPTQqlrltOvxWOOWyp0ZyZy
```

*test2_2.txt*

```
Is we miles ready he might going. Own books built put civil fully blind fanny. Projection appearance at of admiration no.
As he totally cousins warrant besides ashamed do. Therefore by applauded acuteness supported affection it. Except had limits
county enough the figure former add. Do sang my he next mr soon. It merely waited do unable. It real sent your at. Amounted
all shy set why followed declared. Repeated of endeavor mr position kindness offering ignorant so up. Simplicity are melancholy
preference considered saw companions. Disposal on outweigh do speedily in on. Him ham although thoughts entirely drawings.
Acceptance unreserved old admiration projection nay yet him. Lasted am so before on esteem vanity oh.
```

Rezultatas

```
Algorithm took 0.0000873000 second(s) to complete.
2s186 59Y7wY YaeFc4Efh8GhfIBhhEckfdePPmgnpISRrsqslvmooVVpzW0xrTU
```

### 3 testas

- Bent du failai būtų sudaryti iš daug simbolių ir skirtųsi vienas nuo kito tik vienu simboliu.
- Failų skirtumas - antrame faile nėra gale taško.

*test3_1.txt*

```
Ladyship it daughter securing procured or am moreover mr. Put sir she exercise vicinity cheerful
wondered. Continual say suspicion provision you neglected sir curiosity unwilling. Simplicity end
themselves increasing led day sympathize yet. General windows effects not are drawing man garrets.
Common indeed garden you his ladies out yet. Preference imprudence contrasted to remarkably in on.
Taken now you him trees tears any. Her object giving end sister except oppose. Mr do raising article
general norland my hastily. Its companions say uncommonly pianoforte favourable. Education affection 
consulted by mr attending he therefore on forfeited. High way more far feet kind evil play led. Sometimes
furnished collected add for resources attention. Norland an by minuter enquire it general on towards forming.
Adapted mrs totally company two yet conduct men.
```

Rezultatas

```
Algorithm took 0.0000962000 second(s) to complete.
T576uvvvY9ayBy2zzDFe656gBGjiLkIJnFdlmMPqpShsSLlqvNnomouOPYWRyYZU
```

*test3_2.txt*

```
Ladyship it daughter securing procured or am moreover mr. Put sir she exercise vicinity cheerful
wondered. Continual say suspicion provision you neglected sir curiosity unwilling. Simplicity end
themselves increasing led day sympathize yet. General windows effects not are drawing man garrets.
Common indeed garden you his ladies out yet. Preference imprudence contrasted to remarkably in on.
Taken now you him trees tears any. Her object giving end sister except oppose. Mr do raising article
general norland my hastily. Its companions say uncommonly pianoforte favourable. Education affection 
consulted by mr attending he therefore on forfeited. High way more far feet kind evil play led. Sometimes
furnished collected add for resources attention. Norland an by minuter enquire it general on towards forming.
Adapted mrs totally company two yet conduct men
```

Rezultatas

```
Algorithm took 0.0001245000 second(s) to complete.
T576uvvvY9ayBy2zzDFe656gBGjiLkIJnFdlmMPqpShsSLlqmMvMXxoPQzY2sZZy
```

### 4 testas

- Tuščias failas Ir išveskite output'us. Nepriklausomai nuo Input'o, Output'ai turi būti vienodo dydžio.
Tuščias failas - *test4.txt*

Rezultatas

```
Algorithm took 0.0000447000 second(s) to complete.
yT53t9vaW7C8dB03b1gg5g98g9hIJlcLLNflonPRiHiTTpMSMlmmUwoOqWYQY3y6
```

### 5 testas

- Ištirkite Jūsų sukurtos hash funkcijos efektyvumą: tuo tikslu suhash'uokite kiekvieną eilutę iš konstitucija.txt failo.

Rezultatas
```
y2uTW9av6YxBZaC20dD77eeGaB KDLMiemkMGgOpqJPkPjRKMUmVxoxWyq0Z2T5t
t1ztV33 XCcxBd2E1D4dg96gIH jikDLdnLNmGOPpnJQSKtSsrsmXtXoP0yxssy6
3u5T097VaWwcyZ03FDcH4dfffBkiKCKLMjGepgPGrrQJPjrUNvSMoonwYxyRs3yZ
ZSz0uuaX8xBabY03zeCfG97f  gBLCkiNDMoFfhPNqiTQKMSutWoTvVyYWYQY3y6
SuuuVw63v97a0B03e2g3F7GG 9hIJlcLmldGPHqmPOsPTpMSlLsUUwoOqWYQY3y6
226VWwXXax Z ae31G6gFFFfhbHjlJmNMdKFglfNpJsrrKsRrrVOVWQpyZYR01t6
y5Z483X3WBYx0y031CFc54  i8hIJlcLEKNnPgNNHIqSQpMSUsnXtPvuzrQS1SyZ
tsU8VVXVB8x88aB0zceg5ei78bCHDdMJlfdmmPpoJnJITkkTsSVOovYPXq121206
04z351 949cCcCyzc04ffgghHiChHKddmNLgLfNIgRrqKqLmTTToWxpZYpWSr20y
tSt6v3a69 6z8yC3E1gGH9egJji KdbmenlgehNoqQOsiJKUrNWOtxUWZP00rrsS
...
Algorithm took 0.0076054000 second(s) to complete.
```

### 6 testas

- Susigeneruokite bent 1000 000 atsitiktinių simbolių eilučių (string'ų) porų, pvz.: (asdfg, hijkl) apsiribojant iki 5 simbolių eilučių ilgiu ir patikrinkite, kad visais atvejais gautieji porų hash'ai nesutampa.

*test6.txt*

```
bTAKR
ckVEg
SuveE
qyaIq
CIuVa
fpVgD
HUktM
hEtnN
RJxpA
jIvNi
...
```

Rezultatas

```
4T15W7WX5xCYYB03fGfff6gIf9hIJlcLnFmonOMGIPpjPpMSTvmmUwoOqWYQY3y6
546UWV5v75YXYB03E51e895JG9hIJlcLDdneFhHGHniPPpMSMTUmUwoOqWYQY3y6
S61TU574aBBZYB0344cdHHff99hIJlcLDNKPGhmQHnSoPlrqrnnmUwoOqWYQY3y6
ZSzU1u7WWC8 cB03f3fHHdf8g9hIJlcLMjmLFgngqPSqPlrqrSTmUwoOqWYQY3y6
0stU075xW8xDaz2aD03E3h7779hIJlcLndkOGNgPhpPrjpMSSuTmUwoOqWYQY3y6
T6t85494xBaD9B03b46c44F7G9hIJlcLDdneFhHGHniPPpMSSuTmUwoOqWYQY3y6
Utt779Vx66 70B03cd42eEh7I9hIJlcLLfnoHPPmQPqpjpMSrVVmUwoOqWYQY3y6
551u1833Y7YXaB03fcGe5figf9hIJlcLDednflGOQQrITpMSMWWmUwoOqWYQY3y6
z602u4aW88xabB03b46c44F7G9hIJlcLekNkeHpRHhSSjpMSrnnmUwoOqWYQY3y6
U4356U 8v6Z79B03zfF6e59gh9hIJlcLDEoLNlOQNhojjpMSrvWmUwoOqWYQY3y6
...
Algorithm took 7.1330931000 second(s) to complete.
```

### 7 testas

- Susigeneruokite bent 100 000 atsitiktinių simbolių eilučių (string'ų) porų, , pvz.: (asdfg, bsdfg) tokių kad skirtųsi jos tik vienu simboliu ir apsiribojant iki 5 simbolių eilučių ilgiu.

*test7.txt*

```
QHcqZ
Q!cqZ
GiJRv
GiJ!v
pGssj
pGs!j
veKQX
v!KQX
HlnQu
Hln!u
...
```

Rezultatas

```
y0212w5a6w99YB03zdF3dH ag9hIJlcLDfFLfMQHnHpqPpMSvMMtWOnQvxpx2Y5y
y0212w5a6w99YB0340C7GFG979hIJlcLDfFLfMQHnHpqPpMSvMMtWOnQvxpx2Y5y
s5T05UV45aXDYB03E51e895JG9hIJlcLKOdPPQNhHojsjpMSslTmUwoOqWYQY3y6
s5T05UV45aXDYB03E51e895JG9hIJlcLKOdPPQNhHojsjpMSMlmmUwoOqWYQY3y6
43u5358 6bZCaz2aCG5FgG8GH9hIJlcLDNKPGhmQHnSoPlrqltWmUwoOqWYQY3y6
43u5358 6bZCaz2aCG5FgG8GH9hIJlcLDNKPGhmQHnSoPlrqMlmmUwoOqWYQY3y6
yU7735a87YC7YB03FEG6gg JI9hIJlcLLFNMooIoNrKrPpMStmmmUwoOqWYQY3y6
yU7735a87YC7YB0340C7GFG979hIJlcLLFNMooIoNrKrPpMStmmmUwoOqWYQY3y6
UzZ27664YC cZB0325dF7gF8B9hIJlcLlLeGHQmNhIiRjpMStmmmUwoOqWYQY3y6
UzZ27664YC cZB0325dF7gF8B9hIJlcLlLeGHQmNhIiRjpMSMlmmUwoOqWYQY3y6
...
Algorithm took 6.8701638000 second(s) to complete.
```