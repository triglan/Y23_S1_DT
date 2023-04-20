

void SortByID() {
    //cur를 head의 끝까지
    struct node* cur;
    for (cur = head; cur->next != head; cur = cur->next) {
    }
    cur->next = NULL;

    //꼬리를 = NULL
    struct node* tail = NULL;
    int swap = 0;
    do {
        swap = 0;
        cur = head;
        while (cur->next != tail) {
            if (strcmp(cur->data.code, cur->next->data.code) > 0) {
                swapNode(cur, cur->next);
                swap = 1;
            }
            else {
                cur = cur->next;
            }
        }
        tail = cur;

    } while (swap);


    for (cur = head; cur->next != NULL; cur = cur->next) {
    }
    cur->next = head;
}

void swapNode(struct node* a, struct node* b) {
    struct node* prv = NULL;
    struct node* cur = head;
    while (cur != a) {
        prv = cur;
        cur = cur->next;
    }

    if (prv == NULL) {
        a->next = b->next;
        b->next = a;
        head = b;
    }
    else {
        prv->next = a->next;
        a->next = b->next;
        b->next = a;
    }
}