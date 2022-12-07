#define DEC_VECT(type, name)                                                         \
  typedef struct {                                                             \
    type *data;                                                                \
    size_t len;                                                                \
    size_t cap;                                                                \
  } vec_##name;                                                                \
  vec_##name vec_##name##_init(void);                                          \
  void vec_##name##_resize(vec_##name *v, size_t new_cap);                     \
  vec_##name vec_##name##_init_cap(size_t cap);                                \
  void vec_##name##_push(vec_##name *v, type val);                             \
  type vec_##name##_pop(vec_##name *v);                                        \
  void vec_##name##_destroy(vec_##name *v);

#define DEF_VECT(type, name)                                                         \
  DEC_VECT(type, name)                                                               \
  vec_##name vec_##name##_init(void) {                                         \
    vec_##name new = {NULL, 0, 0};                                             \
    return new;                                                                \
  }                                                                            \
  void vec_##name##_resize(vec_##name *v, size_t new_cap) {                    \
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
  vec_##name vec_##name##_init_cap(size_t cap) {                               \
    vec_##name new = vec_##name##_init();                                      \
    vec_##name##_resize(&new, cap);                                            \
    return new;                                                                \
  }                                                                            \
  void vec_##name##_push(vec_##name *v, type val) {                            \
    vec_##name##_resize(v, v->len + 1);                                        \
    v->data[v->len++] = val;                                                   \
  }                                                                            \
  type vec_##name##_pop(vec_##name *v) { return v->data[--v->len]; }           \
  void vec_##name##_destroy(vec_##name *v) {                                   \
    free(v->data);                                                             \
    v->len = 0;                                                                \
    v->cap = 0;                                                                \
  }
