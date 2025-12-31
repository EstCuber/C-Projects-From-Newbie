#1. ALLOCATOR INFO

Свой малок писал по этому гайду simple_al -

https://arjunsreedharan.org/post/148675821737/memory-allocators-101-write-a-simple-memory

gcc -o memalloc.so -fPIC -shared memalloc.c < компилируем как библиотеку

bash

LD_PRELOAD=./memalloc.so ls -la < напишите это, чтобы протестировать ls например с моим маллоком

fish

env LD_PRELOAD=./memalloc.so ls < это на фише.

---

Также добавил allocator_test для замера 1000 аллокаций, работает в целом и хорошо!)
