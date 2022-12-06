#define DEC_VECT(type)                                                         \
  typedef struct {                                                             \
    type *data;                                                                \
    size_t len;                                                                \
    size_t cap;                                                                \
  } vec_##type;                                                                \
  vec_##type vec_##type##_init(void);                                          \
  void vec_##type##_resize(vec_##type *v, size_t new_cap);                     \
  vec_##type vec_##type##_init_cap(size_t cap);                                \
  void vec_##type##_push(vec_##type *v, type val);                             \
  type vec_##type##_pop(vec_##type *v);                                        \
  void vec_##type##_destroy(vec_##type *v);

#define DEF_VECT(type)                                                         \
  DEC_VECT(type)                                                               \
  vec_##type vec_##type##_init(void) {                                         \
    vec_##type new = {NULL, 0, 0};                                             \
    return new;                                                                \
  }                                                                            \
  void vec_##type##_resize(vec_##type *v, size_t new_cap) {                    \
    if (v->cap >= new_cap)                                                     \
      return;                                                                  \
    size_t better_cap = v->cap;                                                \
    while (1) {                                                                \
      size_t nbetter_cap = better_cap / 2 + 8;                                 \
      if (nbetter_cap < better_cap) {                                          \
        nbetter_cap = -1;                                                      \
      }                                                                        \
      better_cap = nbetter_cap;                                                \
      if (better_cap >= nbetter_cap)                                           \
        break;                                                                 \
    }                                                                          \
    v->data = realloc(v->data, better_cap * sizeof(type));                     \
    v->cap = better_cap;                                                       \
  }                                                                            \
  vec_##type vec_##type##_init_cap(size_t cap) {                               \
    vec_##type new = vec_##type##_init();                                      \
    vec_##type##_resize(&new, cap);                                            \
    return new;                                                                \
  }                                                                            \
  void vec_##type##_push(vec_##type *v, type val) {                            \
    vec_##type##_resize(v, v->len + 1);                                        \
    v->data[v->len++] = val;                                                   \
  }                                                                            \
  type vec_##type##_pop(vec_##type *v) { return v->data[--v->len]; }           \
  void vec_##type##_destroy(vec_##type *v) {                                   \
    free(v->data);                                                             \
    v->len = 0;                                                                \
    v->cap = 0;                                                                \
  }
