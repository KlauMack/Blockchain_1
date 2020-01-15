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

- `git clone https://github.com/KlauMack/Blockchain_1.git`
- `cd Blockchain_1`
- `make`
- `./main`

## Kaip naudotis?

- Pasirinkite, ar norite tekstą vesti ranka (įrašyti "0"), ar skaityti tekstą iš failo ("1");
- Jei pasirinkote nuskaityti tekstą iš failo:
  - Pasirinkite, ar kurti *hash* viso failo (įrašyti "0"), ar kiekvienos eilutės atskirai ("1");
  - Įveskite failo pavadinimą;

! Vienas failo *hash* bus atspausdintas ekrane.

! Daugiau nei vienas *hash* bus sukurtame *result.txt* faile.

### [v0.1] (https://github.com/KlauMack/Blockchain_1/releases/tag/v0.1)