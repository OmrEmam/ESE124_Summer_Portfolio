#include <string.h>
#include "brobank.h"
void brobank_init(BroBank *bank, int account_count) {
    if (!bank) return;
    memset(bank, 0, sizeof *bank); 
    bank->account_count = account_count;
    bank->p_rear = -1;
    bank->undo_top = -1;
}
int brobankSubmit(BroBank *bank, Transaction tx) {
     /* TODO: validate and enqueue transaction. */ 
    if (!bank) {
        return 0;
    }
    if (bank->p_count == CAPACITY) {
        return 0;
    }
    bank->p_rear = (bank->p_rear + 1) % CAPACITY;
    bank->pending[bank->p_rear] = tx;
    bank->p_count++;
    return 1;
}
int brobankProcessNext(BroBank *bank) { 
    /* TODO: dequeue, validate, update balances, push successful undo. */ 
    if (!bank) {
        return 0;
    }
    if (bank->p_count == 0) {
        return 0;
    }
 
    Transaction tx = bank->pending[bank->p_front];
    bank->p_front = (bank->p_front + 1) % CAPACITY;
    bank->p_count--;
 
    if (tx.from < 0 || tx.from >= bank->account_count) return 0;
    if (tx.to < 0 || tx.to >= bank->account_count) return 0;
 
    if (tx.type == TX_DEPOSIT) {
        if (tx.amount < 0) return 0;
        bank->balances[tx.to] += tx.amount;
    } else if (tx.type == TX_WITHDRAW) {
        if (tx.amount > bank->balances[tx.from]) return 0;
        bank->balances[tx.from] -= tx.amount;
    } else if (tx.type == TX_TRANSFER) {
        if (tx.amount <= 0) return 0;
        if (tx.amount > bank->balances[tx.from]) return 0;
        bank->balances[tx.from] -= tx.amount;
        bank->balances[tx.to] += tx.amount;
        bank->graph[tx.from][tx.to] = 1;
    } else {
        return 0;
    }
 
    if (bank->undo_top == CAPACITY - 1) return 0;
    bank->undo_top++;
    bank->undo[bank->undo_top] = tx;
    return 1;
}
int brobankUndo(BroBank *bank) {
     /* TODO: reverse most recent successful transaction. */ 
    if (!bank) return 0;
    if (bank->undo_top < 0) return 0;
 
    Transaction tx = bank->undo[bank->undo_top];
    bank->undo_top--;
 
    if (tx.type == TX_DEPOSIT) {
        bank->balances[tx.to] -= tx.amount;
    } else if (tx.type == TX_WITHDRAW) {
        bank->balances[tx.from] += tx.amount;
    } else if (tx.type == TX_TRANSFER) {
        bank->balances[tx.from] += tx.amount;
        bank->balances[tx.to] -= tx.amount;
    }
    return 1;
}
int brobankBFS(const BroBank *bank, int source, int destination) { /* TODO: fewest transfer edges. */ 
    if (!bank) return -1;
    if (source < 0 || source >= bank->account_count) return -1;
    if (destination < 0 || destination >= bank->account_count) return -1;
 
    int visited[BROBANK_MAX_ACCOUNTS] = {0};
    int dist[BROBANK_MAX_ACCOUNTS] = {0};
    Queue q;
    queueInit(&q);
    visited[source] = 1;
    enqueue(&q, source);
 
    while (!queueIsEmpty(&q)) {
        int cur;
        dequeue(&q, &cur);
        if (cur == destination) return dist[cur];
        for (int i = 0; i < bank->account_count; i++) {
            if (bank->graph[cur][i] && !visited[i]) {
                visited[i] = 1;
                dist[i] = dist[cur] + 1;
                enqueue(&q, i);
            }
        }
    }
    return -1;
}
int brobankDFS(const BroBank *bank, int source, int destination) { /* TODO: reachability. */
    if (!bank) return 0;
    if (source < 0 || source >= bank->account_count) return 0;
    if (destination < 0 || destination >= bank->account_count) return 0;
 
    int visited[BROBANK_MAX_ACCOUNTS] = {0};
    Stack s;
    stackInit(&s);
    stackPush(&s, source);
 
    while (!stackIsEmpty(&s)) {
        int cur;
        stackPop(&s, &cur);
        if (visited[cur]) continue;
        visited[cur] = 1;
        if (cur == destination) return 1;
        for (int i = 0; i < bank->account_count; i++) {
            if (bank->graph[cur][i] && !visited[i]) {
                stackPush(&s, i);
            }
        }
    }
    return 0;
}
