# [PSZT] Cats

### Autorzy
* Adamski Maciej
* Kubiszewski Szymon

### Jak użyć
* W pliku `main.cpp` ustawić interesujące nas parametry:
	* `Network({input, { hidden }, output})` - warstwy sieci
	* `learningRate` - funkcja `SetLearningRate()`. Domyślnie `0.1`
	* `epochs` - ilość epok w czasie uczenia
* Skompilować `make` lub `make all`
* Uruchomić `./pszt-cats`
* Usunąć pliki wykonywalne `make clean`