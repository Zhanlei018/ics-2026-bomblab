#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    uint32_t low = (uint32_t)challenge;
    uint32_t high = (uint32_t)(challenge >> 32);
    uint32_t mid = (uint32_t)(challenge >> 16);
    uint32_t res0 = low ^ (high + 0xc9a);       
    uint32_t res1 = (high + (mid << 2)) ^ 0xb89c;           
    uint32_t res2 = (res1 + (res1 << 1)) ^ (low + 0xe480);
    uint32_t ans =  res2 ^ res0;    
    values[0] = ans;
    count = 1;
    // TODO: 根据 phase_01 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    values[0] = (challenge >> 6) & 0x1f;
    for (uint32_t i = 1; i < 6; i++)
    {
        uint32_t temp = challenge >> (20+4*(i-1));
        temp = temp & 0x1f;
        temp = temp + i;
        temp = temp ^ values[i-1];
        values[i] = temp + (temp << 1);
    }
    count = 6;
    // TODO: 根据 phase_02 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    uint32_t index = (uint32_t)(challenge & 0x7);
    uint32_t dispatch = (uint32_t)(challenge >> 32) ^ (uint32_t)(challenge >> 3);
    switch (index)
    {
    case 6:
        values[1] = (dispatch << 2) ^ 0x1974;
        break;
    case 7:
        values[1] = (dispatch ^ 0xb10) + (dispatch >> 1);
        break;
    case 0:
        values[1] = ((dispatch << 2) + dispatch) + 0x21f2f;
        break;
    case 1:
        values[1] = (dispatch << 2) ^ 0x2e76;
        break;
    case 2:
        values[1] = ((dispatch << 1) + dispatch) + 0xdf0e;
        break;
    case 3:
        values[1] = ((dispatch << 1) + dispatch) + 0x8fa9;
        break;
    case 4:
        values[1] = (dispatch >> 1) + (dispatch ^ 0x48b5);
        break;
    case 5:
        values[1] = ((dispatch << 2) + dispatch) + 0x237f3;
        break;
    default:
        values[1] = 0;
        break;
    }
    values[0] = index;
    count = 2;
    // TODO: 根据 phase_03 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    return 1;
}
