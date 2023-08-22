Value array[N];
typedef Value* iterator;
iterator array_begin(Value a[]){ return &a[0];}
iterator array_end(Value a[], int n){ return &a[n];}
iterator array_next(iterator i) { return ++i;}