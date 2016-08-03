int fibonacci(int n) {
  int f1 = 0;
  int f2 = 1;
  int fi = 0;

  if (n < 0) {
    return 0;
  }

  outputInt(0);
  outputString(", ");
  outputInt(1);

  if (n == 0 | n == 1) {
    return 1;
  }

  while (fi < n) {
    fi = f1 + f2;
    f1 = f2;
    f2 = fi;
    outputString(", ");
    outputInt(fi);
  }

  return fi;
}

int main() {
  int n;
  inputInt(n);

  int fib = fibonacci(n);
  #do something with fib
  return 0;
}
