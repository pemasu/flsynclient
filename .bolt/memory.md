# Project memory

## Product intent & audience

- Kosketuslevyn asetuksia hallinva ohjelma (touchpad settings tool).
- Käyttäjä on tekninen, työstää kevyttä C/C++-pohjaista työpöytäsovellusta Linuxissa.

## Brand personality & voice

- Viestintä suomeksi, ytimekäs ja tekninen.
- Suosii konkreettisia vaihtoehtoja ja perusteltuja suosituksia.

## Visual design & UX direction

- GUI rakennettu FLTK:lla: ikkunat, liukusäätimet, valikot, välilehdet, hiiritapahtumat.
- Ei laajempia UX- tai visuaalisia ohjeistuksia toistaiseossa päätelty.

## Decisions, constraints & rationale

- Koodi on käytännössä C-tyylistä mutta käännetään C++:lla; FLTK vaatii C++-käännöksen.
- FLTK valittu GUI-kirjastoksi: kevyt, yksi riippuvuus, koodi jo toimii.
- GUI-koodia arviolta ~1000 riviä FLTK:ta.
- Nopeusongelma (touchpad-asetusten toiminnassa) jo korjattu aiempien muutosten yhteydessä.
- Vaihtoehdot harkittu mutta hylätty toistaiseksi:
  - Xlib (puhdas C): ~2000–3000 riviä uutta koodia, paljon työtä, ei hyötyä.
  - GTK (puhdas C): eri ulkoasu, koko GUI kirjoitettava uudelleen.
- Päätös: pidetään FLTK; vaihto ei tuo konkreettista hyötyä toiminnallisuuteen.

## Open questions & assumptions

- Käyttäjä voi halutessaan palata aiheeseen ja pyytää Xlib-pohjaisen version suunnittelua.
- Ei tietoa tarkasta kohdejärjestelmästä tai jakelusta, oletettu Linux/X11.