# Párhuzamos algoritmusok

Mindháromhoz fog tartozni egy-egy grafikon, ami összehasonlítja az időket a különböző számú szálak között a megadott adatmennyiségtől függően.

## Gyorsrendezés

Az első feladatban POSIX szálakkal fogom implementálni a gyorsrendezést.
* A szálak számát paraméterként lehet állítani. (A szimuláció sorban elvégzi a méréseket 1, 2, ..., p szál esetében.)
* A algoritmus rekurzívan van implementálva.
* Rekurzív hívásnál csak akkor indít új szálat, ha összesen kevesebb szál van, mint p.

## Lagrange interpoláció

A második feladatban OpenMP-vel fogom implementálni a Lagrange interpolációt.
* Kétdimenziós függvényeket interpolál.
* A függvény pontjai véletlenszerűen vannak generálva.
* A párhuzamosítás célja a Lagrange polinom meghatározásának hatékonyabbá tétele.

## Lineáris egyenletrendszer megoldás

A harmadik feladatban OpenMP-vel Gauss-Jordan módszerrel való lineáris egyenletrendszer megoldást fogom implementálni.
* Az egyenletrendszer elemei véletlenszerűen vannak generálva.
