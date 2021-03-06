#include "Poly1305_64.h"

inline static void Hacl_Bignum_Modulo_reduce(uint64_t *b)
{
  uint64_t b0 = b[0];
  b[0] = (b0 << (uint32_t )4) + (b0 << (uint32_t )2);
}

inline static void Hacl_Bignum_Modulo_carry_top(uint64_t *b)
{
  uint64_t b2 = b[2];
  uint64_t b0 = b[0];
  uint64_t b2_42 = b2 >> (uint32_t )42;
  b[2] = b2 & (uint64_t )0x3ffffffffff;
  b[0] = (b2_42 << (uint32_t )2) + b2_42 + b0;
}

inline static void Hacl_Bignum_Modulo_carry_top_wide(FStar_UInt128_t *b)
{
  FStar_UInt128_t b2 = b[2];
  FStar_UInt128_t b0 = b[0];
  FStar_UInt128_t b2_;
  FStar_UInt128_t ret0;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x3ffffffffff, &ret0);
  FStar_UInt128_t s1 = ret0;
  FStar_UInt128_logand(&b2, &s1, &b2_);
  FStar_UInt128_t ret1;
  FStar_UInt128_shift_right(&b2, (uint32_t )42, &ret1);
  FStar_UInt128_t s0 = ret1;
  uint64_t b2_42 = FStar_Int_Cast_uint128_to_uint64(&s0);
  FStar_UInt128_t b0_;
  FStar_UInt128_t ret;
  FStar_Int_Cast_uint64_to_uint128((b2_42 << (uint32_t )2) + b2_42, &ret);
  FStar_UInt128_t s10 = ret;
  FStar_UInt128_add(&b0, &s10, &b0_);
  b[2] = b2_;
  b[0] = b0_;
}

inline static void
Hacl_Bignum_Fproduct_copy_from_wide_(uint64_t *output, FStar_UInt128_t *input)
{
  {
    FStar_UInt128_t uu____381 = input[0];
    uint64_t uu____380 = FStar_Int_Cast_uint128_to_uint64(&uu____381);
    output[0] = uu____380;
  }
  {
    FStar_UInt128_t uu____381 = input[1];
    uint64_t uu____380 = FStar_Int_Cast_uint128_to_uint64(&uu____381);
    output[1] = uu____380;
  }
  {
    FStar_UInt128_t uu____381 = input[2];
    uint64_t uu____380 = FStar_Int_Cast_uint128_to_uint64(&uu____381);
    output[2] = uu____380;
  }
}

inline static void Hacl_Bignum_Fproduct_shift(uint64_t *output)
{
  uint64_t tmp = output[2];
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )0 - (uint32_t )1;
    uint64_t z = output[ctr - (uint32_t )1];
    output[ctr] = z;
  }
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )1 - (uint32_t )1;
    uint64_t z = output[ctr - (uint32_t )1];
    output[ctr] = z;
  }
  output[0] = tmp;
}

inline static void
Hacl_Bignum_Fproduct_sum_scalar_multiplication_(
  FStar_UInt128_t *output,
  uint64_t *input,
  uint64_t s
)
{
  {
    FStar_UInt128_t uu____763 = output[0];
    uint64_t uu____766 = input[0];
    FStar_UInt128_t uu____762;
    FStar_UInt128_t ret;
    FStar_UInt128_mul_wide(uu____766, s, &ret);
    FStar_UInt128_t s1 = ret;
    FStar_UInt128_add_mod(&uu____763, &s1, &uu____762);
    output[0] = uu____762;
  }
  {
    FStar_UInt128_t uu____763 = output[1];
    uint64_t uu____766 = input[1];
    FStar_UInt128_t uu____762;
    FStar_UInt128_t ret;
    FStar_UInt128_mul_wide(uu____766, s, &ret);
    FStar_UInt128_t s1 = ret;
    FStar_UInt128_add_mod(&uu____763, &s1, &uu____762);
    output[1] = uu____762;
  }
  {
    FStar_UInt128_t uu____763 = output[2];
    uint64_t uu____766 = input[2];
    FStar_UInt128_t uu____762;
    FStar_UInt128_t ret;
    FStar_UInt128_mul_wide(uu____766, s, &ret);
    FStar_UInt128_t s1 = ret;
    FStar_UInt128_add_mod(&uu____763, &s1, &uu____762);
    output[2] = uu____762;
  }
}

inline static void Hacl_Bignum_Fproduct_carry_wide_(FStar_UInt128_t *tmp)
{
  {
    uint32_t ctr = (uint32_t )0;
    FStar_UInt128_t tctr = tmp[ctr];
    FStar_UInt128_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t
    r0 = FStar_Int_Cast_uint128_to_uint64(&tctr) & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    FStar_UInt128_t c;
    FStar_UInt128_shift_right(&tctr, (uint32_t )44, &c);
    FStar_Int_Cast_uint64_to_uint128(r0, &tmp[ctr]);
    FStar_UInt128_add(&tctrp1, &c, &tmp[ctr + (uint32_t )1]);
  }
  {
    uint32_t ctr = (uint32_t )1;
    FStar_UInt128_t tctr = tmp[ctr];
    FStar_UInt128_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t
    r0 = FStar_Int_Cast_uint128_to_uint64(&tctr) & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    FStar_UInt128_t c;
    FStar_UInt128_shift_right(&tctr, (uint32_t )44, &c);
    FStar_Int_Cast_uint64_to_uint128(r0, &tmp[ctr]);
    FStar_UInt128_add(&tctrp1, &c, &tmp[ctr + (uint32_t )1]);
  }
}

inline static void Hacl_Bignum_Fproduct_carry_limb_(uint64_t *tmp)
{
  {
    uint32_t ctr = (uint32_t )0;
    uint64_t tctr = tmp[ctr];
    uint64_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t r0 = tctr & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    uint64_t c = tctr >> (uint32_t )44;
    tmp[ctr] = r0;
    tmp[ctr + (uint32_t )1] = tctrp1 + c;
  }
  {
    uint32_t ctr = (uint32_t )1;
    uint64_t tctr = tmp[ctr];
    uint64_t tctrp1 = tmp[ctr + (uint32_t )1];
    uint64_t r0 = tctr & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
    uint64_t c = tctr >> (uint32_t )44;
    tmp[ctr] = r0;
    tmp[ctr + (uint32_t )1] = tctrp1 + c;
  }
}

inline static void Hacl_Bignum_Fmul_shift_reduce(uint64_t *output)
{
  Hacl_Bignum_Fproduct_shift(output);
  Hacl_Bignum_Modulo_reduce(output);
  return;
}

static void
Hacl_Bignum_Fmul_mul_shift_reduce_(FStar_UInt128_t *output, uint64_t *input, uint64_t *input2)
{
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )0 - (uint32_t )1;
    uint32_t i1 = ctr;
    uint32_t j = (uint32_t )2 - i1;
    uint64_t input2i = input2[j];
    Hacl_Bignum_Fproduct_sum_scalar_multiplication_(output, input, input2i);
    if (ctr > (uint32_t )0)
      Hacl_Bignum_Fmul_shift_reduce(input);
  }
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )1 - (uint32_t )1;
    uint32_t i1 = ctr;
    uint32_t j = (uint32_t )2 - i1;
    uint64_t input2i = input2[j];
    Hacl_Bignum_Fproduct_sum_scalar_multiplication_(output, input, input2i);
    if (ctr > (uint32_t )0)
      Hacl_Bignum_Fmul_shift_reduce(input);
  }
  {
    uint32_t ctr = (uint32_t )3 - (uint32_t )2 - (uint32_t )1;
    uint32_t i1 = ctr;
    uint32_t j = (uint32_t )2 - i1;
    uint64_t input2i = input2[j];
    Hacl_Bignum_Fproduct_sum_scalar_multiplication_(output, input, input2i);
    if (ctr > (uint32_t )0)
      Hacl_Bignum_Fmul_shift_reduce(input);
  }
}

inline static void Hacl_Bignum_Fmul_fmul_(uint64_t *output, uint64_t *input, uint64_t *input2)
{
  FStar_UInt128_t ret;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0, &ret);
  KRML_CHECK_SIZE(ret, (uint32_t )3);
  FStar_UInt128_t t[3];
  for (uintmax_t _i = 0; _i < (uint32_t )3; ++_i)
    t[_i] = ret;
  Hacl_Bignum_Fmul_mul_shift_reduce_(t, input, input2);
  Hacl_Bignum_Fproduct_carry_wide_(t);
  Hacl_Bignum_Modulo_carry_top_wide(t);
  Hacl_Bignum_Fproduct_copy_from_wide_(output, t);
  uint64_t i0 = output[0];
  uint64_t i1 = output[1];
  uint64_t i0_ = i0 & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
  uint64_t i1_ = i1 + (i0 >> (uint32_t )44);
  output[0] = i0_;
  output[1] = i1_;
}

inline static void Hacl_Bignum_Fmul_fmul(uint64_t *output, uint64_t *input, uint64_t *input2)
{
  uint64_t tmp[3] = { 0 };
  memcpy(tmp, input, (uint32_t )3 * sizeof input[0]);
  Hacl_Bignum_Fmul_fmul_(output, tmp, input2);
}

inline static void
Hacl_Bignum_AddAndMultiply_add_and_multiply(uint64_t *acc, uint64_t *block, uint64_t *r)
{
  {
    uint64_t uu____763 = acc[0];
    uint64_t uu____766 = block[0];
    uint64_t uu____762 = uu____763 + uu____766;
    acc[0] = uu____762;
  }
  {
    uint64_t uu____763 = acc[1];
    uint64_t uu____766 = block[1];
    uint64_t uu____762 = uu____763 + uu____766;
    acc[1] = uu____762;
  }
  {
    uint64_t uu____763 = acc[2];
    uint64_t uu____766 = block[2];
    uint64_t uu____762 = uu____763 + uu____766;
    acc[2] = uu____762;
  }
  Hacl_Bignum_Fmul_fmul(acc, acc, r);
  return;
}

inline static void
Hacl_Impl_Poly1305_64_poly1305_update(Hacl_Impl_Poly1305_64_poly1305_state *st, uint8_t *m)
{
  uint64_t *acc = st->h;
  uint64_t *r = st->r;
  uint64_t tmp[3] = { 0 };
  FStar_UInt128_t m0;
  load128_le(m, &m0);
  uint64_t r0 = FStar_Int_Cast_uint128_to_uint64(&m0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret0;
  FStar_UInt128_shift_right(&m0, (uint32_t )44, &ret0);
  FStar_UInt128_t s0 = ret0;
  uint64_t r1 = FStar_Int_Cast_uint128_to_uint64(&s0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret;
  FStar_UInt128_shift_right(&m0, (uint32_t )88, &ret);
  FStar_UInt128_t s00 = ret;
  uint64_t r2 = FStar_Int_Cast_uint128_to_uint64(&s00);
  tmp[0] = r0;
  tmp[1] = r1;
  tmp[2] = r2;
  uint64_t b2 = tmp[2];
  uint64_t b2_ = (uint64_t )0x10000000000 | b2;
  tmp[2] = b2_;
  Hacl_Bignum_AddAndMultiply_add_and_multiply(acc, tmp, r);
  return;
}

inline static void
Hacl_Impl_Poly1305_64_poly1305_process_last_block_(
  uint8_t *block,
  Hacl_Impl_Poly1305_64_poly1305_state *st,
  uint8_t *m,
  uint64_t rem_
)
{
  uint64_t tmp[3] = { 0 };
  FStar_UInt128_t m0;
  load128_le(block, &m0);
  uint64_t r0 = FStar_Int_Cast_uint128_to_uint64(&m0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret0;
  FStar_UInt128_shift_right(&m0, (uint32_t )44, &ret0);
  FStar_UInt128_t s0 = ret0;
  uint64_t r1 = FStar_Int_Cast_uint128_to_uint64(&s0) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret;
  FStar_UInt128_shift_right(&m0, (uint32_t )88, &ret);
  FStar_UInt128_t s00 = ret;
  uint64_t r2 = FStar_Int_Cast_uint128_to_uint64(&s00);
  tmp[0] = r0;
  tmp[1] = r1;
  tmp[2] = r2;
  Hacl_Bignum_AddAndMultiply_add_and_multiply(st->h, tmp, st->r);
  return;
}

inline static void
Hacl_Impl_Poly1305_64_poly1305_process_last_block(
  Hacl_Impl_Poly1305_64_poly1305_state *st,
  uint8_t *m,
  uint64_t rem_
)
{
  uint8_t zero1 = (uint8_t )0;
  KRML_CHECK_SIZE(zero1, (uint32_t )16);
  uint8_t block[16];
  for (uintmax_t _i = 0; _i < (uint32_t )16; ++_i)
    block[_i] = zero1;
  uint32_t i0 = (uint32_t )rem_;
  uint32_t i = (uint32_t )rem_;
  memcpy(block, m, i * sizeof m[0]);
  block[i0] = (uint8_t )1;
  Hacl_Impl_Poly1305_64_poly1305_process_last_block_(block, &st[0], m, rem_);
  return;
}

static void Hacl_Impl_Poly1305_64_poly1305_last_pass(uint64_t *acc)
{
  Hacl_Bignum_Fproduct_carry_limb_(acc);
  Hacl_Bignum_Modulo_carry_top(acc);
  uint64_t a0 = acc[0];
  uint64_t a10 = acc[1];
  uint64_t a20 = acc[2];
  uint64_t a0_ = a0 & (uint64_t )0xfffffffffff;
  uint64_t r0 = a0 >> (uint32_t )44;
  uint64_t a1_ = (a10 + r0) & (uint64_t )0xfffffffffff;
  uint64_t r1 = (a10 + r0) >> (uint32_t )44;
  uint64_t a2_ = a20 + r1;
  acc[0] = a0_;
  acc[1] = a1_;
  acc[2] = a2_;
  Hacl_Bignum_Modulo_carry_top(acc);
  uint64_t i0 = acc[0];
  uint64_t i1 = acc[1];
  uint64_t i0_ = i0 & (((uint64_t )1 << (uint32_t )44) - (uint64_t )1);
  uint64_t i1_ = i1 + (i0 >> (uint32_t )44);
  acc[0] = i0_;
  acc[1] = i1_;
  uint64_t a00 = acc[0];
  uint64_t a1 = acc[1];
  uint64_t a2 = acc[2];
  uint64_t mask0 = FStar_UInt64_gte_mask(a00, (uint64_t )0xffffffffffb);
  uint64_t mask1 = FStar_UInt64_eq_mask(a1, (uint64_t )0xfffffffffff);
  uint64_t mask2 = FStar_UInt64_eq_mask(a2, (uint64_t )0x3ffffffffff);
  uint64_t mask = mask0 & mask1 & mask2;
  uint64_t a0_0 = a00 - ((uint64_t )0xffffffffffb & mask);
  uint64_t a1_0 = a1 - ((uint64_t )0xfffffffffff & mask);
  uint64_t a2_0 = a2 - ((uint64_t )0x3ffffffffff & mask);
  acc[0] = a0_0;
  acc[1] = a1_0;
  acc[2] = a2_0;
}

static void
Hacl_Impl_Poly1305_64_mk_state(
  uint64_t *r,
  uint64_t *h,
  Hacl_Impl_Poly1305_64_poly1305_state *ret
)
{
  ret[0] = ((Hacl_Impl_Poly1305_64_poly1305_state ){ .r = r, .h = h });
}

static void
Hacl_Standalone_Poly1305_64_poly1305_blocks(
  Hacl_Impl_Poly1305_64_poly1305_state *st,
  uint8_t *m,
  uint64_t len1
)
{
  if (len1 == (uint64_t )0)
    return;
  else
  {
    uint8_t *block = m;
    uint8_t *tail1 = m + (uint32_t )16;
    Hacl_Impl_Poly1305_64_poly1305_update(&st[0], block);
    uint64_t len2 = len1 - (uint64_t )1;
    Hacl_Standalone_Poly1305_64_poly1305_blocks(&st[0], tail1, len2);
    return;
  }
}

static void
Hacl_Standalone_Poly1305_64_poly1305_partial(
  Hacl_Impl_Poly1305_64_poly1305_state *st,
  uint8_t *input,
  uint64_t len1,
  uint8_t *kr
)
{
  uint8_t *x1 = kr;
  FStar_UInt128_t k1;
  load128_le(x1, &k1);
  FStar_UInt128_t k_clamped;
  FStar_UInt128_t ret0;
  FStar_UInt128_t ret1;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x0ffffffc0fffffff, &ret1);
  FStar_UInt128_t s1 = ret1;
  FStar_UInt128_t ret2;
  FStar_UInt128_t ret3;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x0ffffffc0ffffffc, &ret3);
  FStar_UInt128_t s0 = ret3;
  FStar_UInt128_shift_left(&s0, (uint32_t )64, &ret2);
  FStar_UInt128_t s00 = ret2;
  FStar_UInt128_logor(&s00, &s1, &ret0);
  FStar_UInt128_t s10 = ret0;
  FStar_UInt128_logand(&k1, &s10, &k_clamped);
  uint64_t r0 = FStar_Int_Cast_uint128_to_uint64(&k_clamped) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret4;
  FStar_UInt128_shift_right(&k_clamped, (uint32_t )44, &ret4);
  FStar_UInt128_t s01 = ret4;
  uint64_t r1 = FStar_Int_Cast_uint128_to_uint64(&s01) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret;
  FStar_UInt128_shift_right(&k_clamped, (uint32_t )88, &ret);
  FStar_UInt128_t s02 = ret;
  uint64_t r2 = FStar_Int_Cast_uint128_to_uint64(&s02);
  st->r[0] = r0;
  st->r[1] = r1;
  st->r[2] = r2;
  st->h[0] = (uint64_t )0;
  st->h[1] = (uint64_t )0;
  st->h[2] = (uint64_t )0;
  Hacl_Standalone_Poly1305_64_poly1305_blocks(&st[0], input, len1);
  return;
}

static void
Hacl_Standalone_Poly1305_64_poly1305_complete(
  Hacl_Impl_Poly1305_64_poly1305_state *st,
  uint8_t *m,
  uint64_t len1,
  uint8_t *k1
)
{
  uint8_t *kr = k1;
  uint64_t len16 = len1 >> (uint32_t )4;
  uint64_t rem16 = len1 & (uint64_t )0xf;
  uint8_t *part_input = m;
  uint8_t *last_block = m + (uint32_t )((uint64_t )16 * len16);
  Hacl_Standalone_Poly1305_64_poly1305_partial(&st[0], part_input, len16, kr);
  if (rem16 == (uint64_t )0)
  {
    
  }
  else
    Hacl_Impl_Poly1305_64_poly1305_process_last_block(&st[0], last_block, rem16);
  uint64_t *acc = st->h;
  Hacl_Impl_Poly1305_64_poly1305_last_pass(acc);
  return;
}

static void
Hacl_Standalone_Poly1305_64_crypto_onetimeauth_(
  uint8_t *output,
  uint8_t *input,
  uint64_t len1,
  uint8_t *k1
)
{
  uint64_t buf[6] = { 0 };
  uint64_t *r = buf;
  uint64_t *h = buf + (uint32_t )3;
  Hacl_Impl_Poly1305_64_poly1305_state st;
  Hacl_Impl_Poly1305_64_mk_state(r, h, &st);
  (void )k1;
  uint8_t *key_s = k1 + (uint32_t )16;
  Hacl_Standalone_Poly1305_64_poly1305_complete(&st, input, len1, k1);
  uint64_t *acc = st.h;
  FStar_UInt128_t k_;
  load128_le(key_s, &k_);
  uint64_t h0 = acc[0];
  uint64_t h1 = acc[1];
  uint64_t h2 = acc[2];
  FStar_UInt128_t ret0;
  FStar_UInt128_t ret1;
  FStar_Int_Cast_uint64_to_uint128(h1 << (uint32_t )44 | h0, &ret1);
  FStar_UInt128_t s1 = ret1;
  FStar_UInt128_t ret2;
  FStar_UInt128_t ret;
  FStar_Int_Cast_uint64_to_uint128(h2 << (uint32_t )24 | h1 >> (uint32_t )20, &ret);
  FStar_UInt128_t s0 = ret;
  FStar_UInt128_shift_left(&s0, (uint32_t )64, &ret2);
  FStar_UInt128_t s00 = ret2;
  FStar_UInt128_logor(&s00, &s1, &ret0);
  FStar_UInt128_t acc_ = ret0;
  FStar_UInt128_t mac_;
  FStar_UInt128_add_mod(&acc_, &k_, &mac_);
  store128_le(output, &mac_);
}

static void
Hacl_Standalone_Poly1305_64_crypto_onetimeauth(
  uint8_t *output,
  uint8_t *input,
  uint64_t len1,
  uint8_t *k1
)
{
  Hacl_Standalone_Poly1305_64_crypto_onetimeauth_(output, input, len1, k1);
  return;
}

void
Poly1305_64_mk_state(uint64_t *r, uint64_t *acc, Hacl_Impl_Poly1305_64_poly1305_state *ret)
{
  Hacl_Impl_Poly1305_64_poly1305_state ret0;
  Hacl_Impl_Poly1305_64_mk_state(r, acc, &ret0);
  ret[0] = ret0;
}

void Poly1305_64_init(Hacl_Impl_Poly1305_64_poly1305_state *st, uint8_t *k1)
{
  uint8_t *x1 = k1;
  uint8_t *x10 = x1;
  FStar_UInt128_t k10;
  load128_le(x10, &k10);
  FStar_UInt128_t k_clamped;
  FStar_UInt128_t ret0;
  FStar_UInt128_t ret1;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x0ffffffc0fffffff, &ret1);
  FStar_UInt128_t s1 = ret1;
  FStar_UInt128_t ret2;
  FStar_UInt128_t ret3;
  FStar_Int_Cast_uint64_to_uint128((uint64_t )0x0ffffffc0ffffffc, &ret3);
  FStar_UInt128_t s0 = ret3;
  FStar_UInt128_shift_left(&s0, (uint32_t )64, &ret2);
  FStar_UInt128_t s00 = ret2;
  FStar_UInt128_logor(&s00, &s1, &ret0);
  FStar_UInt128_t s10 = ret0;
  FStar_UInt128_logand(&k10, &s10, &k_clamped);
  uint64_t r0 = FStar_Int_Cast_uint128_to_uint64(&k_clamped) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret4;
  FStar_UInt128_shift_right(&k_clamped, (uint32_t )44, &ret4);
  FStar_UInt128_t s01 = ret4;
  uint64_t r1 = FStar_Int_Cast_uint128_to_uint64(&s01) & (uint64_t )0xfffffffffff;
  FStar_UInt128_t ret;
  FStar_UInt128_shift_right(&k_clamped, (uint32_t )88, &ret);
  FStar_UInt128_t s02 = ret;
  uint64_t r2 = FStar_Int_Cast_uint128_to_uint64(&s02);
  st->r[0] = r0;
  st->r[1] = r1;
  st->r[2] = r2;
  st->h[0] = (uint64_t )0;
  st->h[1] = (uint64_t )0;
  st->h[2] = (uint64_t )0;
}

void *Poly1305_64_empty_log = (void *)(uint8_t )0;

void Poly1305_64_update_block(Hacl_Impl_Poly1305_64_poly1305_state *st, uint8_t *m)
{
  Hacl_Impl_Poly1305_64_poly1305_update(&st[0], m);
}

void Poly1305_64_update(Hacl_Impl_Poly1305_64_poly1305_state *st, uint8_t *m, uint32_t len1)
{
  if (len1 == (uint32_t )0)
    return;
  else
  {
    uint8_t *block = m;
    uint8_t *m_ = m + (uint32_t )16;
    uint32_t len2 = len1 - (uint32_t )1;
    Poly1305_64_update_block(&st[0], block);
    Poly1305_64_update(&st[0], m_, len2);
    return;
  }
}

void
Poly1305_64_update_last(Hacl_Impl_Poly1305_64_poly1305_state *st, uint8_t *m, uint32_t len1)
{
  uint8_t *x2 = m;
  if ((uint64_t )len1 == (uint64_t )0)
  {
    
  }
  else
    Hacl_Impl_Poly1305_64_poly1305_process_last_block(&st[0], x2, (uint64_t )len1);
  uint64_t *acc = st->h;
  Hacl_Impl_Poly1305_64_poly1305_last_pass(acc);
  return;
}

void Poly1305_64_finish(Hacl_Impl_Poly1305_64_poly1305_state *st, uint8_t *mac, uint8_t *k1)
{
  uint64_t *acc = st->h;
  FStar_UInt128_t k_;
  load128_le(k1, &k_);
  uint64_t h0 = acc[0];
  uint64_t h1 = acc[1];
  uint64_t h2 = acc[2];
  FStar_UInt128_t ret0;
  FStar_UInt128_t ret1;
  FStar_Int_Cast_uint64_to_uint128(h1 << (uint32_t )44 | h0, &ret1);
  FStar_UInt128_t s1 = ret1;
  FStar_UInt128_t ret2;
  FStar_UInt128_t ret;
  FStar_Int_Cast_uint64_to_uint128(h2 << (uint32_t )24 | h1 >> (uint32_t )20, &ret);
  FStar_UInt128_t s0 = ret;
  FStar_UInt128_shift_left(&s0, (uint32_t )64, &ret2);
  FStar_UInt128_t s00 = ret2;
  FStar_UInt128_logor(&s00, &s1, &ret0);
  FStar_UInt128_t acc_ = ret0;
  FStar_UInt128_t mac_;
  FStar_UInt128_add_mod(&acc_, &k_, &mac_);
  store128_le(mac, &mac_);
  return;
}

void
Poly1305_64_crypto_onetimeauth(uint8_t *output, uint8_t *input, uint64_t len1, uint8_t *k1)
{
  Hacl_Standalone_Poly1305_64_crypto_onetimeauth(output, input, len1, k1);
  return;
}

