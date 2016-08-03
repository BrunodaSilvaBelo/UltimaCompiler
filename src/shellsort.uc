void shellsort(vector int vet, int size) {
  int value;
  int gap = 1;
  while (gap < size) {
    gap = 3 * gap + 1;
  }

  while (gap > 1) {
    gap = gap / 3;
    for (int i = gap; i < size; i = i + 1) {
      value = getValue(vet, i);
      int j = i - gap;

      while (j >= 0 & value < getValue(vet, j)) {
        setValue(vet, j + gap, getValue(vet, j));
        j = j - gap;
      }

      setValue(vet, j + gap, value);
    }
  }
}

int main() {
  int size;
  inputInt(size);

  vector int vet : size;
  for (int i = 0; size; 1) {
    int x;
    inputInt(x);
    addInt(vet, x);
  }

  shellsort(vet, size);
  #do something with vet

  return 0;
}