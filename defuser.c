#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

typedef struct ListNode
{
    struct ListNode *next;
    uint32_t data1;
    uint32_t data2;
} ListNode;

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count)
{
    size_t used = 0;
    for (size_t i = 0; i < count; ++i)
    {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used)
            return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap)
{
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    uint32_t low = (uint32_t)challenge;
    uint32_t high = (uint32_t)(challenge >> 32);
    uint32_t mid = (uint32_t)(challenge >> 16);
    uint32_t res0 = low ^ (high + 0xc9a);
    uint32_t res1 = (high + (mid << 2)) ^ 0xb89c;
    uint32_t res2 = (res1 + (res1 << 1)) ^ (low + 0xe480);
    uint32_t ans = res2 ^ res0;
    values[0] = ans;
    count = 1;
    // TODO: 根据 phase_01 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap)
{
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    values[0] = (challenge >> 6) & 0x1f;
    for (uint32_t i = 1; i < 6; i++)
    {
        uint32_t temp = challenge >> (20 + 4 * (i - 1));
        temp = temp & 0x1f;
        temp = temp + i;
        temp = temp ^ values[i - 1];
        values[i] = temp + (temp << 1);
    }
    count = 6;
    // TODO: 根据 phase_02 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap)
{
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

uint32_t p4_walk(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    uint32_t average = b + ((c - b) >> 1);
    if (average == a)
    {
        return (average + 0x75) ^ d;
    }
    uint32_t key = average + d;
    if (a < average)
    {
        uint32_t ans = p4_walk(a, b, average - 1, d);
        return (((ans << 2) + ans) ^ key) ^ 0x19;
    }
    else
    {
        uint32_t ans = p4_walk(a, average + 1, c, d);
        return (((ans << 2) + ans) ^ key) ^ 0x16;
    }
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap)
{
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    uint32_t r_number = challenge;
    uint32_t zero = 0;
    uint32_t c_number = 0x7f;
    r_number = r_number & c_number;
    uint32_t x_number = (challenge >> 7) ^ (challenge >> 32);
    values[0] = p4_walk(r_number, zero, c_number, x_number);
    count = 1;
    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

extern ListNode n_c00;
extern ListNode n_b70;
extern ListNode n_be0;
extern ListNode n_bf0;
extern ListNode n_b80;
extern ListNode n_b90;
extern ListNode n_ba0;
extern ListNode n_bb0;
extern ListNode n_bc0;
extern ListNode n_bd0;
extern ListNode n_b60;
extern ListNode n_c10;

ListNode n_b60 = {NULL,   0x0938, 0x9302};
ListNode n_c10 = {&n_bc0, 0x0b39, 0x1ac6};
ListNode n_be0 = {&n_b90, 0x084d, 0xa202};
ListNode n_bf0 = {&n_ba0, 0x0224, 0xa3e1};
ListNode n_b70 = {&n_be0, 0x047d, 0xc876};
ListNode n_c00 = {&n_b70, 0x0733, 0x895b};
ListNode n_b80 = {&n_bb0, 0x0561, 0x90b1};
ListNode n_b90 = {&n_b80, 0x0043, 0x3ac6};
ListNode n_ba0 = {&n_b60, 0x012a, 0xe557};
ListNode n_bb0 = {&n_c10, 0x0607, 0xb61f};
ListNode n_bc0 = {&n_bd0, 0x0317, 0x16d9};
ListNode n_bd0 = {&n_bf0, 0x0a87, 0x1c2e};

ListNode *g_list_array[8] = {
    &n_c00,
    &n_b70,
    &n_be0,
    &n_b90,
    &n_b80,
    &n_bb0,
    &n_c10,
    &n_bc0};

uint32_t p5_traverse(uint64_t a, uint32_t *b)
{
    uint32_t index = a & 7;
    ListNode *node = g_list_array[index];
    uint32_t num = (uint32_t)(a >> 6) ^ (uint32_t)(a >> 32);
    uint32_t count = (a >> 3) & 0x3;
    uint32_t data1 = node->data1;
    uint32_t temp = num ^ 0xd09d;
    uint32_t ans = (temp << 1) + temp + node->data2;
    *b = data1;
    ans = ans ^ data1;
    if (count == 0)
    {
        return ans;
    }
    uint32_t i = 1;
    do
    {
        node = node -> next;
        data1 = node -> data1;
        ans = (ans << 1) + ans;
        ans = ans + node -> data2;
        ans = ans ^ data1;
        *b = data1;
        i++;
    } while (i <= count);
    return ans;
}

int solve_phase_5(uint64_t challenge, char *out, size_t cap)
{
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    uint32_t out_value = 0;
    values[0] = p5_traverse(challenge, &out_value);
    values[1] = out_value;
    count = 2;
    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap)
{
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap)
{
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    return 1;
}
