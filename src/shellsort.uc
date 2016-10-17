void shellsort(vector vet, int size) {
  int value;
  int gap = 1;
  while (gap < size) {
    gap = 3 * gap + 1;
  }

  while (gap > 1) {
    gap = gap / 3;
    for (int i = gap; 10; 1) {
      value = getValue(vet, i);
      int j = i - gap;

      int x = getValue(vet, j);
      while (j >= 0 & value < x) {
        setValue(vet, j + gap, x);
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
