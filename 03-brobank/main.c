#include <stdio.h>
#include "brobank.h"

static void print_balances(const BroBank *bank) {
    for (int i = 0; i < bank->account_count; i++) {
        printf("  Account %d: $%.2f\n", i, bank->balances[i]);
    }
}

int main(void) {
    BroBank bank;
    brobank_init(&bank, 3);
    bank.balances[0] = 100.0;
    bank.balances[1] = 50.0;
    bank.balances[2] = 0.0;

    printf("Starting balances:\n");
    print_balances(&bank);

    /* Queue up a deposit, a transfer, and a withdrawal. */
    brobankSubmit(&bank, (Transaction){TX_DEPOSIT, 0, 0, 25.0});
    brobankSubmit(&bank, (Transaction){TX_TRANSFER, 0, 1, 40.0});
    brobankSubmit(&bank, (Transaction){TX_WITHDRAW, 1, 1, 10.0});

    printf("\nProcessing 3 pending transactions...\n");
    while (brobankProcessNext(&bank)) {
        /* keep draining the queue */
    }
    print_balances(&bank);

    printf("\nUndoing the last transaction (withdrawal)...\n");
    brobankUndo(&bank);
    print_balances(&bank);

    printf("\nReachability after the transfer created account 0 -> 1:\n");
    printf("  BFS distance 0 -> 1: %d edge(s)\n", brobankBFS(&bank, 0, 1));
    printf("  DFS can reach 0 -> 2? %s\n", brobankDFS(&bank, 0, 2) ? "yes" : "no");

    return 0;
}
