#pragma once

#define G3_UNROLL_BODY(IDX, VAR, ARR, MAX, STATEMENT)                          \
  if (IDX < MAX) {                                                             \
    constexpr uint8_t VAR##_idx = IDX;                                         \
    constexpr auto VAR = ARR[IDX];                                             \
    STATEMENT                                                                  \
  }

#define G3_UNROLL(VAR, ARR, MAX, STATEMENT)                                    \
  G3_UNROLL_BODY(0, VAR, ARR, MAX, STATEMENT)                                  \
  G3_UNROLL_BODY(1, VAR, ARR, MAX, STATEMENT)                                  \
  G3_UNROLL_BODY(2, VAR, ARR, MAX, STATEMENT)                                  \
  G3_UNROLL_BODY(3, VAR, ARR, MAX, STATEMENT)                                  \
  G3_UNROLL_BODY(4, VAR, ARR, MAX, STATEMENT)                                  \
  G3_UNROLL_BODY(5, VAR, ARR, MAX, STATEMENT)                                  \
  G3_UNROLL_BODY(6, VAR, ARR, MAX, STATEMENT)                                  \
  G3_UNROLL_BODY(7, VAR, ARR, MAX, STATEMENT)
