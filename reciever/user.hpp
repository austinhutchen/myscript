char array[8];
typedef char *iterator;
iterator array_begin(char a[]) { return &a[0]; }
iterator array_end(char a[], int n) { return &a[n]; }
iterator array_next(iterator i) { return ++i; }

struct user {
  char buf;
  char **str;
  int size;
  user() {
    buf = size = 0;
    str = 0x0;
  }
  char getbuf() {
    str += buf;
    this->size += 1;
    return buf;
  }
  void refresh(char (*f)(void) ) { buf = f(); }
  void prnt() {
    int i = 0;
    iterator it = array_begin(*this->str);
    iterator end = array_end(*this->str, 15);
    for (; it != end; it = array_next(it)) {
      lcd.print(*it);
      lcd.setCursor(i, 0);
      i++;
      delay(100);
    }
  }
};