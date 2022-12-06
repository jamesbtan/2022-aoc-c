#define DEC_DEQT(type)                                                         \
  typedef struct {                                                             \
    type *data;                                                                \
    size_t head;                                                               \
    size_t len;                                                                \
    size_t cap;                                                                \
  } deq_##type;                                                                \
  deq_##type deq_##type##_init(void);                                          \
  type *deq_##type##_get(deq_##type *d, size_t ind);                           \
  void deq_##type##_align(deq_##type *d);                                      \
  void deq_##type##_resize(deq_##type *d, size_t new_cap);                     \
  deq_##type deq_##type##_init_cap(size_t cap);                                \
  void deq_##type##_pushb(deq_##type *d, type val);                            \
  type deq_##type##_popb(deq_##type *d);                                       \
  void deq_##type##_pushf(deq_##type *d, type val);                            \
  type deq_##type##_popf(deq_##type *d);                                       \
  void deq_##type##_destroy(deq_##type *d);

#define DEF_DEQT(type)                                                         \
  DEC_DEQT(type)                                                               \
  deq_##type deq_##type##_init(void) {                                         \
    deq_##type new = {NULL, 0, 0, 0};                                          \
    return new;                                                                \
  }                                                                            \
  type *deq_##type##_get(deq_##type *d, size_t ind) {                          \
    return &d->data[(d->head + ind) % d->cap];                                 \
  }                                                                            \
  void deq_##type##_align(deq_##type *d) {                                     \
    if (d->head == 0)                                                          \
      return;                                                                  \
    if (d->head + d->len < d->cap) {                                           \
      for (size_t i = 0; i < d->len; i++) {                                    \
        d->data[i] = d->data[d->head + i];                                     \
      }                                                                        \
      d->head = 0;                                                             \
    } else {                                                                   \
      type *buf = malloc(d->head * sizeof(type));                              \
      for (size_t i = d->head; i < d->cap; i++) {                              \
        buf[i] = d->data[i];                                                   \
      }                                                                        \
      for (size_t i = 0; i < (d->head + d->len % d->cap); i++) {               \
        d->data[i + d->cap - d->head] = d->data[i];                            \
      }                                                                        \
      for (size_t i = 0; i < d->cap - d->head; i++) {                          \
        d->data[i] = buf[i];                                                   \
      }                                                                        \
      d->head = 0;                                                             \
      free(buf);                                                               \
    }                                                                          \
  }                                                                            \
  void deq_##type##_resize(deq_##type *d, size_t new_cap) {                    \
    if (d->cap >= new_cap)                                                     \
      return;                                                                  \
    size_t better_cap = d->cap;                                                \
    while (1) {                                                                \
      size_t nbetter_cap = better_cap / 2 + 8;                                 \
      if (nbetter_cap < better_cap) {                                          \
        nbetter_cap = -1;                                                      \
      }                                                                        \
      better_cap = nbetter_cap;                                                \
      if (better_cap >= nbetter_cap)                                           \
        break;                                                                 \
    }                                                                          \
    deq_##type##_align(d);                                                     \
    d->data = realloc(d->data, better_cap * sizeof(type));                     \
    d->cap = better_cap;                                                       \
  }                                                                            \
  deq_##type deq_##type##_init_cap(size_t cap) {                               \
    deq_##type new = deq_##type##_init();                                      \
    deq_##type##_resize(&new, cap);                                            \
    return new;                                                                \
  }                                                                            \
  void deq_##type##_pushb(deq_##type *d, type val) {                           \
    deq_##type##_resize(d, d->len + 1);                                        \
    d->data[(d->head + d->len++) % d->cap] = val;                              \
  }                                                                            \
  type deq_##type##_popb(deq_##type *d) {                                      \
    return d->data[(d->head + --d->len) % d->cap];                             \
  }                                                                            \
  void deq_##type##_pushf(deq_##type *d, type val) {                           \
    deq_##type##_resize(d, d->len + 1);                                        \
    d->head += d->cap - 1;                                                     \
    d->head %= d->cap;                                                         \
    d->data[d->head] = val;                                                    \
    d->len++;                                                                  \
  }                                                                            \
  type deq_##type##_popf(deq_##type *d) {                                      \
    type result = d->data[d->head];                                            \
    d->head++;                                                                 \
    d->head %= d->cap;                                                         \
    d->len--;                                                                  \
    return result;                                                             \
  }                                                                            \
  void deq_##type##_destroy(deq_##type *d) {                                   \
    free(d->data);                                                             \
    d->head = 0;                                                               \
    d->len = 0;                                                                \
    d->cap = 0;                                                                \
  }
